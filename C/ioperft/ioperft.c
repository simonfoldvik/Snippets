/**
 *  Author: Simon Foldvik
 * Created: Sun 24 May 2020
 * Updated: Sat 20 Jun 2020
 *
 * Purpose
 * -------
 * This program compares IO read/write performance of the read/write syscalls
 * as compared to the fread/fwrite library functions.
 *
 * Conclusion
 * ----------
 * The library functions fread, fwrite seem to have better interfaces, and they
 * take care of buffering for you; buffering may also be configured with the
 * setvbuf family of functions, if required. In spite of this, the read, write
 * system calls appear to outperform the library functions with the same buffer
 * sizes, from which we may conclude that they yield better IO performance.
 *
 * Samples with various optimization levels
 * ----------------------------------------
 * Below are some sample results from running the program,
 * copying a 1.17 GB file, with various optimization flags
 * given to the compiler.
 *
 * Compiler: gcc (compilation flags are shown in the samples themselves)
 * Hardware: Apple MacBook Pro Retina 13" (Early 2015);
 *           3.1 GHz Dual-Core Intel Core i7 processor with hyperthreading;
 *           16 GB at 1867 MHz DDR3 memory.
 * Legend:
 *     buf:    buffer size
 *     rw:     clocktime for read/write syscalls
 *     frw:    clocktime for fread/fwrite library functions
 *     win:    which method performed better
 *     frw/rw: performance ratio
 * Samples:
 *
 * flags: -std=c18
 * buf         rw          frw         win         frw/rw    
 * 512         8668965     9608687     rw          1.108     
 * 1024        4907219     5136448     rw          1.047     
 * 2048        2719952     2763761     rw          1.016     
 * 4096        1553081     1946849     rw          1.254     
 * 8192        1169266     1236247     rw          1.057     
 * 16384       737920      1128531     rw          1.529     
 * 32768       566447      953583      rw          1.683     
 * 65536       499500      768809      rw          1.539     
 * 131072      455673      691734      rw          1.518     
 * 262144      450933      698708      rw          1.549     
 * 
 * flags: -std=c18 -O0
 * buf         rw          frw         win         frw/rw    
 * 512         9916096     10833920    rw          1.093     
 * 1024        5022649     5515348     rw          1.098     
 * 2048        2661590     2851168     rw          1.071     
 * 4096        1570135     1761279     rw          1.122     
 * 8192        1007129     1233297     rw          1.225     
 * 16384       697828      921605      rw          1.321     
 * 32768       546932      765198      rw          1.399     
 * 65536       476732      694442      rw          1.457     
 * 131072      446689      675537      rw          1.512     
 * 262144      438393      654298      rw          1.492     
 * 
 * flags: -std=c18 -O1
 * buf         rw          frw         win         frw/rw    
 * 512         9828217     10968340    rw          1.116     
 * 1024        5057585     5387605     rw          1.065     
 * 2048        2721236     2916188     rw          1.072     
 * 4096        1538739     1773246     rw          1.152     
 * 8192        1007225     1187797     rw          1.179     
 * 16384       702008      963927      rw          1.373     
 * 32768       547777      764089      rw          1.395     
 * 65536       473180      704193      rw          1.488     
 * 131072      445665      644740      rw          1.447     
 * 262144      429703      642588      rw          1.495     
 * 
 * flags: -std=c18 -O2
 * buf         rw          frw         win         frw/rw    
 * 512         9753084     10889607    rw          1.117     
 * 1024        4999699     5387559     rw          1.078     
 * 2048        2739442     2906426     rw          1.061     
 * 4096        1553506     1879611     rw          1.210     
 * 8192        1006143     1217617     rw          1.210     
 * 16384       713745      969604      rw          1.358     
 * 32768       551237      782644      rw          1.420     
 * 65536       481931      738096      rw          1.532     
 * 131072      449748      653663      rw          1.453     
 * 262144      434000      640775      rw          1.476     
 * 
 * flags: -std=c18 -O3
 * buf         rw          frw         win         frw/rw    
 * 512         9931546     10879465    rw          1.095     
 * 1024        5006114     5361792     rw          1.071     
 * 2048        2692689     2915911     rw          1.083     
 * 4096        1588415     1784513     rw          1.123     
 * 8192        975225      1235860     rw          1.267     
 * 16384       710825      1001364     rw          1.409     
 * 32768       555574      787975      rw          1.418     
 * 65536       481787      718112      rw          1.491     
 * 131072      465487      685390      rw          1.472     
 * 262144      429819      657332      rw          1.529     
 * 
 * flags: -std=c18 -Ofast
 * buf         rw          frw         win         frw/rw    
 * 512         9777510     10769277    rw          1.101     
 * 1024        5046921     5621827     rw          1.114     
 * 2048        2752353     2766000     rw          1.005     
 * 4096        1583803     1739288     rw          1.098     
 * 8192        1009813     1259131     rw          1.247     
 * 16384       702636      907137      rw          1.291     
 * 32768       552905      798073      rw          1.443     
 * 65536       502458      710613      rw          1.414     
 * 131072      452900      688680      rw          1.521     
 * 262144      444376      629453      rw          1.416     
 * 
 * flags: -std=c18 -Os
 * buf         rw          frw         win         frw/rw    
 * 512         9766216     10921564    rw          1.118     
 * 1024        4999990     5335150     rw          1.067     
 * 2048        2723559     2920267     rw          1.072     
 * 4096        1515224     1793455     rw          1.184     
 * 8192        993444      1261018     rw          1.269     
 * 16384       707516      926622      rw          1.310     
 * 32768       555517      804030      rw          1.447     
 * 65536       482128      702813      rw          1.458     
 * 131072      451296      670300      rw          1.485     
 * 262144      448168      640381      rw          1.429     
 * 
 * flags: -std=c18 -Oz
 * buf         rw          frw         win         frw/rw    
 * 512         9761264     10756126    rw          1.102     
 * 1024        4854721     5320203     rw          1.096     
 * 2048        2717321     2930351     rw          1.078     
 * 4096        1572744     1842328     rw          1.171     
 * 8192        998155      1227962     rw          1.230     
 * 16384       712666      995281      rw          1.397     
 * 32768       549443      790063      rw          1.438     
 * 65536       476452      724277      rw          1.520     
 * 131072      467977      678063      rw          1.449     
 * 262144      428544      651814      rw          1.521   
 *
 * flags: -std=c18 -Og
 * buf         rw          frw         win         frw/rw    
 * 512         9623112     10721303    rw          1.114     
 * 1024        4969062     5329863     rw          1.073     
 * 2048        2709964     2869302     rw          1.059     
 * 4096        1505598     1843173     rw          1.224     
 * 8192        1018169     1324766     rw          1.301     
 * 16384       706654      922621      rw          1.306     
 * 32768       551381      796961      rw          1.445     
 * 65536       484549      703908      rw          1.453     
 * 131072      454993      652789      rw          1.435     
 * 262144      433624      627489      rw          1.447     
*/

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#define EMPTY_READ_WRITE_PASSES 10

