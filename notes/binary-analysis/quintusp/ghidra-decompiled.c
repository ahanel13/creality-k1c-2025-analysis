
// === signal_handle @ 00404504 ===

void signal_handle(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 0x10) {
    hs_log_push(1," \n<-------- Show hostserver info start -------->\n");
    hs_log_push(1,"Build (%s %s)\n","Aug 26 2025","05:47:57");
    if ((*(char *)((int)hs + 300) == '\0') && (*(int *)((int)hs + 0x130) < 2)) {
      puVar1 = &DAT_00411c80;
    }
    else {
      puVar1 = &DAT_00411c7c;
    }
    hs_log_push(1,"Debug mode is %s\n",puVar1);
    hs_log_push(1," \n### Station\n");
    hs_station_show((int)hs + 0x1240);
    hs_log_push(1," \n### Activate\n");
    hs_activate_show((int)hs + 0x1218);
    hs_log_push(1," \n### Timer\n");
    hs_timer_show((int)hs + 0x11f0);
    hs_log_push(1," \n### Hardware\n");
    hs_hal_veiw((int)hs + 0x240);
    hs_log_push(1," \n### Woerker\n");
    hs_worker_view();
    hs_log_push(1,"<-------- Show hostserver info end -------->\n ");
    return;
  }
  if (param_1 == 0x11) {
    if (*(char *)((int)hs + 300) != '\0') {
      *(undefined1 *)((int)hs + 300) = 0;
      hs_log_push(1,"Set debug flag %s \n",&DAT_00411c80);
      return;
    }
    *(undefined1 *)((int)hs + 300) = 1;
    hs_log_push(1,"Set debug flag %s \n",&DAT_00411c7c);
    return;
  }
  if (*(code **)((int)hs + 0x11c) != (code *)0x0) {
    (**(code **)((int)hs + 0x11c))((int)hs + 0x104);
  }
  if (*(code **)((int)hs + 0x12c4) != (code *)0x0) {
    (**(code **)((int)hs + 0x12c4))((int)hs + 0x1298);
  }
  hs_hal_destory((int)hs + 0x240);
  hs_activate_destory((int)hs + 0x1218);
  hs_station_destory((int)hs + 0x1240);
  hs_timer_destory((int)hs + 0x11f0);
  hs_conf_destory((int)hs + 0x10e0);
  hs_log_destory((int)hs + 0x128);
  free(hs);
                    /* WARNING: Subroutine does not return */
  hs = (void *)0x0;
  _exit(0);
}



// === signal_manage @ 00404720 ===

void signal_manage(void)

{
  _union_1051 local_98;
  code *local_94;
  sigset_t sStack_90;
  
  local_94 = signal_handle;
  sigemptyset(&sStack_90);
  local_98.sa_handler = (__sighandler_t)0x10000008;
  sigaction(0x10,(sigaction *)&local_98,(sigaction *)0x0);
  sigaction(0x11,(sigaction *)&local_98,(sigaction *)0x0);
  sigaction(2,(sigaction *)&local_98,(sigaction *)0x0);
  signal(0x1b,(__sighandler_t)&DAT_00000001);
  return;
}



// === hs_ipcmsg_get_key @ 00405b70 ===

void hs_ipcmsg_get_key(undefined4 param_1)

{
  (*(code *)PTR_ftok_00425a40)(param_1,0x20);
  return;
}



// === hs_hal_uvc_update @ 00408b30 ===

void hs_hal_uvc_update(int *param_1)

{
  int *piVar1;
  
  if ((((param_1 != (int *)0x0) && (*param_1 != 0)) &&
      (piVar1 = (int *)param_1[1], piVar1 != (int *)0x0)) && ((*piVar1 != 0 || (piVar1[1] != 0)))) {
    hs_timer_resume(*param_1,3000);
    hs_log_push(2,"HAL uvc do update\n");
    return;
  }
  return;
}



// === hs_worker_assign_from_hal @ 0040abe0 ===

undefined4 hs_worker_assign_from_hal(int param_1)

