/*see README for original credits */

#ifndef BACK_TRACK_H
#define BACK_TRACK_H

#define MAXCANDIDATES   100		/* max possible next extensions */
#define NMAX            100		/* maximum solution size */

typedef char* data;			/* type to pass data to backtrack */

void back_track(int a[], int k, data input);

#endif /* BACK_TRACK_H */

