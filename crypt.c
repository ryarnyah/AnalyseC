#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER 1 << 12

#ifdef DEBUG
#define DERROR(function, test, in_action, out_action){				\
if(test){								\
fprintf(stderr, \
"\n--------------- \tErreur : %s \t---------------\n\
Fichier : %s\n\
Fonction : %s\n\
Ligne : %d\n",\
function, __FILE__, __FUNCTION__, __LINE__);\
{in_action;}								\
fprintf(stderr,"--------------- \tErreur : %s \t---------------\n",function);\
{out_action;}}							\
}
#else
#define DERROR(function, test, in_action, out_action){	\
if(test){\
{in_action;}				\
{out_action;}				\
}						\
}
#endif

#ifdef DEBUG
static char xor(char a, char b)
{
  return (a & ~b) | (~a & b);
}
#else
#define xor(a, b) a ^ b
#endif

static char *fcrypt(char *chaine, int taille)
{
  int i = 0;
  char *tmp = NULL;

  DERROR("malloc", (tmp = malloc(sizeof(*tmp) * taille)) == NULL,
	 (void) NULL, return NULL);
  (void) memcpy(tmp, chaine, (size_t) taille);

  for (i = 0; i < taille - 1; i++)
  {
    tmp[i] = xor(chaine[i], chaine[i + 1]);
  }
  return tmp;
}

static char *fdecrypt(char *chaineCrypt, int taille)
{
  int i = 0;
  char *tmp = NULL;

  DERROR("malloc", (tmp = malloc(sizeof(*tmp) * taille)) == NULL,
	 (void) NULL, return NULL);
  (void) memcpy(tmp, chaineCrypt, (size_t) taille);

  for (i = taille - 2; i >= 0; i--)
  {
    tmp[i] = xor(tmp[i], tmp[i + 1]);
  }
  return tmp;
}

static char *fileCharge(char *path)
{
  int tmp = 0;
  char *res = NULL;
  off_t fileSize = 0;
  ssize_t ret = 0;
  ssize_t read_byte = 0;
  ssize_t to_read_byte = BUFFER;

  DERROR("open", (tmp = open(path, O_RDONLY)) == -1, perror("open"),
	 return NULL);
  DERROR("lseek", (fileSize = lseek(tmp, 0, SEEK_END)) == -1,
	 perror("lseek");
  DERROR("close", close(tmp) == -1, perror("close"), (void) NULL);
  ,
    return NULL);
  DERROR("lseek", lseek(tmp, 0, SEEK_SET) == -1,
	 perror("lseek");
  DERROR("close", close(tmp) == -1, perror("close"), (void) NULL);
  ,
    return NULL);
  DERROR("malloc", (res = malloc(sizeof(*res) * fileSize)) == NULL,
	 perror("malloc");
  DERROR("close", close(tmp) == -1, perror("close"), (void) NULL);
  ,
    return NULL);

  for (; fileSize > 0; fileSize -= to_read_byte)
  {
    if (fileSize < to_read_byte)
      to_read_byte = fileSize;
    ret = read(tmp, res + read_byte, to_read_byte);
    DERROR("read", ret == -1,
	   perror("read");
    if (res != NULL)
    {
      free(res);
      res = NULL;
    },
      break);
    read_byte += ret;
  }
  DERROR("close", close(tmp) == -1, (void) NULL, (void) NULL);
  return res;
}

static off_t fileSizeO(char *path)
{
  int tmp = 0;
  off_t fileSize = 0;

  DERROR("open", (tmp = open(path, O_RDONLY)) == -1, perror("open"),
	 return -1);
  DERROR("lseek", (fileSize = lseek(tmp, 0, SEEK_END)) == -1, perror("lseek"),
	 (void) NULL);
  DERROR("close", close(tmp) == -1, (void) NULL, (void) NULL);
  return fileSize;
}

