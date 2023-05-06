#include <stdio.h>

void GradTransform(unsigned cor_init, unsigned cor_end, int num_step)
{
    unsigned diff = (cor_end - cor_init) / num_step;     // simply divide the difference
    int i = 0;
    for (i = 0; i < num_step; i++)
    {
        unsigned value = cor_init + diff * i;     
        printf("0x%06X\n", value);
    }

}

int main()
{
    unsigned init = 0x00001A;
    unsigned end = 0xFF001A;
    GradTransform(init, end, 3);
 
    return 0;
}
