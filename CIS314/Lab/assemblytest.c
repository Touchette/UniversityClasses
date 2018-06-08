void swap(int *xp, int *yp) {
    int t0 = *xp;
    int t1 = *yp;
    *xp = t1;
    *yp = t0;
}

void asemswap() {
    __asm__ __volatile__(
        movl 8(%ebp), %edx;   // edx = xp
        movl 12(%ebp), %ecx;  // ecx = yp
        movl (%edx), %ebx;    // ebx = *xp (t0)
        movl (%ecx), %eax;    // eax = *yp (t1)
        movl %eax, (%edx);    // *xp = t1
        movl %ebx, (%ecx);    // *yp = t0
        );
}