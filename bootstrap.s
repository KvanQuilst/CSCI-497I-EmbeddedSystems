.global __reset
__reset:
  ldr   r0, .L3+0  //LMA
  ldr   r1, .L3+4  //VMA
  ldr   r2, .L3+8  //END
  b .L5
.L4:                    // Copy Data to RAM
  ldr   r3, [r0]
  str   r3, [r1]
  add   r0, #4
  add 	r1, #4
.L5:               
  cmp	  r1, r2
  bne	  .L4
  ldr	  r0, .L3+12      // Zero BSS
  ldr   r2, .L3+16
  eor   r3, r3
  b     .L7
.L6:
  str   r3, [r0]
  add   r0, #4
.L7:
  cmp   r0, r2
  bne   .L6
.L8:                    // Change SP to PSP
  ldr   r0, .L3+28      // Load location of __main__
  ldr   r0, [r0]    // Load __PSP (top of __main__'s stack)
  msr   psp, r0         // Set hardware psp to __PSP
  mrs   r0, control     // Move control into r0
  mov   r1, #2
  orr   r0, r1
  msr   control, r0
  isb
.L9:                      // Run Constructors
  ldr   r6, .L3+20
  ldr   r7, .L3+24
  b     .L11
.L10:
  ldr   r0, [r6]
  blx   r0
  add   r6, #4
.L11:
  cmp   r6, r7
  bne   .L10
  bl    reset
  .align 2
.L3:
  .word __DATA_LMA        //0
  .word __DATA_VMA        //4
  .word __DATA_END        //8
  .word __BSS_VMA         //12
  .word __BSS_END         //16
  .word __INIT_ARRAY_VMA  //20
  .word __INIT_ARRAY_END  //24
  .word __PSP             //28
