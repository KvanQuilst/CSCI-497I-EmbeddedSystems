.global __irq
__irq:
  mov   r0, r14
  ldr   r1, .L3 + 8
  cmp   r0, r1
  bne   .L0
  CPSID i           // Turn off interrupts
  mrs   r0, PSP     // Get PSP
  mov   r1, r13     // Save MSP
  mov   r13, r0     
  push  {r4-r7}
  mov   r4, r8
  mov   r5, r9
  mov   r6, r10
  mov   r7, r11
  push  {r4-r7}
  mov   r0, r13     // Save new PSP
  mov   r13, r1     // Restore MSP
  CPSIE i           // Enable interrupts
  ldr   r1, .L3
  ldr   r1, [r1]
  str   r0, [r1, #4]
.L0:
  mrs   r0, psr
  mov   r1, 0x3F    // 0b00111111
  and   r0, r1
  sls   r0, #2
  ldr   r1, .L3 + 4
  add   r0, r1
  ldr   r0, [r0]
  tst   r0, r0      // Does r0 point to a function?
  beq   .L1
  blx   r0
.L1:
  mov   r0, .L3 + 12
  blx   r0          // Execute interrupt handler
  CPSID i           // Disable interrupts
  mov   r1, r13
  mov   r0, .L3
  mov   r0, [r0]
  mov   r0, [r0, #4]
  mov   r13, r0
  pop   {r4-r7}
  mov   r8, r4
  mov   r9, r5
  mov   r10, r6
  mov   r11, r7
  pop   {r4-r7}
  mov   r0, r13
  mov   r13, r1
  CPSIE i
  msr   psp, r0
  bx    r14
.L3:
  .word CURCTX      //0
  .word __handlers  //4
  .word 0xFFFFFFFD  //8
  .word schedule    //12
