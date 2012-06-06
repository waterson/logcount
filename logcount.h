#ifndef logcount_h__
#define logcount_h__

#include <stddef.h>

struct logcount {
  int nhash;
  int *hashes;
};

/* Initialize a new logcount with the specified number of hashes. */
void
logcount_init(struct logcount *lc, int nhashes);

/* Finish the logcount and free extra storage associated with it. */
void
logcount_finish(struct logcount *lc);

/* Add data to the logcount. */
void
logcount_add(struct logcount *lc, const unsigned char *data, size_t datalen);

/* Combine two logcounts. */
int
logcount_combine(struct logcount *dst, const struct logcount *src);

/* Return the count value of a logcount. */
int
logcount_value(const struct logcount *lc);

#endif /* logcount_h__ */