{
  if (*(int *)(param_1 + 4) != 1) {
    if (*(int *)(param_1 + 4) == 2) {
      hs_worker_hal_msg_pwl(param_1 + 8,&hsworker);
    }
    return 0;
  }
  hs_worker_hal_msg_cam(param_1 + 8,&hsworker);
  return 0;
}



// === hs_worker_assign_to_hal @ 0040ac40 ===

undefined4 hs_worker_assign_to_hal(void)

{
  return 0;
}



// === hs_worker_assign_from_ai @ 0040ac48 ===

undefined4 hs_worker_assign_from_ai(void)

{
  return 0;
}



// === hs_worker_assign_to_ai @ 0040ac50 ===

undefined4 hs_worker_assign_to_ai(void)

{
  return 0;
}



// === hs_worker_assign_from_printer @ 0040ac58 ===

undefined4 hs_worker_assign_from_printer(int param_1)

{
  if (*(uint *)(param_1 + 8) < 8) {
    switch(*(uint *)(param_1 + 8)) {
    default:
      hs_worker_print_abnormal();
      return 0;
    case 1:
      hs_worker_print_standby();
      return 0;
    case 2:
      hs_worker_print_printing();
      return 0;
    case 3:
      hs_worker_print_paused();
      return 0;
    case 4:
      hs_worker_print_cancelled();
      return 0;
    case 5:
      hs_worker_print_complete(param_1 + 4,&hsworker);
      return 0;
    }
  }
  return 0;
}



// === hs_worker_assign_to_printer @ 0040ad28 ===

undefined4 hs_worker_assign_to_printer(void)

{
  return 0;
}



// === hs_worker_assign_from_ui @ 0040ad30 ===

undefined4 hs_worker_assign_from_ui(int param_1)

{
  int iVar1;
  
  if (*(uint *)(param_1 + 4) < 10) {
    iVar1 = param_1 + 4;
    switch(*(uint *)(param_1 + 4)) {
    case 1:
      hs_worker_ui_lcd(iVar1,&hsworker);
      return 0;
    case 2:
      hs_worker_ui_led(iVar1,&hsworker);
      return 0;
    case 3:
      hs_worker_ui_camera(iVar1,&hsworker);
      return 0;
    case 4:
      hs_worker_ui_upgrade(iVar1,&hsworker);
      return 0;
    case 5:
      hs_worker_ui_ai(iVar1,&hsworker);
      break;
    case 6:
      hs_worker_ui_livestream(iVar1,&hsworker);
      return 0;
    case 7:
      hs_worker_ui_lapse(iVar1,&hsworker);
      return 0;
    case 8:
      hs_worker_ui_print(iVar1,&hsworker);
      return 0;
    case 9:
      hs_worker_ui_reset(iVar1,&hsworker);
      return 0;
    }
    return 0;
  }
  return 0;
}



// === hs_worker_assign @ 0040ae64 ===

undefined4 hs_worker_assign(uint *param_1,int param_2)

{
  uint uVar1;
  
  if ((param_1 == (uint *)0x0) || (param_2 == 0)) {
    return 0xffffffff;
  }
  uVar1 = *param_1;
  hsworker = param_2;
  if (uVar1 == 4) {
    hs_worker_assign_from_hal();
    return 0;
  }
  if (uVar1 < 5) {
    if (uVar1 == 1) {
      hs_worker_assign_from_ui();
      return 0;
    }
    if (uVar1 == 2) {
      hs_worker_assign_from_printer();
      return 0;
    }
  }
  else if (uVar1 == 0x8001) {
    if (*(code **)(param_2 + 0x120) != (code *)0x0) {
      (**(code **)(param_2 + 0x120))(param_2 + 0x104,param_1);
      return 0;
    }
  }
  else if ((uVar1 == 0x8002) && (*(code **)(param_2 + 0x12c8) != (code *)0x0)) {
    (**(code **)(param_2 + 0x12c8))(param_2 + 0x1298,param_1);
    return 0;
  }
  return 0;
}



// === hs_worker_ui_upgrade @ 0040bc3c ===

