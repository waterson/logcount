#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <openssl/md5.h>

#include "logcount.h"

struct root_list {
  int nhash;
  double *roots;
  struct root_list *next;
};

static struct root_list *root_cache;

static double *
get_roots(int nhash)
{
  struct root_list *p = root_cache;
  while (p) {
    if (p->nhash == nhash)
      return p->roots;
  }

  p = (struct root_list *) malloc(sizeof(struct root_list));
  p->roots = calloc(nhash, sizeof(double));

  double inve = 1.0 / exp(1);
  int i;
  for (i = 0; i < nhash; ++i)
    p->roots[i] = pow(2.0, inve + ((double) i) / ((double) nhash));

  p->next = root_cache;
  root_cache = p->next;

  return p->roots;
}

/*
 * Computes "nhash" 32-bit hashes into "digest" from "data".
 */
static void
hash(int nhash, unsigned char *digest, unsigned char *data, int datalen)
{
  int nbytes = sizeof(int) * (nhash + sizeof(int) - nhash % sizeof(int));
  unsigned char *buf = malloc(nbytes), *p = buf, *end = buf + nbytes;

  MD5(p, datalen, data);
  for (p += 16; p < end; p += 16)
    MD5(p, 16, p - 16);

  for (p = buf; p < end; p += sizeof(int)) {
    int *q = (int *) p, n = *q;
    *q = n ^ (n & (n-1));
  }

  memcpy(digest, buf, nhash * sizeof(int));
  free(buf);
}

/* Returns the index of the lowest unset bit in "n". */
static int
lowest_unset_bit_index(int n)
{
  int i;
  for (i = 0; n & 1 && i <= sizeof(int) * 8; ++i, n >>= 1)
    ;
  return i;
}

static void
combine(int *dst, const int *src, int nhash)
{
  const int *end = src + nhash;
  for ( ; src != end; ++src, ++dst)
    *dst |= *src;
}

void
logcount_init(struct logcount *lc, int nhash)
{
  lc->nhash = nhash;
  lc->hashes = calloc(nhash, sizeof(int));
}

void
logcount_finish(struct logcount *lc)
{
  free(lc->hashes);
}

void
logcount_add(struct logcount *dst, const unsigned char *data, size_t datalen)
{
  int nbytes = sizeof(int) * (dst->nhash + sizeof(int) - dst->nhash % sizeof(int));
  unsigned char *buf = malloc(nbytes), *p = buf, *end = buf + nbytes;

  MD5(data, datalen, p);
  for (p += 16; p < end; p += 16)
    MD5(p-16, 16, p);

  for (p = buf; p < end; p += sizeof(int)) {
    int *q = (int *) p, n = *q;
    *q = n ^ (n & (n-1));
  }

  combine(dst->hashes, (int *) buf, dst->nhash);
  free(buf);
}

int
logcount_combine(struct logcount *dst, const struct logcount *src)
{
  if (src->nhash != dst->nhash)
    return -1;

  combine(dst->hashes, src->hashes, src->nhash);
  return 0;
}

int
logcount_value(const struct logcount *lc)
{
  const int *hash = lc->hashes;
  int count = 0;

  double *roots = get_roots(lc->nhash);
  int i;

  for (i = lc->nhash; --i >= 0; ++hash)
    count += lowest_unset_bit_index(*hash);

  return count ? (1 << (count / lc->nhash)) * roots[count % lc->nhash] : 0;
}
