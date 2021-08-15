#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

const char* hex_lower = "0123456789abcdef";
const char* hex_upper = "0123456789ABCDEF";
const char* FILL_CHAR = " 0";
enum FILL_FLAG {
  FILL_SPACE = 0,
  FILL_ZERO = 1,
};


inline int _generate_hex_str(char* num_buf, uint64_t num, const char* hex_array) {
  int idx = 0;
  if(num == 0) {
    num_buf[idx++] = '0';
  }
  else {
    while (num) {
      num_buf[idx++] = hex_array[num%16];
      num /= 16;
    }
  }
  return idx;
}

inline int _generate_dec_str(char* num_buf, uint64_t num) {
  int idx = 0;
  if (num == 0) {
    num_buf[idx++] = '0';
  }
  else {
    while(num) {
      num_buf[idx++] = num%10 + '0';
      num /= 10;
    }
  }
  return idx;
}

inline char* _generate_fill_char(char* buf, int fill_width, int fill_flag) {
  char ch = FILL_CHAR[fill_flag];
  while (fill_width--) {
    *buf++ = ch;
  }
  return buf;
}

inline char* _generate_neg(char* buf, int64_t num) {
  if (num < 0) {
    *buf++ = '-';
  }
  return buf;
}

inline char* _copy_numbuf_to_buf(char* buf, char* num_buf, int num_len) {
  while(num_len--){
    *buf++ = num_buf[num_len];
  }
  return buf;
}

int printf(const char *fmt, ...) {
  va_list args;
  int i, len;
  char out[1024];
  va_start(args, fmt);
  vsprintf(out, fmt, args);
  va_end(args);
  len = strlen(out);
  for(i=0;i<len;i++){
    putch(out[i]);
  }
  return 0;
}

int vsprintf(char *out, const char *ori_fmt, va_list ap) {
  char* buf = out;
  int i,len;
  int64_t num;
  uint64_t unum;
  int num_len;
  int flag, field_width;
  const char* tmp;
  char num_buf[100];
  const char* fmt = ori_fmt;
  while (*fmt) {
    if (*fmt != '%') {
      *buf++ = *fmt++;
      continue;
    }
    flag = 0;
    fmt++;  // skip %
    if (*fmt == ' ') {
      flag = FILL_SPACE;
    }
    else if (*fmt == '0'){
      flag = FILL_ZERO;
    }
    field_width = 0;
    if (*fmt >= '0' && *fmt <= '9') {
      while (*fmt >= '0' && *fmt <= '9'){
        field_width = field_width * 10 + *fmt - '0';
        fmt++;
      }
    }
    switch (*fmt++)
    {
    case 's':
      tmp = va_arg(ap, char*);
      len = strlen(tmp);
      for (i=0; i<len; i++) {
        *buf++ = *tmp++;
      }
      continue;
      break;  // case 's'
    case 'd':
      num = (int64_t)va_arg(ap, int);
      if (num < 0) {
        *buf++ = '-';
        num = -num;
      }
      num_len = _generate_dec_str(num_buf, (uint64_t)num);
      if (num_len < field_width) {
        buf = _generate_fill_char(buf, field_width - num_len, flag);
      }
      buf = _copy_numbuf_to_buf(buf, num_buf, num_len);
      break;  // case 'd'
    case 'l':
      switch (*fmt++)
      {
      case 'd':
        num = va_arg(ap, int64_t);
        if (num < 0) {
          *buf++ = '-';
          num = -num;
        }
        num_len = _generate_dec_str(num_buf, (uint64_t)num);
        if (num_len < field_width) {
          buf = _generate_fill_char(buf, field_width - num_len, flag);
        }
        buf = _copy_numbuf_to_buf(buf, num_buf, num_len);
        break;
      default:
        printf("ori_fmt: %s\n", ori_fmt);
        panic("unsupported flag\n");
        break;
      }
      break; // case 'l'
    case 'x':
      unum = va_arg(ap, uint32_t);
      num_len = _generate_hex_str(num_buf, unum, hex_lower);
      if (num_len < field_width) {
        buf = _generate_fill_char(buf, field_width - num_len, flag);
      }
      buf = _copy_numbuf_to_buf(buf, num_buf, num_len);
      break; // case 'x'
    case 'c':
      if (1 < field_width) {
        buf = _generate_fill_char(buf, field_width - 1, flag);
      }
      *buf++ = (char)va_arg(ap, int);
      break; // case 'c':
    default:
      printf("ori_fmt: %s\n", ori_fmt);
      panic("unsupported flag\n");
      break;
    }
  }
  *buf = '\0';

  return 0;
}

int sprintf(char *out, const char *fmt, ...) {
  va_list args;
  int val;
  va_start(args, fmt);
  val = vsprintf(out, fmt, args);
  va_end(args);
  return val;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