undefined4 hs_worker_ui_upgrade(int param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (*(short *)(param_1 + 6) == 0) {
    cVar1 = *(char *)(param_1 + 8);
  }
  else {
    if (*(short *)(param_1 + 6) != 1) goto LAB_0040bc58;
    if (*(char *)(param_1 + 8) == '\0') goto LAB_0040bca4;
    cVar1 = *(char *)(param_1 + 0x31);
  }
  if (cVar1 != '\0') {
LAB_0040bca4:
    puVar2 = (undefined4 *)(param_1 + 4);
    puVar3 = (undefined4 *)(param_2 + 0xac);
    do {
      uVar7 = *puVar2;
      uVar6 = puVar2[1];
      uVar5 = puVar2[2];
      uVar4 = puVar2[3];
      puVar2 = puVar2 + 4;
      *puVar3 = uVar7;
      puVar3[1] = uVar6;
      puVar3[2] = uVar5;
      puVar3[3] = uVar4;
      puVar3 = puVar3 + 4;
    } while (puVar2 != (undefined4 *)(param_1 + 0x104));
    *puVar3 = *puVar2;
    uVar4 = hs_worker_upgrade_do(param_2);
    return uVar4;
  }
LAB_0040bc58:
  hs_log_push(0,"Upgrade file not set \'%s\'","hs_worker_ui_upgrade");
  return 0xffffffff;
}



// === hs_worker_upgrade_handle @ 0040c640 ===

undefined4 hs_worker_upgrade_handle(int param_1)

