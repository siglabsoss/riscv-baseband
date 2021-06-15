#ifndef __TABLE_H__
#define __TABLE_H__

// seems like this type is ununsed (it is set but not checked)
typedef enum {
TABLE_T_MAP,
TABLE_T_SOURCE,
TABLE_T_DEST,
TABLE_T_CONST,
TABLE_T_SCHEDULE,
TABLE_T_TEMP,
TABLE_T_GARBAGE
} Table_type;

typedef struct {
	Table_type type;
	int addr;  // dma pointer
	int len;
} Table;  

#endif