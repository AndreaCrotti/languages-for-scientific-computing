#define TS ((double) clock())/CLOCKS_PER_SEC
#define PRECISION ".6f"

void print_double_matrix(double *, int);
void print_double_vector(double *, int);

double *gen_rand_tril(int);
double *gen_rand_vector(int);

// tries to write to a .m file the square matrix given
int matrix_to_matlab(double *, int, char *);
void print_vector_to_matlab(FILE *, double *, int);

// creates a random matrix and writes it to filename
int test_write_to_m(int, char *);

//void print_plot_generator(FILE *, graph_options *);

/* typedef struct _graph_options */
/* { */
/*   char *title; */
/*   double x0; */
/*   double x1; */
/*   double y0; */
/*   double y1; */
/*   char *legend; */
/*   double *values; */
/* } graph_options; */