{
  char cVar1;
  char cVar2;
  short sVar3;
  bool bVar4;
  char *pcVar5;
  undefined *puVar6;
  FILE *pFVar7;
  char *pcVar8;
  char *pcVar9;
  int iVar10;
  size_t sVar11;
  int *piVar12;
  char *pcVar13;
  undefined *puVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  char acStack_8c0 [1024];
  undefined4 local_4c0;
  undefined4 local_4bc;
  undefined2 local_4b8;
  char acStack_4b4 [504];
  char local_2bc [4];
  undefined4 local_2b8 [4];
  char acStack_2a8 [492];
  int local_bc [16];
  undefined4 local_7c;
  undefined2 local_78;
  int local_3c;
  int local_38;
  int local_34;
  undefined *local_30;
  int local_2c;
  
  memset(local_2bc,0,0x200);
  memset(acStack_8c0,0,0x400);
  memset(&local_4c0,0,0x204);
  if (*(short *)(param_1 + 0xae) == 0) {
    snprintf(local_2bc,0x1ff,"%s %s &> /dev/null && echo \"retcode($?)\"","/bin/upgchck.sh",
             param_1 + 0xb0);
LAB_0040c784:
    hs_log_push(1,"upgrade command: %s\n",local_2bc);
    pFVar7 = popen(local_2bc,"r");
    if (pFVar7 == (FILE *)0x0) goto LAB_0040cb9c;
    while( true ) {
      pcVar8 = fgets(acStack_8c0,0x400,pFVar7);
      if (pcVar8 == (char *)0x0) break;
      pcVar8 = strstr(acStack_8c0,"retcode(0)");
      if (pcVar8 != (char *)0x0) {
        fclose(pFVar7);
        sVar3 = *(short *)(param_1 + 0xae);
        goto LAB_0040c89c;
      }
      pcVar8 = "upgcheck.sh";
      if (*(short *)(param_1 + 0xae) != 0) {
        pcVar8 = "cfs_iap_upgrade.sh";
      }
      hs_log_push(1,"%s : %s",pcVar8,acStack_8c0);
      memset(acStack_8c0,0,0x400);
    }
    fclose(pFVar7);
    sVar3 = *(short *)(param_1 + 0xae);
  }
  else {
    cVar1 = *(char *)(param_1 + 0xb1);
    uVar18 = (uint)*(byte *)(param_1 + 0xb0);
    if (*(char *)(param_1 + 0xd9) != '\0') {
      puVar6 = (undefined *)(param_1 + 0xb1);
      if (cVar1 == '\0') {
        puVar6 = &DAT_00413dc4;
      }
      snprintf(local_2bc,0x1ff,"%s -t %x -i %s -f %s && echo \"retcode($?)\"",
               "/usr/apps/usr/bin/cfs_iap_upgrade.sh",uVar18,puVar6,param_1 + 0xd9);
LAB_0040c768:
      local_4c0 = 0x8001;
      local_4bc = 4;
      local_4b8 = 4;
      hs_station_msg_push(&local_4c0,0);
      goto LAB_0040c784;
    }
    memset(&local_7c,0,0x40);
    if (uVar18 != 0) {
      sprintf((char *)&local_7c,"-t %x ",uVar18);
LAB_0040c6ec:
      puVar6 = (undefined *)(param_1 + 0xb1);
      if (cVar1 == '\0') {
        puVar6 = &DAT_00413dc4;
      }
      snprintf(local_2bc,0x1ff,"%s %s -i %s && echo \"retcode($?)\"",
               "/usr/apps/usr/bin/cfs_iap_upgrade.sh",&local_7c,puVar6);
      goto LAB_0040c768;
    }
    memset(local_bc,0,0x40);
    pcVar8 = "/usr/apps/usr/bin/cfs_iap_upgchck.sh";
    pcVar5 = local_2bc;
    do {
      pcVar13 = pcVar5;
      pcVar9 = pcVar8;
      uVar17 = *(undefined4 *)(pcVar9 + 4);
      uVar16 = *(undefined4 *)(pcVar9 + 8);
      uVar15 = *(undefined4 *)(pcVar9 + 0xc);
      *(undefined4 *)pcVar13 = *(undefined4 *)pcVar9;
      *(undefined4 *)(pcVar13 + 4) = uVar17;
      *(undefined4 *)(pcVar13 + 8) = uVar16;
      *(undefined4 *)(pcVar13 + 0xc) = uVar15;
      pcVar8 = pcVar9 + 0x10;
      pcVar5 = pcVar13 + 0x10;
    } while (pcVar9 + 0x10 != "k.sh");
    cVar2 = pcVar9[0x14];
    *(undefined4 *)(pcVar13 + 0x10) = s__usr_apps_usr_bin_cfs_iap_upgchc_00413e2c._32_4_;
    pcVar13[0x14] = cVar2;
    pFVar7 = popen(local_2bc,"r");
    if (pFVar7 != (FILE *)0x0) {
      local_38 = 0x410000;
      pcVar8 = fgets(acStack_8c0,0x400,pFVar7);
      iVar20 = 0;
      bVar4 = false;
      while (pcVar8 != (char *)0x0) {
        pcVar8 = strstr(acStack_8c0,"device needs to be upgraded");
        if (pcVar8 != (char *)0x0) {
          pcVar8 = strstr(acStack_8c0,"type=");
          bVar4 = true;
          if (pcVar8 != (char *)0x0) {
            local_3c = 0;
            iVar10 = __isoc99_sscanf(pcVar8 + 5,local_38 + 0x3e90,&local_3c);
            if (iVar10 == 1) {
              if (iVar20 == 0) {
LAB_0040cb7c:
                local_bc[iVar20 * 2] = local_3c;
                local_bc[iVar20 * 2 + 1] = 1;
                iVar20 = iVar20 + 1;
              }
              else {
                piVar12 = local_bc;
                if (local_3c == local_bc[0]) {
                  iVar10 = 0;
                }
                else {
                  iVar10 = 0;
                  do {
                    iVar10 = iVar10 + 1;
                    piVar12 = piVar12 + 2;
                    if (iVar20 == iVar10) {
                      bVar4 = true;
                      if (iVar20 != 8) goto LAB_0040cb7c;
                      goto LAB_0040c9dc;
                    }
                  } while (*piVar12 != local_3c);
                }
                local_bc[iVar10 * 2 + 1] = local_bc[iVar10 * 2 + 1] + 1;
              }
            }
            bVar4 = true;
          }
        }
LAB_0040c9dc:
        hs_log_push(1,"cfs_iap_upgcheck.sh : %s",acStack_8c0);
        memset(acStack_8c0,0,0x400);
        pcVar8 = fgets(acStack_8c0,0x400,pFVar7);
      }
      fclose(pFVar7);
      if (!bVar4) {
        sVar3 = *(short *)(param_1 + 0xae);
LAB_0040c89c:
        if (sVar3 == 0) {
          local_4b8 = 0;
        }
        else {
          local_4b8 = 2;
        }
        goto LAB_0040c84c;
      }
      if (iVar20 == 0) {
        local_7c = 0x3020742d;
        local_78 = 0x20;
      }
      else {
        sVar11 = strlen((char *)&local_7c);
        sprintf((char *)((int)&local_7c + sVar11),"-t %x ",local_bc[0]);
        sVar11 = strlen(acStack_4b4);
        pcVar8 = acStack_4b4 + sVar11;
        local_38 = iVar20 + -1;
        local_34 = 0x410000;
        local_30 = &DAT_00413de8;
        piVar12 = local_bc;
        iVar19 = 0;
        puVar6 = &DAT_00413dc0;
        local_2c = 0x410000;
        iVar10 = local_bc[0];
        while( true ) {
          puVar14 = local_30;
          if (iVar19 == local_38) {
            puVar14 = &DAT_00413dec;
          }
          iVar19 = iVar19 + 1;
          sprintf(pcVar8,(char *)(local_34 + 0x3f80),puVar6,iVar10,piVar12[1],puVar14);
          if (iVar20 == iVar19) break;
          sVar11 = strlen((char *)&local_7c);
          iVar10 = piVar12[2];
          sprintf((char *)((int)&local_7c + sVar11),"-t %x ",iVar10);
          sVar11 = strlen(acStack_4b4);
          pcVar8 = acStack_4b4 + sVar11;
          piVar12 = piVar12 + 2;
          puVar6 = (undefined *)(local_2c + 0x2ab0);
        }
        hs_log_push(1,"cfs_iap_upgcheck result: %s\n",acStack_4b4);
      }
      goto LAB_0040c6ec;
    }
LAB_0040cb9c:
    piVar12 = __errno_location();
    pcVar8 = strerror(*piVar12);
    hs_log_push(0,"Popen \'%s\' fail (%s)\n",local_2bc,pcVar8);
    sVar3 = *(short *)(param_1 + 0xae);
  }
  if (sVar3 == 0) {
    local_4b8 = 1;
  }
  else {
    local_4b8 = 3;
  }
LAB_0040c84c:
  local_4bc = 4;
  local_4c0 = 0x8001;
  hs_station_msg_push(&local_4c0,0);
  return 0;
}



