#define ES_MIN(a, b) ((a) < (b) ? (a) : (b))

#if defined(__linux__) || defined(__linux) || defined(linux)
#define MAXTHREADNAMEBUFSIZ 16
#define MAXTHREADNAMELEN (MAXTHREADNAMEBUFSIZ - 1)
#elif defined(__APPLE__) || defined(__MACH__)
#define MAXTHREADNAMEBUFSIZ 64
#define MAXTHREADNAMELEN (MAXTHREADNAMEBUFSIZ - 1)
#endif
