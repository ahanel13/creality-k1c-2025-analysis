
// === mdns_record_update_rclass_ttl @ 00403f68 ===

/* WARNING: Unknown calling convention */

void mdns_record_update_rclass_ttl(mdns_record_t *record,uint16_t rclass,uint32_t ttl)

{
  int in_a0;
  undefined2 in_a1;
  int in_a2;
  
  if (*(short *)(in_a0 + 0x28) == 0) {
    *(undefined2 *)(in_a0 + 0x28) = in_a1;
  }
  if ((*(int *)(in_a0 + 0x2c) == 0) || (in_a2 == 0)) {
    *(int *)(in_a0 + 0x2c) = in_a2;
  }
  *(ushort *)(in_a0 + 0x28) = *(ushort *)(in_a0 + 0x28) & 0x8001;
  if (*(int *)(in_a0 + 8) == 0xc) {
    *(ushort *)(in_a0 + 0x28) = *(ushort *)(in_a0 + 0x28) & 0x7fff;
  }
  return;
}



// === signal_handler @ 00409500 ===

/* WARNING: Unknown calling convention */

void signal_handler(int signal)

{
  running = 0;
  return;
}



// === signal @ 0040a560 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;
  
  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_0041b028)();
  return p_Var1;
}



// === signal @ 0041c01c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* signal@@GLIBC_2.0 */
  halt_baddata();
}