static void fileWrite(char *path, char *chaine, off_t taille)
{
  int tmp = 0;
  off_t size_file = taille;
  ssize_t ret = 0;
  ssize_t write_byte = 0;
  ssize_t to_write_byte = BUFFER;

  DERROR("open", (tmp = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0664)) == -1,
	 perror("open"), return);

  for (; size_file > 0; size_file -= to_write_byte)
  {
    if (size_file < to_write_byte)
      to_write_byte = size_file;

    ret = write(tmp, chaine + write_byte, to_write_byte);
    DERROR("write", ret == -1, perror("write"),
	   break);
    write_byte += ret;
  }

  DERROR("close", close(tmp) == -1, (void) NULL, (void) NULL);
  return;
}

#ifdef DEBUG
static void testXor(void)
{
  int i = 0;
  char bits[4][2] = {{0, 0},
  {0, 1},
  {1, 0},
  {1, 1}};

  for (; i < 4; i++)
    printf("%d xor %d -> %d\n", bits[i][0],
	   bits[i][1], xor(bits[i][0], bits[i][1]));
  return;
}

static void testCrypt(void)
{
  char *test = "Bonjour";
  char *res1 = fcrypt(test, strlen(test));

  DERROR("fcrypt", res1 == NULL, (void) NULL,
	 return);
  char *res2 = fdecrypt(res1, strlen(test));

  DERROR("fdecrypt", res2 == NULL, if (res1 != NULL)
	 {
    free(res1);
    res1 = NULL;
  },
    return);
  printf("%s -> %s -> %s\n", test, res1, res2);
  free(res1);
  free(res2);
}

static void testOpen(void)
{
  char *test = fileCharge("ttt.c");

  DERROR("fileCharge", test == NULL, (void) NULL,
	 return);
  printf("%s\n", test);
  free(test);
}

static void testWrite(void)
{
  char *in = fileCharge("ttt.c");

  DERROR("fileCharge", in == NULL, (void) NULL,
	 return);
  int taille = fileSizeO("ttt.c");

  DERROR("fileSizeO", taille == -1, if (in != NULL)
	 {
    free(in);
    in = NULL;
  },
    return);
  fileWrite("truc.c", in, taille);
  free(in);
}
#endif

static int usage(char *s)
{
  fprintf(stderr, "Usage : %s -[e|d] <fileIn> <fileOut> <nbCrypt>\n", s);
  return 1;
}

int main(int argc, char **argv)
{
#ifdef DEBUG
  testXor();
  testCrypt();
  testOpen();
  testWrite();
#endif
  if (argc != 5 || argv[1][0] != '-')
    return usage(argv[0]);

  int i = 0;
  int nb = 0;
  char *in = NULL;
  char *res = NULL;

  DERROR("atoi", (nb = atoi(argv[4])) <= -1, (void) NULL,
	 return usage(argv[0]));

  switch (argv[1][1])
  {
  case 'e':
    {
      int taille = 0;

      printf("1.Encrypt\n");
      in = fileCharge(argv[2]);
      DERROR("fileCharge", in == NULL, (void) NULL,
	     break);
      DERROR("fileSizeO", (taille = fileSizeO(argv[2])) == -1,
	     if (in != NULL)
	     {
	free(in);
	in = NULL;
      },
	break);
      for (i = 0; i < nb; i++)
      {
	res = fcrypt(in, taille);
	DERROR("fcrypt", res == NULL, if (in != NULL)
	       {
	  free(in);
	  in = NULL;
	},
	  break);
	free(in);
	in = res;
      }
      fileWrite(argv[3], res, taille);
      printf("2.Encrypted\n");
      break;
    }
  case 'd':
    {
      int taille = 0;

      printf("1.Decrypt\n");
      in = fileCharge(argv[2]);
      DERROR("fileCharge", in == NULL, (void) NULL,
	     break);
      DERROR("fileSizeO", (taille = fileSizeO(argv[2])) == -1,
	     if (in != NULL)
	     {
	free(in);
	in = NULL;
      },
	break);
      for (i = 0; i < nb; i++)
      {
	res = fdecrypt(in, taille);
	DERROR("fcrypt", res == NULL, if (in != NULL)
	       {
	  free(in);
	  in = NULL;
	},
	  break);
	free(in);
	in = res;
      }
      fileWrite(argv[3], res, taille);
      printf("2.Decrypted\n");
      break;
    }
  default:
    {
      usage(argv[0]);
      break;
    }
  }
  if (res != NULL)
    free(res);
  return 0;
}
