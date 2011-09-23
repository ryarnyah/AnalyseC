#include <stdio.h>
#include <stdlib.h>

unsigned quotient_tq(unsigned a, unsigned b)
{
  unsigned quotient = 0;

  while (a >= b)
  {
    a -= b;
    quotient++;
  }

  return quotient;
}

unsigned quotient_rj(unsigned a, unsigned b)
{
  int quotient = 0;

  if (a < b)
    return quotient;

  do
  {
    a -= b;
    quotient++;
  } while (a >= b);

  return quotient;
}

unsigned quotient_for(unsigned a, unsigned b)
{
  int quotient = 0;

  for (; a >= b; quotient++)
    a -= b;

  return quotient;
}

unsigned pgcd_iter(unsigned a, unsigned b)
{
  while (a != b)
  {
    if (a > b)
      a -= b;
    if (a < b)
      b -= a;
  }
  return a;
}

unsigned pgcd_rec(unsigned a, unsigned b)
{
  if (a > b)
    return pgcd_rec(a - b, b);
  if (a < b)
    return pgcd_rec(b - a, a);
  return a;
}

unsigned ppcm(unsigned a, unsigned b)
{
  return (a * b) / pgcd_rec(a, b);
}

unsigned long long factorielle_iter(unsigned n)
{
  unsigned long long resultat = 1;

  for (int i = 1; i <= n; i++)
    resultat *= i;
  return resultat;
}

unsigned long long factorielle_rec(unsigned n)
{
  return (n == 0 || n == 1) ? 1 : n * factorielle_rec(n - 1);
}

unsigned calculer_taille(unsigned taille, unsigned n)
{
  while (n >= taille)
    taille *= 2;
  return taille;
}

unsigned fibonacci(unsigned n)
{
  static unsigned *t = NULL;
  static unsigned taille = 4;
  static unsigned dernier_n_c = 0;

  if (n >= taille)
  {
    taille = calculer_taille(taille, n);
    realloc(t, taille * sizeof(*t));
  }
  if (dernier_n_c == 0)
  {
    if (t == NULL)
      t = malloc(taille * sizeof(*t));
    *t = *(t + 1) = 1;
    dernier_n_c = 2;
  }
  for (; dernier_n_c <= n; dernier_n_c++)
    *(t + dernier_n_c) = *(t + dernier_n_c - 1) + *(t + dernier_n_c - 2);

  return *(t + n);
}

void usage(char *s)
{
  fprintf(stderr, "Usage : %s [nbr] [nbr]\n", s);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
  if (argc != 3)
    usage(argv[0]);
  printf("Quotient de %d et %d : %u ,%u ,%u\n", atoi(argv[1]), atoi(argv[2]), quotient_for(atoi(argv[1]), atoi(argv[2])), quotient_tq(atoi(argv[1]), atoi(argv[2])), quotient_rj(atoi(argv[1]), atoi(argv[2])));
  printf("PGCD de %d et %d : %u, %u\nPPCM : %u\n", atoi(argv[1]), atoi(argv[2]), pgcd_iter(atoi(argv[1]), atoi(argv[2])), pgcd_rec(atoi(argv[1]), atoi(argv[2])), ppcm(atoi(argv[1]), atoi(argv[2])));
  printf("Factorielle de %d : %llu %llu\n", atoi(argv[1]), factorielle_iter(atoi(argv[1])), factorielle_rec(atoi(argv[1])));
  printf("Fibonacci de %d = %u\nFibonacci de %d = %u\n", atoi(argv[1]), fibonacci(atoi(argv[1])), atoi(argv[2]), fibonacci(atoi(argv[2])));
  return EXIT_SUCCESS;
}
