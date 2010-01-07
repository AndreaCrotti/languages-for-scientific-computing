#define TS ((double) clock())/CLOCKS_PER_SEC

void print_double_matrix(double *, int);

void print_double_vector(double *, int);

double *gen_rand_tril(int);
double *gen_rand_vector(int);

// tries to write to a .m file the square matrix given
int write_to_m(double *, int, char *);

// creates a random matrix and writes it to filename
int test_write_to_m(int, char *);

