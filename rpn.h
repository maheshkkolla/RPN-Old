typedef struct status Status;

struct status {
  int error;
  int result;
};

Status evaluate(char *expression);