#include <stdio.h>

void otrisov(int xshar, int yshar, int first, int second, int height, int width, char mas[][width]);
void dvig_mych(int x1, int y1, int x2, int y2, int *xshar, int *yshar, int *speed_x, int *speed_y);
void otrisov_poly(int x1, int x2, int y1, int y2, int ysetka, int height, int width, char mas[][width]);
void chet(int *yshar, int *xshar, int *speed_x, int x1, int x2, int *first, int *second);
void dvig_rack(int key, int *x1, int *x2);
void winner(int a, int b);
int main() {
    const int width = 81, height = 25;
    char mas[height][width];
    int x1 = 12, x2 = 12;
    int speed_y = 1, speed_x = 1;
    int xshar = 12, yshar = 40;
    int first = 0, second = 0;
    const int y1 = 3, y2 = 76, ysetka = 40;
    char key;

    printf(
            "To Start the Game enter \"x\"\n\nTo Exit the Game enter \"o\"\n\nTo exit the menu enter any else "
            "button\n\n..");
        scanf("%c", &key);
    if (key == 'x') {
        
        while (first != 5 && second != 5 && key != 'o') {
            dvig_rack(key, &x1, &x2);
            otrisov_poly(x1, x2, y1, y2, ysetka, height, width, mas);
            if (key == ' ' || key == 'a' || key == 'z' || key == 'm' || key == 'k') {
                dvig_mych(x1, y1, x2, y2, &xshar, &yshar, &speed_x, &speed_y);
            }
            chet(&yshar, &xshar, &speed_x, x1, x2, &first, &second);
            otrisov(xshar, yshar, first, second, height, width, mas);
            
            key = getc(stdin);
        }
        if (first == 5 || second == 5) {
            winner(first, second);
        } }
    else if (key == 'o') return 0;
    return 0;
}

void chet(int *yshar, int *xshar, int *speed_x, int x1, int x2, int *first, int *second) {
    if (*yshar == 1) {
        *xshar = x2 + 1;
        *yshar = 75;
        *second += 1;
    }
    if (*yshar == 79) {
        *xshar = x1 + 1;
        *yshar = 4;
        *speed_x *= -1;
        *first += 1;
    }
}

void dvig_rack(int key, int *x1, int *x2) {
    if (key == 'a' && *x1 > 1) *x1 -= 1;
    if (key == 'z' && *x1 < 21) *x1 += 1;

    if (key == 'k' && *x2 > 1) *x2 -= 1;
    if (key == 'm' && *x2 < 21) *x2 += 1;
}

void dvig_mych(int x1, int y1, int x2, int y2, int *xshar, int *yshar, int *speed_x, int *speed_y) {
    if (*xshar == 1 || *xshar == 23) {
        *speed_x *= -1;
        *xshar += *speed_x;
        *yshar += *speed_y;
    } else {
        *xshar += *speed_x;
        *yshar += *speed_y;
    }

    // otbivaetsa ot levoi raketki
    if ((*xshar == x1 && *yshar == y1) || (*xshar == x1 + 1 && *yshar == y1) ||
        (*xshar == x1 + 2 && *yshar == y1)) {
        *speed_y *= -1;
        *xshar += *speed_x;
        *yshar += 2 * *speed_y;
    }

    // otbivaetsa ot pravoi raketki
    if ((*xshar == x2 && *yshar == y2) || (*xshar == x2 + 1 && *yshar == y2) ||
        (*xshar == x2 + 2 && *yshar == y2)) {
        *speed_y *= -1;
        *xshar += *speed_x;
        *yshar += 2 * *speed_y;
    }
}

void otrisov_poly(int x1, int x2, int y1, int y2, int ysetka, int height, int width, char mas[][width]) {
    int i;
    sprintf(mas[0], "################################################################################");
    for (i = 1; i < 24; i++)
        sprintf(mas[i], "#                                                                              #");
    sprintf(mas[24], "################################################################################");

    // levay raketka
    for (i = x1; i < x1 + 3; i++) {
        mas[i][y1] = '|';
    }

    // pravay raketka
    for (i = x2; i < x2 + 3; i++) {
        mas[i][y2] = '|';
    }

    for (i = 1; i < height - 1; i++) {
        mas[i][ysetka] = '|';
    }
}

void otrisov(int xshar, int yshar, int first, int second, int height, int width, char mas[][width]) {
    mas[xshar][yshar] = '*';
    int i;
    for (i = 0; i < height; i++) printf("%s\n", mas[i]);
    printf("============\n   %d : %d\n============\n", first, second);
}
void winner(int a, int b) {
    int c;
    if (a > b) c = 1;
    if (b > a) c = 2;
    printf("\t\t\tC O N G R A T U L A T I O N S\n\t\t\t   PLAYER %d IS A WINNER!!!\n", c);
}

