.global __reset:
  ldr   r0, .L3+0  //LMA
  ldr   r1, .L3+4  //VMA
  ldr   r2, .L3+8  //END
  b .L5
.L4:
  ldr   r3, [r0]
  str   r3, [r1]
  adds  r0, #4
  adds	r0, #4
.L5:
  cmp	r1, r2
  bne	.L4
  ldr	r0, .L3 + 12
  ldr   r2, .L3 + 16
  eors  r3, r3
  b     .L7
.L6:
  str   r3, [r0]
  adds  r0, #4
.L7:
  cmp   r0, r2
  bne   .L6
  bl    reset
  .align 2
.L3:
  .word __DATA_LMA  //0
  .word __DATA_VMA  //4
  .word __DATA_END  //8
  .word __BSS_VMA   //12
  .word __BSS_END   //16
