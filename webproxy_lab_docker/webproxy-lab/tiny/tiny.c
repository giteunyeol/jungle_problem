/* $begin tinymain */
/*
 * tiny.c - A simple, iterative HTTP/1.0 Web server that uses the
 *     GET method to serve static and dynamic content.
 *
 * Updated 11/2019 droh
 *   - Fixed sprintf() aliasing issue in serve_static(), and clienterror().
 */
#include "csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
                 char *longmsg);

int main(int argc, char **argv)
{
  int listenfd, connfd;
  char hostname[MAXLINE], port[MAXLINE];
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;

  /* Check command line args */
  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  listenfd = Open_listenfd(argv[1]); //듣기 소켓을 오픈함
  while (1)
  {
    clientlen = sizeof(clientaddr); //반복적인 연결요청 접수  
    connfd = Accept(listenfd, (SA *)&clientaddr,
                    &clientlen); // line:netp:tiny:accept
    Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE,
                0);
    printf("Accepted connection from (%s, %s)\n", hostname, port);
    doit(connfd);  // line:netp:tiny:doit 트렌젝션
    Close(connfd); // line:netp:tiny:close 본인 연결 끝을 닫음.
  }
}


void doit(int fd) //HTTP트랜잭션 하나 처리
{
  int is_static;
  struct stat sbuf;
  char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
  char filename[MAXLINE], cgiargs[MAXLINE];
  rio_t rio; 

  //요청라인을 읽고 분석
  Rio_readinitb(&rio, fd);
  Rio_readlineb(&rio, buf, MAXLINE);
  printf("헤더 요청: \n");
  printf("%s", buf);
  sscanf(buf, "%s %s %s", method, uri, version);
  if(strcasecmp(method, "GET")){ //GET요청이 아니면 에러 리턴, main루틴으로 돌아옴 (돌아와서 연결을 닫고 다음 연결요청을 기다림)
    clienterror(fd, method, "501", "Not implemented",
              "Tiny does not implement this method");
    return;
  }
  read_requesthdrs(&rio); //제대로 들어왓으면 읽어들이고, 다른 요청 헤더 무시
  
  //GET요청으로부터 URI파싱
  is_static = parse_uri(uri, filename, cgiargs); //정적인지 동적인지 플래그, 파일이 디스크에 있지 않으면 에러 메세지를 클라이언트에게 보내고 리턴
  if(stat(filename, &buf) < 0){
    clienterror(fd, filename, "404", "Not found",
                "Tiny couldn't find this file");
  }

  if(is_static) { //정적컨텐츠면
    if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) { //보통파일, 읽기 권한이 있으면
      clienterror(fd, filename, "403", "Forbidden",
                  "Tiny couldn't read this file");
      return;
    }
    serve_static(fd, filename, sbuf.st_size);
  }
  else { //동적 컨텐츠라면
    if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
        clienterror(fd, filename, "403", "Forbidden",
                    "Tiny couldn't run the CGI program");
      return;
    }
    serve_dynamic(fd, filename, cgiargs);
  }
}