// === hs_worker_upgrade_do @ 0040cc10 ===

undefined4 hs_worker_upgrade_do(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  char *__name;
  undefined4 local_218;
  undefined4 local_214;
  undefined2 local_210;
  
  memset(&local_218,0,0x204);
  __name = (char *)(param_1 + 0xb0);
  if (((*(short *)(param_1 + 0xae) == 0) ||
      (__name = (char *)(param_1 + 0xd9), *(char *)(param_1 + 0xb0) != '\0')) &&
     (iVar2 = access(__name,4), iVar2 != 0)) {
    piVar3 = __errno_location();
    pcVar4 = strerror(*piVar3);
    hs_log_push(0,"Package file \'%s\' ls nonexistent or unreadable (%s)\n",__name,pcVar4);
    local_218 = 0x8001;
    local_214 = 4;
    local_210 = 1;
    hs_station_msg_push(&local_218,0);
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = hs_comm_create_thread_task(hs_worker_upgrade_handle,param_1);
  }
  return uVar1;
}



// === get_total_time @ 00410cdc ===

/* WARNING: Removing unreachable block (ram,0x00410d00) */

int get_total_time(void)

{
  timespec local_10;
  
  clock_gettime(1,&local_10);
  return local_10.tv_sec * 1000 + local_10.tv_nsec / 1000000;
}



// === pthread_mutex_unlock @ 004150f0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_mutex_unlock_004258c4)();
  return iVar1;
}



// === signal @ 00415270 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;
  
  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_00425924)();
  return p_Var1;
}



// === pthread_mutex_unlock @ 00426004 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_mutex_unlock@@GLIBC_2.0 */
  halt_baddata();
}



// === signal @ 00426068 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* signal@@GLIBC_2.0 */
  halt_baddata();
}


