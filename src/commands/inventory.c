#include <stdio.h>
#include "../modules/adt.h"

#ifndef GADGET_UNDEF
#define GADGET_UNDEF '0'
#endif

/* Proses: Menampilkan antarmuka pemakaian gadget */
/* I.S. Banyak gadget dalam inventory tidak melebihi capacity */
/* F.S Jika pemakaian berhasil, gadget yang terpakai menghilang dari inventory */
/*     Jika pemakaian gagal, menuliskan pesan */
void inventory(ListGadget *l, int *time, int *incTime, int *saveTime, Stack *s) {
    int command;
    Gadget val;
    displayListGadget(*l);
    printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali): ");
    startWord();
    command = charToInt(currentWord);
    /* Sesuai Command*/
    if (GADGET_ELMT(*l, command-1) != GADGET_UNDEF) {
        deleteGadget(l, command-1, &val);
        if (val == 'A') {
            if (TYPE(ITEM(TOP(*s))) == 'P') {
                PTIME(TOP(*s)) += *time - TIME(TOP(*s));
            }
            printf("Kain Pembungkus Waktu berhasil digunakan\n");
        } else if (val == 'B') {
            increase2TimesTasCapacity(s);
            printf("Senter Pembesar berhasil digunakan\n");
        } else if (val == 'C') {
            *saveTime = *incTime;
            *incTime = 0;
            printf("Pintu Kemana Saja berhasil digunakan\n");
        } else {
            if (*time > 50) {
                *time -= 50;
            } else {
                *time = 0;
            }
            printf("Mesin Waktu berhasil digunakan\n");
        }
    }
    else {
		printf("Tidak ada Gadget yang dapat digunakan!\n");
	}
}