/* Performs an empty fread on the given file. */
static void femptyread(const char *src)
{
    /* Open file. */
    FILE *fp = fopen(src, "rb");
    if (!fp) {
        fprintf(stderr, "femptyread: failed to open %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Read file and do nothing with its contents. */
    uint8_t buffer[BUFSIZ];
    while (fread((void *) buffer, sizeof(uint8_t), BUFSIZ, fp) > 0U) {
        /* Q: Is this the right place to check for read errors on fp? */
        if (ferror(fp)) {
            fprintf(stderr, "femptywrite: error reading %s\n", src);
            perror("Reason");
            exit(EXIT_FAILURE);
        }
    }
    /* Check for errors. */
    if (ferror(fp) || !feof(fp)) {
        fprintf(stderr, "femptywrite: error reading %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Perform cleanup operations. */
    fclose(fp);
}

/* Performs an empty fwrite on the specified file. */
static void femptywrite(const char *dst)
{
    FILE *fp = fopen(dst, "wb");
    if (!fp) {
        fprintf(stderr, "femptywrite: error creating %s\n", dst);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

/* Copies file src -> dst using read/write syscalls and the given buffer size. */
static void readwrite(const char *src, const char *dst, const size_t bufsize)
{
    /* Open the respective files for reading/writing. */
    const int fd_src = open(src, O_RDONLY);
    struct stat srcstat;
    if (stat(src, &srcstat) == -1) {
        fprintf(stderr, "readwrite: stat call error on %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    const int fd_dst = open(dst, O_WRONLY | O_CREAT, srcstat.st_mode);
    if (fd_src == -1) {
        fprintf(stderr, "readwrite: failed to open %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    if (fd_dst == -1) {
        fprintf(stderr, "readwrite: failed to create %s\n", dst);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Perform read/write operations. */
    ssize_t nread;
    uint8_t buffer[bufsize];
    while ((nread = read(fd_src, (void *) buffer, bufsize)) > 0) {
        /* Successful read operation. */
        if (write(fd_dst, (const void *) buffer, nread) != nread) {
            /* Write error. */
            fprintf(stderr, "readwrite: write error on %s\n", dst);
            perror("Reason");
            exit(EXIT_FAILURE);
        }
    }
    /* Check for errors. */
    if (nread == -1) {
        fprintf(stderr, "readwrite: read error on %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Perform cleanup operations. */
    close(fd_src);
    close(fd_dst);
}

/* Copies file src -> dst using fread/fwrite library functions and the given buffer size. */
static void freadwrite(const char *src, const char *dst, const size_t bufsize)
{
    /* Open the respective file for reading/writing. */
    FILE *fp_src = fopen(src, "rb");
    FILE *fp_dst = fopen(dst, "wb");
    if (!fp_src) {
        fprintf(stderr, "freadwrite: failed to open %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    if (!fp_dst) {
        fprintf(stderr, "freadwrite: failed to create %s\n", dst);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Prepare IO. */
    size_t nread;
    uint8_t buffer[bufsize];
    if (setvbuf(fp_src, NULL, _IOFBF, bufsize)) {
        fprintf(stderr, "freadwrite: setvbuf failed on src: %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    if (setvbuf(fp_dst, NULL, _IOFBF, bufsize)) {
        fprintf(stderr, "freadwrite: setvbuf failed on dst: %s\n", dst);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Perform IO. */
    while ((nread = fread((void *) buffer, sizeof(uint8_t), bufsize, fp_src)) > 0U) {
        /* Q: Is this the right place to check for read errors on fp_src? */
        if (ferror(fp_src)) {
            fprintf(stderr, "freadwrite: read error on %s\n", src);
            perror("Reason");
            exit(EXIT_FAILURE);
        }
        /* Successful read operation. */
        if (fwrite((const void *) buffer, sizeof(uint8_t), nread, fp_dst) != nread) {
            /* Write error. */
            fprintf(stderr, "freadwrite: write error on %s\n", dst);
            perror("Reason");
            exit(EXIT_FAILURE);
        }
    }
    /* Check for errors. */
    if (ferror(fp_src) || !feof(fp_src)) {
        fprintf(stderr, "freadwrite: read error on %s\n", src);
        perror("Reason");
        exit(EXIT_FAILURE);
    }
    /* Perform cleanup operations. */
    fclose(fp_src);
    fclose(fp_dst);
}

/* Main program: entry point. */
int main(int argc, char *argv[])
{
    /* Fetch src, dst on the command line. */
    if (argc != 3) {
        puts("Usage: ioperft <src> <dst>");
        return 0;
    }
    const char *src = argv[1];
    const char *dst = argv[2];
    if (access(dst, F_OK) == 0) {
        fprintf(stderr, "dst already exists: %s\n", dst);
        fprintf(stderr, "Aborting to prevent accidental overwrite!\n");
        return 0;
    }

    /* Setup tests. */
    const size_t sizes[] = {
          512UL,  1024UL,  2048UL,   4096UL,   8192UL,
        16384UL, 32768UL, 65536UL, 131072UL, 262144UL
    };
    const size_t nsizes = sizeof(sizes)/sizeof(size_t);
    clock_t times[nsizes];
    clock_t ftimes[nsizes];

    /* Perform empty reads/writes to warm up. */
    for (int i = 0; i < EMPTY_READ_WRITE_PASSES; ++i) {
        femptyread(src);
        femptywrite(dst);
    }

    /* Execute tests. */
    size_t size;
    clock_t start;
    for (size_t i = 0UL; i < nsizes; ++i) {
        size = sizes[i];
        /* readwrite */
        start = clock();
        readwrite(src, dst, size);
        times[i] = clock() - start;
        /* freadwrite */
        start = clock();
        freadwrite(src, dst, size);
        ftimes[i] = clock() - start;
    }

    /* Report results. */
    printf("%-10s  %-10s  %-10s  %-10s  %-10s\n", "buf", "rw", "frw", "win", "frw/rw");
    for (size_t i = 0UL; i < nsizes; ++i)
        printf("%-10lu  %-10lu  %-10lu  %-10s  %-10.3f\n", sizes[i], times[i], ftimes[i],
            (times[i] >= ftimes[i]) ? "frw" : "rw", ((double) ftimes[i])/((double) times[i]));
    return 0;
}
