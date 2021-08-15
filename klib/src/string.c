#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  int len = 0;
  while(*(s++)!='\0'){
    len++;
  }
  return len;
}

char *strcpy(char *dst, const char *src) {
  int i;
  for(i=0; src[i]!='\0'; i++){
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  int i;
  for(i=0; i<n; i++) {
    dst[i] = src[i];
  }
  dst[i]='\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  int start = strlen(dst);
  while (*src!='\0'){
    dst[start++] = *(src++);
  }
  dst[start]='\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  while(*s1 == *s2 && *s1!='\0'){
    s1++; s2++;
  }
  return *s1-*s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  while(*s1 == *s2 && *s1!='\0' && n--){
    s1++; s2++;
  }
  return *s1-*s2;
}

void *memset(void *s, int c, size_t n) {
  int i;
  for (i=0; i<n; i++) {
    ((char*)s)[i]=c;
  }
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {
  int i;
  for(i=0;i<n;i++){
    ((char*)dst)[i] = ((char*)src)[i];
  }
  return dst;
}

void *memcpy(void *out, const void *in, size_t n) {
  for (int i=0;i<n;i++) {
    ((char*)out)[i]=((char*)in)[i];
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  while( *((char*)s1) == *((char*)s2) && n-- ){
    s1++; s2++;
  }
  return *((char*)s1 - 1) - *((char*)s2 - 1);
}

#endif
