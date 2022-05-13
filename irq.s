  .text
  .align 1
  .global __irq
  .syntax unified

__irq:
  push  {lr}

  mov   r0, lr
  ldr   r1, .L2+8   // Return to thread mode address
  cmp   r0, r1      // Check if in interrupt context
  bne   .L0         // Skip context save if from interrupt

  cpsid i           // Turn off interrupts
  mrs   r0, psp     // Get PSP
  mov   r1, sp      // Save MSP
  mov   sp, r0     
  push  {r4-r7}
  mov   r4, r8
  mov   r5, r9
  mov   r6, r10
  mov   r7, r11
  push  {r4-r7}
  mov   r0, sp      // Save new PSP
  mov   sp, r1      // Restore MSP
  cpsie i           // Enable interrupts

  ldr   r1, .L2     // Save the stack pointer
  ldr   r1, [r1]
  str   r0, [r1, #4]

.L0:
  mrs   r0, psr     // Get the interrupt offset
  movs  r1, 0x3F    // 0b00111111
  ands  r0, r1
  lsls  r0, #2      
  ldr   r1, .L2+4   
  adds  r0, r1      // __handler + offset
  ldr   r0, [r0]
  tst   r0, r0      // Does r0 point to a function?
  beq   .L1
  blx   r0          // Execute interrupt handler

  ldr   r0, [sp]    // Did we come from an interrupt context?
  ldr   r1, .L2+8
  cmp   r1, r0
  bne   .L12

.L1:                // Time for a new context
  ldr   r0, .L2+12
  blx   r0          // Schedule

  cpsid i           // Disable interrupts
  //mov   r1, sp
  ldr   r1, .L2
  ldr   r1, [r1]
  ldr   r0, [r1,#4]

  ldm   r0!, {r4-r7}
  mov   r8, r4
  mov   r9, r5
  mov   r10, r6
  mov   r11, r7
  ldm   r0!, {r4-r7}
  //mov   r0, sp
  //mov   sp, r1
  cpsie i           // Enable interrupts
  msr   psp, r0

.L12:
  pop   {pc}
  .align 2

.L2:
  .word CURCTX      //0
  .word __handler   //4
  .word 0xFFFFFFFD  //8
  .word schedule    //12
  /*mov   r0, r14
  ldr   r1, .L2+4   // Return to thread mode address
  cmp   r0, r1      // Check if in interrupt context
  bne   .L0
  cpsid i           // Turn off interrupts
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
  cpsie i           // Enable interrupts
  //ldr   r1, .L2
  //ldr   r1, [r1]
  //str   r0, [r1, #4]
.L0:
  mrs   r0, psr     // Get the interrupt offset
  mov   r1, #0x3F   // 0b00111111
  and   r0, r1
  lsl   r0, #2      
  ldr   r1, .L2+4   
  add   r0, r1      // __handler + offset
  ldr   r0, [r0]
  tst   r0, r0      // Does r0 point to a function?
  beq   .L1
  blx   r0          // Execute interrupt handler
.L1:
  cpsid i           // Disable interrupts
  mov   r1, r13
  ldr   r0, .L2
  ldr   r0, [r0]
  ldr   r0, [r0, #4]
  mov   r13, r0
  pop   {r4-r7}
  mov   r8, r4
  mov   r9, r5
  mov   r10, r6
  mov   r11, r7
  pop   {r4-r7}
  mov   r0, r13
  mov   r13, r1
  cpsie i           // Enable interrupts
  msr   psp, r0
  bx r14
  .align 2
.L2:
  .word __handler
  .word 0xFFFFFFFD*/
