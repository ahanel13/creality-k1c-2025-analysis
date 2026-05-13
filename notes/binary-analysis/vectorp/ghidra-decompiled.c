
// === lv_timer_enable.part.2 @ 00409510 ===

void lv_timer_enable_part_2(void)

{
  DAT_0084d6b4 = 0;
  if (DAT_0084d6cc != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00409524. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_0084d6cc)(DAT_0084d6d0);
    return;
  }
  return;
}



// === lv_timer_enable @ 00409eec ===

void lv_timer_enable(int param_1)

{
  DAT_0084d6b0._0_1_ = (undefined1)param_1;
  if (param_1 != 0) {
    lv_timer_enable_part_2();
    return;
  }
  return;
}



// === lv_unlock @ 0040a004 ===

void lv_unlock(void)

{
  lv_mutex_unlock(&DAT_0084d8a8);
  return;
}



// === lv_mutex_unlock @ 0040a278 ===

bool lv_mutex_unlock(pthread_mutex_t *param_1)

{
  int iVar1;
  
  iVar1 = pthread_mutex_unlock(param_1);
  if (iVar1 != 0) {
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/osal/lv_pthread.c"
               ,0x71,"lv_mutex_unlock","Error: %d",iVar1);
  }
  return iVar1 == 0;
}



// === lv_thread_sync_signal @ 0040a394 ===

undefined4 lv_thread_sync_signal(pthread_mutex_t *param_1)

{
  pthread_mutex_lock(param_1);
  param_1[3].__size[0] = '\x01';
  pthread_cond_signal((pthread_cond_t *)(param_1 + 1));
  pthread_mutex_unlock(param_1);
  return 1;
}



// === lv_thread_sync_signal_isr @ 0040a404 ===

undefined4 lv_thread_sync_signal_isr(void)

{
  return 0;
}



// === value_update @ 004118fc ===

/* WARNING: Removing unreachable block (ram,0x00411ab0) */

void value_update(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined4 uVar7;
  
  iVar3 = *(int *)(param_1 + 0x40);
  if (iVar3 != -0x8000) {
    fVar4 = *(float *)(param_1 + 0x3c);
    fVar5 = *(float *)(param_1 + 0x38);
    if (fVar5 <= fVar4) {
      iVar2 = *(int *)(param_1 + 0x4c);
    }
    else {
      iVar2 = *(int *)(param_1 + 0x4c);
      fVar4 = fVar4 + DAT_00585fd0;
    }
    uVar1 = (uint)(iVar2 << 0x1d) >> 0x1e;
    if (uVar1 == 1) {
      iVar2 = (*(int *)(param_1 + 0x44) + *(int *)(param_1 + 0x48)) / 2;
      fVar6 = (fVar5 + fVar4) * DAT_00585fd4;
      if (iVar3 < iVar2) {
        iVar3 = lv_map(iVar3,*(int *)(param_1 + 0x44),iVar2,(int)fVar5,(int)fVar6);
        fVar4 = (float)iVar3;
        lv_arc_set_start_angle(param_1,fVar4);
        lv_arc_set_end_angle(param_1,fVar6);
        *(float *)(param_1 + 0x58) = fVar4;
      }
      else {
        iVar3 = lv_map(iVar3,iVar2,*(int *)(param_1 + 0x48),(int)fVar6,(int)fVar4);
        lv_arc_set_start_angle(param_1,fVar6);
        fVar4 = (float)iVar3;
        lv_arc_set_end_angle(param_1,fVar4);
        *(float *)(param_1 + 0x58) = fVar4;
      }
    }
    else if (uVar1 == 0) {
      iVar3 = lv_map(iVar3,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48),
                     (int)fVar5,(int)fVar4);
      uVar7 = *(undefined4 *)(param_1 + 0x38);
      fVar4 = (float)iVar3;
      lv_arc_set_end_angle(param_1,fVar4);
      lv_arc_set_start_angle(param_1,uVar7);
      *(float *)(param_1 + 0x58) = fVar4;
    }
    else {
      if (uVar1 != 2) {
        lv_log_add(2,2,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/widgets/arc/lv_arc.c"
                   ,0x395,"value_update","Invalid mode: %d",3);
        return;
      }
      iVar3 = lv_map(iVar3,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48),
                     (int)fVar4,(int)fVar5);
      fVar4 = (float)iVar3;
      lv_arc_set_end_angle(param_1,*(undefined4 *)(param_1 + 0x3c));
      lv_arc_set_start_angle(param_1,fVar4);
      *(float *)(param_1 + 0x58) = fVar4;
    }
  }
  return;
}



// === lv_arc_set_rotation @ 004131d4 ===

void lv_arc_set_rotation(int param_1,int param_2)

{
  if (param_2 < 0) {
    do {
      param_2 = param_2 + 0x168;
    } while (param_2 < 0);
    *(int *)(param_1 + 0x2c) = param_2;
    lv_obj_invalidate();
    return;
  }
  for (; 0x167 < param_2; param_2 = param_2 + -0x168) {
  }
  *(int *)(param_1 + 0x2c) = param_2;
  lv_obj_invalidate();
  return;
}



// === lv_arc_get_rotation @ 004135dc ===

undefined4 lv_arc_get_rotation(int param_1)

{
  return *(undefined4 *)(param_1 + 0x2c);
}



// === lv_arc_rotate_obj_to_angle @ 0041375c ===

/* WARNING: Removing unreachable block (ram,0x004137d4) */

void lv_arc_rotate_obj_to_angle(undefined4 param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 *in_f31;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  float local_20;
  undefined4 local_18;
  
  local_18 = 0;
  if (param_2 == 0) {
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/widgets/arc/lv_arc.c"
               ,0x180,"lv_arc_rotate_obj_to_angle","Asserted at expression: %s (%s)",
               "obj_to_rotate != NULL","NULL pointer");
    *in_f31 = 0;
                    /* WARNING: Does not return */
    pcVar1 = (code *)trap(0);
    (*pcVar1)();
  }
  lv_obj_update_layout();
  get_center(param_1,&local_30,&local_24);
  lv_obj_get_style_prop(&local_28,param_1,0x20000,0x50);
  local_24 = (local_24 - local_28 / 2) + param_3;
  lv_obj_align_to(param_2,param_1,9,0,-local_24);
  lv_obj_update_layout(param_1);
  local_18 = 0;
  local_20 = (float)get_angle(param_1);
  local_18 = 0;
  iVar2 = *(int *)(param_2 + 0x18);
  lv_obj_set_style_transform_pivot_x(param_2,local_30 - *(int *)(param_2 + 0x14),0);
  lv_obj_set_style_transform_pivot_y(param_2,-(iVar2 - local_2c),0);
  local_18 = 0;
  lv_obj_set_style_transform_rotation(param_2,(int)local_20 * 10 + 900,0);
  return;
}



// === highlight_update @ 00416808 ===

/* WARNING: Removing unreachable block (ram,0x00416894) */
/* WARNING: Removing unreachable block (ram,0x00416870) */
/* WARNING: Removing unreachable block (ram,0x00416884) */
/* WARNING: Removing unreachable block (ram,0x004168a4) */

void highlight_update(int param_1)

{
  int iVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  lv_buttonmatrix_clear_button_ctrl_all(*(undefined4 *)(param_1 + 0x2c),0xc000);
  uVar6 = (uint)*(ushort *)(param_1 + 0x34);
  uVar3 = (uint)((uint)(int)*(char *)(param_1 + 0x36) < 3);
  uVar4 = uVar6 - uVar3;
  iVar5 = *(int *)(param_1 + 0x38);
  uVar3 = ((((uVar4 >> 2) + uVar4 + 1 + uVar4 / 400) - uVar4 / 100) +
          ((uVar3 * 0xc + (int)*(char *)(param_1 + 0x36)) * 0x1f - 0x3e) / 0xc) % 7;
  if (iVar5 != 0) {
    uVar4 = *(uint *)(param_1 + 0x3c);
    uVar7 = 0;
    if (uVar4 != 0) {
      iVar1 = 0;
      while( true ) {
        puVar2 = (ushort *)(iVar5 + iVar1);
        uVar7 = uVar7 + 1;
        if ((*puVar2 == uVar6) && ((char)puVar2[1] == *(char *)(param_1 + 0x36))) {
          lv_buttonmatrix_set_button_ctrl
                    (*(undefined4 *)(param_1 + 0x2c),uVar3 + (int)*(char *)((int)puVar2 + 3) + 6,
                     0x8000);
          uVar4 = *(uint *)(param_1 + 0x3c);
        }
        if (uVar4 <= uVar7) break;
        iVar5 = *(int *)(param_1 + 0x38);
        uVar6 = (uint)*(ushort *)(param_1 + 0x34);
        iVar1 = uVar7 * 4;
      }
    }
  }
  if ((*(uint *)(param_1 + 0x34) & 0xffffff) == (*(uint *)(param_1 + 0x30) & 0xffffff)) {
    lv_buttonmatrix_set_button_ctrl
              (*(undefined4 *)(param_1 + 0x2c),uVar3 + (int)*(char *)(param_1 + 0x33) + 6,0x4000);
    return;
  }
  return;
}



// === lv_chart_set_update_mode @ 00418a84 ===

void lv_chart_set_update_mode(int param_1,uint param_2)

{
  if ((uint)(*(int *)(param_1 + 0x74) << 0x1c) >> 0x1f != param_2) {
    *(byte *)(param_1 + 0x74) = *(byte *)(param_1 + 0x74) & 0xf7 | (byte)((param_2 & 1) << 3);
    lv_obj_invalidate();
    return;
  }
  return;
}



// === lv_keyboard_update_ctrl_map @ 0041dc30 ===

void lv_keyboard_update_ctrl_map(int param_1)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  if ((*(byte *)(param_1 + 0x50) & 1) == 0) {
    puVar1 = (uint *)lv_malloc(*(int *)(param_1 + 0x38) << 2);
    lv_memcpy(puVar1,*(undefined4 *)(kb_ctrl + *(int *)(param_1 + 0x4c) * 4),
              *(int *)(param_1 + 0x38) << 2);
    iVar4 = *(int *)(param_1 + 0x38);
    if (iVar4 != 0) {
      puVar2 = puVar1;
      do {
        puVar3 = puVar2 + 1;
        *puVar2 = *puVar2 & 0xfffffbff;
        puVar2 = puVar3;
      } while (puVar1 + iVar4 != puVar3);
    }
    lv_buttonmatrix_set_ctrl_map(param_1,puVar1);
    lv_free(puVar1);
    return;
  }
  lv_buttonmatrix_set_ctrl_map(param_1,*(undefined4 *)(kb_ctrl + *(int *)(param_1 + 0x4c) * 4));
  return;
}



// === lv_keyboard_update_map @ 0041dd04 ===

void lv_keyboard_update_map(int param_1)

{
  lv_buttonmatrix_set_map(param_1,(&kb_map)[*(int *)(param_1 + 0x4c)]);
  lv_keyboard_update_ctrl_map(param_1);
  return;
}



// === lv_keyboard_constructor @ 0041dd44 ===

void lv_keyboard_constructor(undefined4 param_1,int param_2)

{
  lv_obj_remove_flag(param_2,4);
  *(byte *)(param_2 + 0x50) = *(byte *)(param_2 + 0x50) & 0xfe;
  *(undefined4 *)(param_2 + 0x48) = 0;
  *(undefined4 *)(param_2 + 0x4c) = 0;
  lv_obj_align(param_2,5,0,0);
  lv_obj_add_event_cb(param_2,lv_keyboard_def_event_cb,0x23,0);
  lv_obj_set_style_base_dir(param_2,0,0);
  lv_keyboard_update_map(param_2);
  return;
}



// === lv_keyboard_def_event_cb @ 0041ddc4 ===

void lv_keyboard_def_event_cb(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined *puVar6;
  
  iVar1 = lv_event_get_current_target();
  iVar2 = lv_buttonmatrix_get_selected_button(iVar1);
  if (iVar2 == 0xffff) {
    return;
  }
  iVar2 = lv_buttonmatrix_get_button_text(iVar1,iVar2);
  if (iVar2 == 0) {
    return;
  }
  iVar3 = lv_strcmp(iVar2,&PTR_DAT_00586ee0);
  puVar6 = kb_map;
  if (iVar3 == 0) {
    *(undefined4 *)(iVar1 + 0x4c) = 0;
    lv_buttonmatrix_set_map(iVar1,puVar6);
    lv_keyboard_update_ctrl_map(iVar1);
    return;
  }
  iVar3 = lv_strcmp(iVar2,&DAT_00586ee4);
  puVar6 = PTR_default_kb_map_uc_006c457c;
  if (iVar3 == 0) {
    *(undefined4 *)(iVar1 + 0x4c) = 1;
  }
  else {
    iVar3 = lv_strcmp(iVar2,&DAT_00586ee8);
    puVar6 = PTR_default_kb_map_spec_006c4580;
    if (iVar3 != 0) {
      iVar3 = lv_strcmp(iVar2,&DAT_00586eec);
      if ((iVar3 == 0) || (iVar3 = lv_strcmp(iVar2,&DAT_00586ef0,0), iVar3 == 0)) {
        iVar2 = lv_obj_send_event(iVar1,0x27);
        if (iVar2 != 1) {
          return;
        }
        iVar1 = *(int *)(iVar1 + 0x48);
        if (iVar1 == 0) {
          return;
        }
        uVar5 = 0x27;
      }
      else {
        iVar3 = lv_strcmp(iVar2,&DAT_00585e80,0);
        if (iVar3 == 0) {
          iVar2 = lv_obj_send_event(iVar1,0x26,0);
          if (iVar2 != 1) {
            return;
          }
          iVar1 = *(int *)(iVar1 + 0x48);
          if (iVar1 == 0) {
            return;
          }
        }
        else {
          if (*(int *)(iVar1 + 0x48) == 0) {
            return;
          }
          iVar3 = lv_strcmp(iVar2,"Enter");
          if ((iVar3 != 0) && (iVar3 = lv_strcmp(iVar2,&DAT_00586efc), iVar3 != 0)) {
            iVar3 = lv_strcmp(iVar2,&DAT_00586310);
            if (iVar3 == 0) {
              lv_textarea_cursor_left(*(undefined4 *)(iVar1 + 0x48));
              return;
            }
            iVar3 = lv_strcmp(iVar2,&DAT_00586314);
            if (iVar3 == 0) {
              lv_textarea_cursor_right(*(undefined4 *)(iVar1 + 0x48));
              return;
            }
            iVar3 = lv_strcmp(iVar2,&DAT_00586f00);
            if (iVar3 == 0) {
              lv_textarea_delete_char(*(undefined4 *)(iVar1 + 0x48));
              return;
            }
            iVar3 = lv_strcmp(iVar2,&DAT_00586f04);
            if (iVar3 == 0) {
              iVar2 = lv_textarea_get_cursor_pos();
              pcVar4 = (char *)lv_textarea_get_text(*(undefined4 *)(iVar1 + 0x48));
              if (*pcVar4 == '-') {
                lv_textarea_set_cursor_pos(*(undefined4 *)(iVar1 + 0x48),1);
                lv_textarea_delete_char(*(undefined4 *)(iVar1 + 0x48));
                lv_textarea_add_char(*(undefined4 *)(iVar1 + 0x48),0x2b);
                uVar5 = *(undefined4 *)(iVar1 + 0x48);
              }
              else if (*pcVar4 == '+') {
                lv_textarea_set_cursor_pos(*(undefined4 *)(iVar1 + 0x48),1);
                lv_textarea_delete_char(*(undefined4 *)(iVar1 + 0x48));
                lv_textarea_add_char(*(undefined4 *)(iVar1 + 0x48),0x2d);
                uVar5 = *(undefined4 *)(iVar1 + 0x48);
              }
              else {
                lv_textarea_set_cursor_pos(*(undefined4 *)(iVar1 + 0x48),0);
                lv_textarea_add_char(*(undefined4 *)(iVar1 + 0x48),0x2d);
                uVar5 = *(undefined4 *)(iVar1 + 0x48);
                iVar2 = iVar2 + 1;
              }
              lv_textarea_set_cursor_pos(uVar5,iVar2);
              return;
            }
            lv_textarea_add_text(*(undefined4 *)(iVar1 + 0x48),iVar2);
            return;
          }
          lv_textarea_add_char(*(undefined4 *)(iVar1 + 0x48),10);
          iVar2 = lv_textarea_get_one_line(*(undefined4 *)(iVar1 + 0x48));
          if (iVar2 == 0) {
            return;
          }
          iVar1 = *(int *)(iVar1 + 0x48);
        }
        uVar5 = 0x26;
      }
      lv_obj_send_event(iVar1,uVar5,0);
      return;
    }
    *(undefined4 *)(iVar1 + 0x4c) = 2;
  }
  lv_buttonmatrix_set_map(iVar1,puVar6);
  lv_keyboard_update_ctrl_map(iVar1);
  return;
}



// === lv_keyboard_create @ 0041e130 ===

undefined4 lv_keyboard_create(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = lv_obj_class_create_obj(lv_keyboard_class,param_1);
  lv_obj_class_init_obj(uVar1);
  return uVar1;
}



// === lv_keyboard_set_textarea @ 0041e164 ===

void lv_keyboard_set_textarea(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x48) != 0) {
    lv_obj_remove_state(param_1,2);
  }
  *(int *)(param_1 + 0x48) = param_2;
  if (param_2 != 0) {
    lv_obj_add_state(param_1,2);
    return;
  }
  return;
}



// === lv_keyboard_set_mode @ 0041e1c4 ===

void lv_keyboard_set_mode(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x4c) != param_2) {
    *(int *)(param_1 + 0x4c) = param_2;
    lv_keyboard_update_map();
    return;
  }
  return;
}



// === lv_keyboard_set_popovers @ 0041e1e0 ===

void lv_keyboard_set_popovers(int param_1,uint param_2)

{
  if ((*(uint *)(param_1 + 0x50) & 1) != param_2) {
    *(byte *)(param_1 + 0x50) = *(byte *)(param_1 + 0x50) & 0xfe | (byte)param_2 & 1;
    lv_keyboard_update_ctrl_map();
    return;
  }
  return;
}



// === lv_keyboard_set_map @ 0041e208 ===

void lv_keyboard_set_map(undefined4 param_1,int param_2,undefined *param_3,undefined4 param_4)

{
  (&kb_map)[param_2] = param_3;
  *(undefined4 *)(kb_ctrl + param_2 * 4) = param_4;
  lv_keyboard_update_map();
  return;
}



// === lv_keyboard_get_textarea @ 0041e230 ===

undefined4 lv_keyboard_get_textarea(int param_1)

{
  return *(undefined4 *)(param_1 + 0x48);
}



// === lv_keyboard_get_mode @ 0041e238 ===

undefined4 lv_keyboard_get_mode(int param_1)

{
  return *(undefined4 *)(param_1 + 0x4c);
}



// === lv_keyboard_get_popovers @ 0041e240 ===

uint lv_keyboard_get_popovers(int param_1)

{
  return *(uint *)(param_1 + 0x50) & 1;
}



// === lv_keyboard_get_map_array @ 0041e24c ===

undefined4 lv_keyboard_get_map_array(int param_1)

{
  return *(undefined4 *)(param_1 + 0x2c);
}



// === lv_keyboard_get_selected_button @ 0041e254 ===

undefined4 lv_keyboard_get_selected_button(int param_1)

{
  return *(undefined4 *)(param_1 + 0x40);
}



// === lv_keyboard_get_button_text @ 0041e25c ===

undefined4 lv_keyboard_get_button_text(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  if ((param_2 == 0xffff) || (uVar1 = *(uint *)(param_1 + 0x38), uVar1 < param_2)) {
    return 0;
  }
  uVar4 = 0;
  iVar3 = 0;
  if (param_2 != 0) {
    do {
      iVar5 = iVar3 + 1;
      iVar2 = lv_strcmp(*(undefined4 *)(*(int *)(param_1 + 0x2c) + iVar5 * 4),"\n");
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 2;
      if (iVar2 != 0) {
        iVar3 = iVar5;
      }
    } while (param_2 != uVar4);
    uVar1 = *(uint *)(param_1 + 0x38);
  }
  if (uVar4 == uVar1) {
    return 0;
  }
  return *(undefined4 *)(*(int *)(param_1 + 0x2c) + iVar3 * 4);
}



// === lv_menu_set_mode_root_back_button @ 004223d0 ===

void lv_menu_set_mode_root_back_button(int param_1,uint param_2)

{
  if ((uint)(*(int *)(param_1 + 0x68) << 0xc) >> 0x1f != param_2) {
    *(byte *)(param_1 + 0x6a) = *(byte *)(param_1 + 0x6a) & 0xf7 | (byte)((param_2 & 1) << 3);
    lv_menu_refr();
    return;
  }
  return;
}



// === lv_menu_back_button_is_root @ 004226d4 ===

bool lv_menu_back_button_is_root(int param_1,int param_2)

{
  if (*(int *)(param_1 + 0x50) == param_2) {
    return true;
  }
  if (*(int *)(param_1 + 0x3c) != param_2) {
    return false;
  }
  return *(byte *)(param_1 + 0x69) < 2;
}



// === lv_scale_set_total_tick_count @ 004269b4 ===

void lv_scale_set_total_tick_count(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x48) = *(uint *)(param_1 + 0x48) & 0xffff8000 | param_2 & 0x7fff;
  lv_obj_invalidate();
  return;
}



// === lv_scale_set_rotation @ 004269f8 ===

void lv_scale_set_rotation(int param_1,undefined4 param_2)

{
  int iStack_18;
  int iStack_14;
  int iStack_10;
  int iStack_c;
  
  *(undefined4 *)(param_1 + 0x54) = param_2;
  iStack_c = lv_obj_get_ext_draw_size();
  iStack_14 = *(int *)(param_1 + 0x18) - iStack_c;
  iStack_10 = iStack_c + *(int *)(param_1 + 0x1c);
  iStack_18 = *(int *)(param_1 + 0x14) - iStack_c;
  iStack_c = iStack_c + *(int *)(param_1 + 0x20);
  lv_obj_invalidate_area(param_1,&iStack_18);
  return;
}



// === lv_scale_get_total_tick_count @ 00426f00 ===

uint lv_scale_get_total_tick_count(int param_1)

{
  return *(uint *)(param_1 + 0x48) & 0x7fff;
}



// === update_knob_pos @ 00427144 ===

/* WARNING: Removing unreachable block (ram,0x004272d4) */
/* WARNING: Removing unreachable block (ram,0x004273f0) */

void update_knob_pos(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int *piVar12;
  uint uVar13;
  char cVar14;
  bool bVar15;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30 [2];
  
  iVar1 = lv_indev_active();
  iVar2 = lv_indev_get_type(iVar1);
  if (iVar2 != 1) {
    return;
  }
  iVar2 = lv_indev_get_scroll_obj(iVar1);
  if (iVar2 != 0) {
    return;
  }
  lv_indev_get_point(iVar1,&local_38);
  lv_obj_transform_point(param_1,&local_38,3);
  iVar2 = lv_obj_get_width(param_1);
  iVar3 = lv_obj_get_height(param_1);
  if ((param_2 == 0) || ((*(byte *)(param_1 + 0xa0) & 1) != 0)) {
    iVar1 = *(int *)(param_1 + 0x9c);
  }
  else {
    if (iVar2 < iVar3) {
      uVar8 = local_34 - *(int *)(param_1 + 0x98);
    }
    else {
      uVar8 = local_38 - *(int *)(param_1 + 0x94);
    }
    if ((int)(((int)uVar8 >> 0x1f ^ uVar8) - ((int)uVar8 >> 0x1f)) <
        (int)(uint)*(byte *)(iVar1 + 0x2c)) {
      return;
    }
    iVar1 = *(int *)(param_1 + 0x9c);
  }
  if (iVar1 == 0) {
    iVar1 = lv_bar_get_mode(param_1);
    if (iVar1 != 2) {
      *(byte *)(param_1 + 0xa0) = *(byte *)(param_1 + 0xa0) & 0xfe | 1;
      goto LAB_0042757c;
    }
    *(byte *)(param_1 + 0xa0) = *(byte *)(param_1 + 0xa0) & 0xfe | 1;
    uVar7 = lv_indev_active();
    lv_indev_get_point(uVar7,&local_40);
    lv_obj_transform_point(param_1,&local_40,3);
    lv_obj_get_style_prop(local_30,param_1,0,0x27);
    iVar1 = lv_obj_get_width(param_1);
    iVar4 = lv_obj_get_height(param_1);
    if (local_30[0] == 1) {
      cVar14 = '\x01';
      if (iVar1 < iVar4) goto LAB_004275a0;
LAB_004274a4:
      local_3c = local_40;
      if (*(char *)(param_1 + 0x4c) == cVar14) {
        iVar1 = *(int *)(param_1 + 0x8c);
        if (local_40 <= iVar1) {
          iVar4 = *(int *)(param_1 + 0x74);
          if (iVar4 <= local_40) {
            iVar6 = *(int *)(param_1 + 0x84);
            iVar5 = *(int *)(param_1 + 0x7c);
            goto LAB_004274d4;
          }
          goto LAB_004275ec;
        }
      }
      else {
        iVar6 = *(int *)(param_1 + 0x84);
        if (iVar6 <= local_40) {
          iVar5 = *(int *)(param_1 + 0x7c);
          if (local_40 <= iVar5) {
            iVar1 = *(int *)(param_1 + 0x8c);
            iVar4 = *(int *)(param_1 + 0x74);
LAB_004274d4:
            uVar8 = ((iVar5 - iVar4) / 2 + iVar4) - local_3c;
            uVar10 = ((iVar1 - iVar6) / 2 + iVar6) - local_3c;
            uVar13 = (int)uVar8 >> 0x1f;
            uVar11 = (int)uVar10 >> 0x1f;
            if ((int)((uVar11 ^ uVar10) - uVar11) < (int)((uVar13 ^ uVar8) - uVar13)) {
              *(int *)(param_1 + 0x9c) = param_1 + 0x2c;
              *(byte *)(param_1 + 0xa0) = *(byte *)(param_1 + 0xa0) & 0xfd;
            }
            else {
              *(int *)(param_1 + 0x9c) = param_1 + 0x38;
              *(byte *)(param_1 + 0xa0) = *(byte *)(param_1 + 0xa0) & 0xfd | 2;
            }
            goto LAB_0042721c;
          }
LAB_004275ec:
          *(int *)(param_1 + 0x9c) = param_1 + 0x38;
          goto LAB_0042721c;
        }
      }
    }
    else {
      if (iVar4 <= iVar1) {
        cVar14 = '\0';
        goto LAB_004274a4;
      }
LAB_004275a0:
      if (*(char *)(param_1 + 0x4c) != '\0') {
        iVar1 = *(int *)(param_1 + 0x90);
        if (iVar1 < local_3c) goto LAB_0042757c;
        iVar4 = *(int *)(param_1 + 0x78);
        if (iVar4 <= local_3c) {
          iVar6 = *(int *)(param_1 + 0x88);
          iVar5 = *(int *)(param_1 + 0x80);
          goto LAB_004274d4;
        }
        goto LAB_004275ec;
      }
      iVar6 = *(int *)(param_1 + 0x88);
      if (iVar6 <= local_3c) {
        iVar5 = *(int *)(param_1 + 0x80);
        if (iVar5 < local_3c) goto LAB_004275ec;
        iVar1 = *(int *)(param_1 + 0x90);
        iVar4 = *(int *)(param_1 + 0x78);
        goto LAB_004274d4;
      }
    }
LAB_0042757c:
    *(int *)(param_1 + 0x9c) = param_1 + 0x2c;
  }
LAB_0042721c:
  iVar9 = *(int *)(param_1 + 0x34);
  iVar4 = *(int *)(param_1 + 0x30);
  lv_obj_get_style_prop(&local_40,param_1,0,0x27);
  iVar1 = local_40;
  iVar5 = lv_obj_get_width(param_1);
  iVar6 = lv_obj_get_height(param_1);
  cVar14 = *(char *)(param_1 + 0x4c);
  bVar15 = iVar1 == 1 && iVar6 <= iVar5;
  if (iVar2 < iVar3) {
    lv_obj_get_style_prop(&local_40,param_1,0,0x10);
    iVar1 = local_40;
    lv_obj_get_style_prop(&local_40,param_1,0,0x11);
    iVar5 = lv_obj_get_height(param_1);
    iVar5 = (iVar5 - local_40) - iVar1;
    if ((bool)cVar14 == bVar15) {
      local_38 = (local_40 + *(int *)(param_1 + 0x20)) - local_34;
    }
    else {
      local_38 = local_34 - (iVar1 + *(int *)(param_1 + 0x18));
    }
    iVar1 = *(int *)(param_1 + 0x30);
  }
  else {
    lv_obj_get_style_prop(&local_40,param_1,0,0x12);
    iVar1 = local_40;
    lv_obj_get_style_prop(&local_40,param_1,0,0x13);
    iVar5 = lv_obj_get_width(param_1);
    iVar5 = (iVar5 - iVar1) - local_40;
    if ((bool)cVar14 == bVar15) {
      local_38 = local_38 - (iVar1 + *(int *)(param_1 + 0x14));
    }
    else {
      local_38 = (*(int *)(param_1 + 0x1c) - local_40) - local_38;
    }
    iVar1 = *(int *)(param_1 + 0x30);
    if (iVar5 == 0) goto LAB_004272f0;
  }
  if (iVar5 == 0) {
    trap(7);
  }
  local_38 = iVar1 + (iVar5 / 2 + local_38 * (iVar9 - iVar4)) / iVar5;
LAB_004272f0:
  piVar12 = *(int **)(param_1 + 0x9c);
  if (piVar12 == (int *)(param_1 + 0x38)) {
    iVar4 = *(int *)(param_1 + 0x2c);
  }
  else {
    iVar4 = *(int *)(param_1 + 0x34);
    iVar1 = *(int *)(param_1 + 0x38);
  }
  if (iVar4 < local_38) {
    local_38 = iVar4;
  }
  if (local_38 < iVar1) {
    local_38 = iVar1;
  }
  if (*piVar12 != local_38) {
    *piVar12 = local_38;
    if (iVar2 < iVar3) {
      lv_obj_remove_flag(param_1,0x100);
    }
    else {
      lv_obj_remove_flag(param_1,0x200);
    }
    lv_obj_invalidate(param_1);
    lv_obj_send_event(param_1,0x23,0);
  }
  return;
}



// === lv_spinbox_updatevalue @ 0042a2e0 ===

/* WARNING: Removing unreachable block (ram,0x0042a440) */

void lv_spinbox_updatevalue(int param_1)

{
  ushort uVar1;
  uint uVar2;
  size_t sVar3;
  char *pcVar4;
  char *pcVar5;
  char cVar6;
  byte bVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  uint uVar11;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined2 local_30;
  char acStack_2d [21];
  
  uVar2 = *(uint *)(param_1 + 0x74);
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (*(int *)(param_1 + 0x7c) < 0) {
    bVar7 = 0x2d;
    if (-1 < (int)uVar2) {
      bVar7 = 0x2b;
    }
    local_40 = (uint)bVar7;
    iVar10 = 0;
    pcVar9 = (char *)((int)&local_40 + 1);
  }
  else {
    pcVar9 = (char *)&local_40;
    iVar10 = 1;
  }
  lv_snprintf(acStack_2d + 1,0xe,"%d",((int)uVar2 >> 0x1f ^ uVar2) - ((int)uVar2 >> 0x1f));
  sVar3 = lv_strlen(acStack_2d + 1);
  uVar11 = *(uint *)(param_1 + 0x84);
  uVar2 = uVar11 & 0xf;
  iVar8 = uVar2 - sVar3;
  if (iVar8 != 0) {
    if (-1 < (int)sVar3) {
      pcVar4 = acStack_2d + sVar3 + 1;
      pcVar5 = acStack_2d + uVar2 + 1;
      do {
        cVar6 = *pcVar4;
        pcVar4 = pcVar4 + -1;
        *pcVar5 = cVar6;
        pcVar5 = pcVar5 + -1;
      } while (pcVar4 != acStack_2d);
    }
    if (0 < iVar8) {
      pcVar5 = acStack_2d + 1;
      pcVar4 = pcVar5 + iVar8;
      do {
        *pcVar5 = '0';
        pcVar5 = pcVar5 + 1;
      } while (pcVar5 != pcVar4);
    }
  }
  uVar1 = *(ushort *)(param_1 + 0x84);
  if ((uVar1 & 0xf0) == 0) {
    uVar11 = 0;
    if ((uVar2 == 0) || (uVar11 = uVar2, acStack_2d[1] == '\0')) goto LAB_0042a41c;
LAB_0042a3e0:
    iVar8 = 0;
    pcVar5 = acStack_2d + 2;
    do {
      iVar8 = iVar8 + 1;
      *pcVar9 = acStack_2d[1];
      pcVar9 = pcVar9 + 1;
      if ((int)uVar11 <= iVar8) break;
      acStack_2d[1] = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (acStack_2d[1] != '\0');
    if ((uVar1 & 0xf0) == 0) goto LAB_0042a41c;
  }
  else {
    uVar11 = (uVar11 << 0x18) >> 0x1c;
    if ((uVar11 != 0) && (acStack_2d[1] != '\0')) goto LAB_0042a3e0;
    iVar8 = 0;
  }
  *pcVar9 = '.';
  if ((iVar8 < (int)uVar2) && (cVar6 = acStack_2d[iVar8 + 1], cVar6 != '\0')) {
    pcVar5 = acStack_2d + iVar8 + 1;
    do {
      pcVar9 = pcVar9 + 1;
      *pcVar9 = cVar6;
      if (pcVar5 == acStack_2d + uVar2) break;
      pcVar5 = pcVar5 + 1;
      cVar6 = *pcVar5;
    } while (cVar6 != '\0');
  }
LAB_0042a41c:
  lv_textarea_set_text(param_1,&local_40);
  uVar2 = *(uint *)(param_1 + 0x84) & 0xf;
  for (iVar8 = *(int *)(param_1 + 0x80); 9 < iVar8; iVar8 = iVar8 / 10) {
    uVar2 = uVar2 - 1;
  }
  lv_textarea_set_cursor_pos(param_1,(uVar2 + (uVar11 < uVar2)) - iVar10);
  return;
}



// === lv_textarea_get_password_bullet.part.4 @ 0042e8d4 ===

undefined * lv_textarea_get_password_bullet_part_4(undefined4 param_1)

{
  int iVar1;
  undefined4 local_28 [9];
  
  lv_obj_get_style_prop(local_28,param_1,0,0x5a);
  iVar1 = lv_font_get_glyph_dsc(local_28[0],local_28,0x2022,0);
  if (iVar1 == 0) {
    return &DAT_00586f18;
  }
  return &DAT_005883d0;
}



// === lv_textarea_set_password_bullet @ 0042f344 ===

void lv_textarea_set_password_bullet(int param_1,char *param_2)

{
  code *pcVar1;
  undefined4 *in_zero;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (param_2 == (char *)0x0) {
    pcVar6 = "NULL pointer";
    pcVar5 = "bullet != NULL";
    uVar4 = 0x221;
  }
  else {
    sVar2 = lv_strlen(param_2);
    iVar3 = lv_realloc(*(undefined4 *)(param_1 + 0x38),sVar2 + 1);
    *(int *)(param_1 + 0x38) = iVar3;
    if (iVar3 != 0) {
      lv_memcpy(iVar3,param_2,sVar2);
      *(undefined1 *)(*(int *)(param_1 + 0x38) + sVar2) = 0;
      if ((*(byte *)(param_1 + 0x70) & 4) == 0) {
        return;
      }
      pwd_char_hider_part_5(param_1);
      return;
    }
    pcVar6 = "Out of memory";
    pcVar5 = "ta->pwd_bullet != NULL";
    uVar4 = 0x22f;
  }
  lv_log_add(2,3,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/widgets/textarea/lv_textarea.c"
             ,uVar4,"lv_textarea_set_password_bullet","Asserted at expression: %s (%s)",pcVar5,
             pcVar6);
  *in_zero = 0;
                    /* WARNING: Does not return */
  pcVar1 = (code *)trap(0);
  (*pcVar1)();
}



// === lv_textarea_set_password_show_time @ 0042f584 ===

void lv_textarea_set_password_show_time(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x44) = param_2;
  if ((*(byte *)(param_1 + 0x70) & 4) == 0) {
    return;
  }
  pwd_char_hider_part_5();
  return;
}



// === lv_textarea_get_password_mode @ 0042f6c8 ===

uint lv_textarea_get_password_mode(int param_1)

{
  return ((uint)*(byte *)(param_1 + 0x70) << 0x1d) >> 0x1f;
}



// === lv_textarea_get_password_bullet @ 0042f6d4 ===

void lv_textarea_get_password_bullet(int param_1)

{
  if (*(int *)(param_1 + 0x38) != 0) {
    return;
  }
  lv_textarea_get_password_bullet_part_4();
  return;
}



// === lv_textarea_get_password_show_time @ 0042f778 ===

undefined4 lv_textarea_get_password_show_time(int param_1)

{
  return *(undefined4 *)(param_1 + 0x44);
}



// === lv_textarea_set_password_mode @ 004301d8 ===

void lv_textarea_set_password_mode(int param_1,uint param_2)

{
  code *pcVar1;
  undefined4 *in_zero;
  undefined4 uVar2;
  int iVar3;
  
  if ((uint)(*(int *)(param_1 + 0x70) << 0x1d) >> 0x1f == param_2) {
    return;
  }
  if (param_2 != 0) {
    *(byte *)(param_1 + 0x70) = *(byte *)(param_1 + 0x70) & 0xfb | 4;
    uVar2 = lv_label_get_text(*(undefined4 *)(param_1 + 0x2c));
    lv_free(*(undefined4 *)(param_1 + 0x34));
    iVar3 = lv_strdup(uVar2);
    *(int *)(param_1 + 0x34) = iVar3;
    if (iVar3 != 0) {
      if ((*(byte *)(param_1 + 0x70) & 4) != 0) {
        pwd_char_hider_part_5(param_1);
      }
      lv_textarea_clear_selection(param_1);
      refr_cursor_area(param_1);
      return;
    }
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/widgets/textarea/lv_textarea.c"
               ,0x20c,"lv_textarea_set_password_mode","Asserted at expression: %s (%s)",
               "ta->pwd_tmp != NULL","Out of memory");
    *in_zero = 0;
                    /* WARNING: Does not return */
    pcVar1 = (code *)trap(0);
    (*pcVar1)();
  }
  *(byte *)(param_1 + 0x70) = *(byte *)(param_1 + 0x70) & 0xfb;
  lv_textarea_clear_selection();
  lv_label_set_text(*(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x34));
  lv_free(*(undefined4 *)(param_1 + 0x34));
  *(undefined4 *)(param_1 + 0x34) = 0;
  refr_cursor_area(param_1);
  return;
}



// === update_obj_state @ 00432778 ===

void update_obj_state(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  uint *puVar6;
  undefined2 *puVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  uint uVar11;
  undefined4 uVar12;
  char cVar13;
  char *pcVar14;
  uint uVar15;
  undefined4 *puVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  undefined4 *puVar20;
  
  uVar18 = (uint)*(ushort *)(param_1 + 0x28);
  if (uVar18 != param_2) {
    uVar2 = lv_obj_style_state_compare(param_1,uVar18,param_2);
    if (uVar2 == 0) {
      *(short *)(param_1 + 0x28) = (short)param_2;
    }
    else {
      lv_obj_invalidate(param_1);
      *(short *)(param_1 + 0x28) = (short)param_2;
      lv_obj_update_layer_type(param_1);
      iVar3 = lv_malloc_zeroed(0x280);
      uVar1 = (uint)(*(int *)(param_1 + 0x28) << 6) >> 0x1a;
      if (uVar1 != 0) {
        puVar16 = *(undefined4 **)(param_1 + 0xc);
        uVar17 = 0;
        uVar15 = 0;
        do {
          uVar4 = puVar16[1];
          if (((uVar4 & 0xffff & ~param_2) == 0) && ((uVar4 & 0x2000000) == 0)) {
            uVar11 = (uint)*(byte *)((undefined4 *)*puVar16 + 2);
            pcVar14 = *(char **)*puVar16;
            if (uVar11 == 0xff) {
              if (*pcVar14 != '\0') {
                if (*pcVar14 == 'f') {
LAB_00432ac0:
                  puVar20 = *(undefined4 **)(pcVar14 + 4);
                  goto LAB_004329bc;
                }
                cVar13 = pcVar14[8];
                pcVar14 = pcVar14 + 8;
                while (cVar13 != '\0') {
                  if (cVar13 == 'f') goto LAB_00432ac0;
                  cVar13 = pcVar14[8];
                  pcVar14 = pcVar14 + 8;
                }
              }
            }
            else if (uVar11 != 0) {
              if (pcVar14[uVar11 * 4] != 'f') {
                uVar8 = 0;
                pcVar5 = pcVar14 + uVar11 * 4 + 1;
                do {
                  uVar8 = uVar8 + 1;
                  if (uVar11 == uVar8) goto LAB_004328c4;
                  cVar13 = *pcVar5;
                  pcVar5 = pcVar5 + 1;
                } while (cVar13 != 'f');
                pcVar14 = pcVar14 + uVar8 * 4;
              }
              puVar20 = *(undefined4 **)pcVar14;
LAB_004329bc:
              pcVar14 = (char *)*puVar20;
              cVar13 = *pcVar14;
              if ((cVar13 != '\0') && (uVar15 < 0x20)) {
                do {
                  puVar6 = (uint *)(iVar3 + 4);
                  uVar11 = 0;
                  if (uVar15 != 0) {
                    do {
                      uVar11 = uVar11 + 1;
                      if ((((char)puVar6[1] == cVar13) &&
                          ((*puVar6 & 0xff0000) == (uVar4 & 0xff0000))) &&
                         ((uVar4 & 0xffff) <= (*puVar6 & 0xffff))) goto LAB_00432a1c;
                      puVar6 = puVar6 + 5;
                    } while (uVar11 != uVar15);
                  }
                  iVar9 = uVar15 * 0x14;
                  uVar12 = puVar20[4];
                  uVar15 = uVar15 + 1;
                  puVar7 = (undefined2 *)(iVar9 + iVar3);
                  uVar10 = puVar20[2];
                  *puVar7 = (short)puVar20[3];
                  puVar7[1] = (short)uVar12;
                  *(undefined4 *)(puVar7 + 6) = uVar10;
                  *(char *)(puVar7 + 4) = *pcVar14;
                  uVar10 = puVar20[1];
                  *(uint *)(puVar7 + 2) = uVar4 & 0xffffff;
                  *(undefined4 *)(puVar7 + 8) = uVar10;
LAB_00432a1c:
                  pcVar14 = pcVar14 + 1;
                  cVar13 = *pcVar14;
                } while ((cVar13 != '\0') && (uVar15 != 0x20));
              }
            }
          }
LAB_004328c4:
          uVar17 = uVar17 + 1;
          if (uVar17 == uVar1) {
            if (uVar15 == 0) goto LAB_00432910;
            break;
          }
          puVar16 = puVar16 + 2;
        } while (uVar15 < 0x20);
        iVar9 = iVar3;
        do {
          iVar19 = iVar9 + 0x14;
          lv_obj_style_create_transition
                    (param_1,*(uint *)(iVar9 + 4) & 0xff0000,uVar18,param_2,iVar9);
          iVar9 = iVar19;
        } while (uVar15 * 0x14 + iVar3 != iVar19);
      }
LAB_00432910:
      lv_free(iVar3);
      if ((uVar2 & 0xfffffffd) == 1) {
        lv_obj_refresh_style(param_1,0xf0000,0xff);
        return;
      }
      if (uVar2 == 2) {
        lv_obj_invalidate(param_1);
        lv_obj_refresh_ext_draw_size(param_1);
        return;
      }
    }
  }
  return;
}



// === lv_obj_update_flag @ 00432d78 ===

void lv_obj_update_flag(undefined4 param_1,undefined4 param_2,int param_3)

{
  if (param_3 == 0) {
    lv_obj_remove_flag();
    return;
  }
  lv_obj_add_flag();
  return;
}



// === lv_event_get_key @ 00435964 ===

undefined4 lv_event_get_key(int param_1)

{
  undefined4 *puVar1;
  
  if (*(int *)(param_1 + 8) != 0x11) {
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/core/lv_obj_event.c"
               ,0xf5,"lv_event_get_key","Not interpreted with this event code");
    return 0;
  }
  puVar1 = (undefined4 *)lv_event_get_param();
  if (puVar1 != (undefined4 *)0x0) {
    return *puVar1;
  }
  return 0;
}



// === lv_event_get_rotary_diff @ 004359e0 ===

undefined4 lv_event_get_rotary_diff(int param_1)

{
  undefined4 *puVar1;
  
  if (*(int *)(param_1 + 8) != 0x12) {
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/core/lv_obj_event.c"
               ,0x102,"lv_event_get_rotary_diff","Not interpreted with this event code");
    return 0;
  }
  puVar1 = (undefined4 *)lv_event_get_param();
  if (puVar1 != (undefined4 *)0x0) {
    return *puVar1;
  }
  return 0;
}



// === layout_update_core @ 00438908 ===

void layout_update_core(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = lv_obj_get_child_count();
  if (iVar2 != 0) {
    iVar4 = 0;
    do {
      iVar3 = iVar4 * 4;
      iVar4 = iVar4 + 1;
      layout_update_core(*(undefined4 *)(**(int **)(param_1 + 8) + iVar3));
    } while (iVar2 != iVar4);
  }
  uVar1 = *(ushort *)(param_1 + 0x2a);
  if ((uVar1 & 1) != 0) {
    *(ushort *)(param_1 + 0x2a) = uVar1 & 0xfffe;
    if ((*(uint *)(param_1 + 0x28) & 0xc000000) == 0xc000000) {
      lv_obj_refr_pos(param_1);
    }
    else {
      lv_obj_refr_size_part_3(param_1);
      lv_obj_refr_pos(param_1);
    }
    if (iVar2 == 0) {
      uVar1 = *(ushort *)(param_1 + 0x2a);
    }
    else {
      lv_layout_apply(param_1);
      uVar1 = *(ushort *)(param_1 + 0x2a);
    }
  }
  if ((uVar1 & 2) == 0) {
    return;
  }
  *(ushort *)(param_1 + 0x2a) = *(ushort *)(param_1 + 0x2a) & 0xfffd;
  lv_obj_readjust_scroll(param_1,0);
  return;
}



// === lv_obj_update_layout.part.4 @ 00438a0c ===

void lv_obj_update_layout_part_4(void)

{
  ushort uVar1;
  int iVar2;
  
  DAT_0084d690 = 1;
  iVar2 = lv_obj_get_screen();
  uVar1 = *(ushort *)(iVar2 + 0x2a);
  while ((uVar1 & 4) != 0) {
    *(ushort *)(iVar2 + 0x2a) = *(ushort *)(iVar2 + 0x2a) & 0xfffb;
    layout_update_core(iVar2);
    uVar1 = *(ushort *)(iVar2 + 0x2a);
  }
  DAT_0084d690 = 0;
  return;
}



// === lv_obj_update_layout @ 00438a7c ===

void lv_obj_update_layout(void)

{
  if (DAT_0084d690 != '\0') {
    return;
  }
  lv_obj_update_layout_part_4();
  return;
}



// === lv_obj_update_snap @ 0043a94c ===

void lv_obj_update_snap(undefined4 param_1,undefined4 param_2)

{
  int local_18;
  int local_14;
  
  lv_obj_update_layout();
  lv_indev_scroll_get_snap_dist(param_1,&local_18);
  if ((local_18 == 0x1fffffff) || (local_18 == -0x1fffffff)) {
    local_18 = 0;
  }
  if ((local_14 == 0x1fffffff) || (local_14 == -0x1fffffff)) {
    local_14 = 0;
  }
  lv_obj_scroll_by(param_1,local_18,local_14,param_2);
  return;
}



// === lv_obj_enable_style_refresh @ 0043c164 ===

void lv_obj_enable_style_refresh(undefined1 param_1)

{
  DAT_0084d654 = param_1;
  return;
}



// === lv_obj_update_layer_type @ 0043ca00 ===

void lv_obj_update_layer_type(int param_1)

{
  int iVar1;
  short sVar2;
  short sVar3;
  int local_18 [3];
  
  lv_obj_get_style_prop(local_18,param_1,0,0x6e);
  if (local_18[0] == 0) {
    lv_obj_get_style_prop(local_18,param_1,0,0x6c);
    if (local_18[0] == 0x100) {
      lv_obj_get_style_prop(local_18,param_1,0,0x6d);
      if (((local_18[0] == 0x100) &&
          (lv_obj_get_style_prop(local_18,param_1,0,0x71), local_18[0] == 0)) &&
         (lv_obj_get_style_prop(local_18,param_1,0,0x72), local_18[0] == 0)) {
        lv_obj_get_style_prop(local_18,param_1,0,0x60);
        if ((((char)local_18[0] != -1) ||
            (lv_obj_get_style_prop(local_18,param_1,0,0x73), local_18[0] != 0)) ||
           (lv_obj_get_style_prop(local_18,param_1,0,0x67), local_18[0] != 0)) {
          iVar1 = *(int *)(param_1 + 8);
          sVar2 = 1;
          sVar3 = 1;
          if (iVar1 != 0) goto LAB_0043ca60;
          goto LAB_0043cac8;
        }
        iVar1 = *(int *)(param_1 + 8);
        sVar2 = 0;
        if (iVar1 == 0) {
          return;
        }
        goto LAB_0043ca60;
      }
      goto LAB_0043cab8;
    }
    iVar1 = *(int *)(param_1 + 8);
  }
  else {
LAB_0043cab8:
    iVar1 = *(int *)(param_1 + 8);
  }
  sVar2 = 2;
  if (iVar1 == 0) {
    sVar3 = 2;
LAB_0043cac8:
    lv_obj_allocate_spec_attr(param_1);
    *(ushort *)(*(int *)(param_1 + 8) + 0x2e) =
         *(ushort *)(*(int *)(param_1 + 8) + 0x2e) & 0xf3ff | sVar3 << 10;
    return;
  }
LAB_0043ca60:
  *(ushort *)(iVar1 + 0x2e) = *(ushort *)(iVar1 + 0x2e) & 0xf3ff | sVar2 << 10;
  return;
}



// === lv_obj_set_style_transform_rotation @ 0043e2b0 ===

void lv_obj_set_style_transform_rotation(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  lv_obj_set_local_style_prop(param_1,0x6e,param_2,param_3);
  return;
}



// === lv_obj_set_style_rotary_sensitivity @ 0043eac8 ===

void lv_obj_set_style_rotary_sensitivity(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  lv_obj_set_local_style_prop(param_1,0x74,param_2,param_3);
  return;
}



// === update_resolution @ 00443c58 ===

void update_resolution(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined1 auStack_28 [16];
  
  if (param_1 == (undefined4 *)0x0) {
    uVar4 = 0;
    uVar5 = 0;
    if (DAT_0084d644 == (undefined4 *)0x0) goto LAB_00443cb4;
    iVar1 = DAT_0084d644[0xc0];
    puVar2 = DAT_0084d644;
  }
  else {
    iVar1 = param_1[0xc0];
    puVar2 = param_1;
  }
  uVar3 = (uint)(iVar1 << 0x1d) >> 0x1e;
  if ((uVar3 == 1) || (uVar3 == 3)) {
    uVar4 = puVar2[1];
  }
  else {
    uVar4 = *puVar2;
  }
  if ((uVar3 == 1) || (uVar3 == 3)) {
    uVar5 = *puVar2;
  }
  else {
    uVar5 = puVar2[1];
  }
LAB_00443cb4:
  lv_obj_get_coords(param_1[0xb1],auStack_28);
  uVar3 = 0;
  if (param_1[0xb7] != 0) {
    do {
      iVar1 = uVar3 * 4;
      uVar3 = uVar3 + 1;
      lv_area_set_width(*(int *)(param_1[0xb0] + iVar1) + 0x14,uVar4);
      lv_area_set_height(*(int *)(param_1[0xb0] + iVar1) + 0x14,uVar5);
      lv_obj_send_event(*(undefined4 *)(param_1[0xb0] + iVar1),0x31,auStack_28);
    } while (uVar3 < (uint)param_1[0xb7]);
  }
  lv_area_set_width(param_1[0xb2] + 0x14,uVar4);
  lv_area_set_height(param_1[0xb2] + 0x14,uVar5);
  lv_obj_send_event(param_1[0xb2],0x31,auStack_28);
  lv_area_set_width(param_1[0xb1] + 0x14,uVar4);
  lv_area_set_height(param_1[0xb1] + 0x14,uVar5);
  lv_obj_send_event(param_1[0xb1],0x31,auStack_28);
  lv_area_set_width(param_1[0xb4] + 0x14,uVar4);
  lv_area_set_height(param_1[0xb4] + 0x14,uVar5);
  lv_obj_send_event(param_1[0xb4],0x31,auStack_28);
  lv_memset(param_1 + 0x12,0,0x200);
  lv_memset(param_1 + 0x92,0,0x20);
  param_1[0x9a] = 0;
  lv_obj_invalidate(param_1[0xb1]);
  lv_obj_tree_walk(0,invalidate_layout_cb,0);
  lv_display_send_event(param_1,0x36,0);
  return;
}



// === lv_display_set_rotation @ 00443ee8 ===

void lv_display_set_rotation(int param_1,byte param_2)

{
  if ((param_1 == 0) && (param_1 = DAT_0084d644, DAT_0084d644 == 0)) {
    return;
  }
  *(byte *)(param_1 + 0x300) = *(byte *)(param_1 + 0x300) & 0xf9 | (param_2 & 3) << 1;
  update_resolution(param_1);
  return;
}



// === lv_display_get_rotation @ 00443f1c ===

uint lv_display_get_rotation(int param_1)

{
  if (param_1 == 0) {
    param_1 = DAT_0084d644;
    if (DAT_0084d644 == 0) {
      return 0;
    }
  }
  return (uint)(*(int *)(param_1 + 0x300) << 0x1d) >> 0x1e;
}



// === lv_display_enable_invalidation @ 0044411c ===

void lv_display_enable_invalidation(int param_1,int param_2)

{
  int iVar1;
  
  if ((param_1 == 0) && (param_1 = DAT_0084d644, DAT_0084d644 == 0)) {
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/display/lv_display.c"
               ,0x366,"lv_display_enable_invalidation","no display registered");
    return;
  }
  iVar1 = -1;
  if (param_2 != 0) {
    iVar1 = 1;
  }
  *(int *)(param_1 + 0x26c) = *(int *)(param_1 + 0x26c) + iVar1;
  return;
}



// === lv_display_is_invalidation_enabled @ 0044418c ===

bool lv_display_is_invalidation_enabled(int param_1)

{
  if ((param_1 == 0) && (param_1 = DAT_0084d644, DAT_0084d644 == 0)) {
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/display/lv_display.c"
               ,0x371,"lv_display_is_invalidation_enabled","no display registered");
    return false;
  }
  return 0 < *(int *)(param_1 + 0x26c);
}



// === lv_display_rotate_area @ 0044433c ===

void lv_display_rotate_area(int *param_1,int *param_2)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  piVar2 = param_1;
  if ((param_1 == (int *)0x0) && (piVar2 = DAT_0084d644, DAT_0084d644 == (int *)0x0)) {
    lv_area_get_width(param_2);
    lv_area_get_height(param_2);
    return;
  }
  iVar6 = piVar2[0xc0];
  iVar3 = lv_area_get_width(param_2);
  uVar1 = (uint)(iVar6 << 0x1d) >> 0x1e;
  iVar6 = lv_area_get_height(param_2);
  if (uVar1 == 2) {
    iVar5 = (param_1[1] - param_2[1]) + -1;
    iVar4 = (*param_1 - *param_2) + -1;
    *param_2 = (iVar4 - iVar3) + 1;
    param_2[3] = iVar5;
    param_2[1] = (iVar5 - iVar6) + 1;
    param_2[2] = iVar4;
    return;
  }
  if (uVar1 < 3) {
    if (uVar1 == 1) {
      iVar4 = (param_1[1] - *param_2) + -1;
      param_2[3] = iVar4;
      *param_2 = param_2[1];
      param_2[2] = param_2[1] + iVar6 + -1;
      param_2[1] = (iVar4 - iVar3) + 1;
    }
    return;
  }
  iVar4 = (*param_1 - param_2[3]) + -1;
  param_2[1] = (param_2[2] - iVar3) + 1;
  *param_2 = iVar4;
  param_2[3] = param_2[2];
  param_2[2] = iVar4 + iVar6 + -1;
  return;
}



// === lv_draw_sw_rotate @ 0044ae14 ===

void lv_draw_sw_rotate(undefined4 *param_1,int param_2,int param_3,int param_4,uint param_5,
                      uint param_6,int param_7,undefined4 param_8)

{
  undefined1 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined4 *puVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  undefined1 *puVar10;
  undefined2 *puVar11;
  undefined4 uVar12;
  undefined4 *puVar13;
  int iVar14;
  
  if (param_7 != 1) {
    if (param_7 != 2) {
      if (param_7 != 3) {
        return;
      }
      switch(param_8) {
      case 6:
        goto switchD_0044aecc_caseD_6;
      case 7:
      case 8:
      case 9:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
        return;
      case 0xf:
        if (0 < param_3) {
          puVar10 = (undefined1 *)(param_2 + -3);
          puVar13 = (undefined4 *)(param_3 * 3 + (int)param_1);
          do {
            if (0 < param_4) {
              puVar8 = puVar10 + (param_4 + -1) * 3 + 3;
              puVar7 = param_1;
              do {
                puVar6 = puVar8 + -3;
                *puVar8 = *(undefined1 *)puVar7;
                puVar8[1] = *(undefined1 *)((int)puVar7 + 1);
                puVar11 = (undefined2 *)((int)puVar7 + 2);
                puVar7 = (undefined4 *)((int)puVar7 + param_5);
                puVar8[2] = *(undefined1 *)puVar11;
                puVar8 = puVar6;
              } while (puVar6 != puVar10);
            }
            param_1 = (undefined4 *)((int)param_1 + 3);
            puVar10 = puVar10 + param_6;
          } while (param_1 != puVar13);
          return;
        }
        return;
      case 0x10:
      case 0x11:
        if (0 < param_3) {
          puVar13 = (undefined4 *)(param_2 + param_4 * 4);
          iVar14 = 0;
          do {
            if (0 < param_4) {
              puVar7 = puVar13;
              puVar9 = param_1;
              do {
                uVar12 = *puVar9;
                puVar7 = puVar7 + -1;
                puVar9 = (undefined4 *)((int)puVar9 + (param_5 & 0xfffffffc));
                *puVar7 = uVar12;
              } while (puVar7 != puVar13 + -param_4);
            }
            iVar14 = iVar14 + 1;
            param_1 = param_1 + 1;
            puVar13 = (undefined4 *)((int)puVar13 + (param_6 & 0xfffffffc));
          } while (param_3 != iVar14);
          return;
        }
        return;
      case 0x12:
        if (param_3 < 1) {
          return;
        }
        puVar11 = (undefined2 *)(param_2 + param_4 * 2);
        puVar13 = (undefined4 *)((int)param_1 + param_3 * 2);
        do {
          if (0 < param_4) {
            puVar3 = puVar11;
            puVar7 = param_1;
            do {
              uVar2 = *(undefined2 *)puVar7;
              puVar3 = puVar3 + -1;
              puVar7 = (undefined4 *)((int)puVar7 + (param_5 & 0xfffffffe));
              *puVar3 = uVar2;
            } while (puVar3 != puVar11 + -param_4);
          }
          param_1 = (undefined4 *)((int)param_1 + 2);
          puVar11 = (undefined2 *)((int)puVar11 + (param_6 & 0xfffffffe));
        } while (param_1 != puVar13);
        return;
      default:
        return;
      }
    }
    switch(param_8) {
    case 6:
      goto switchD_0044ae6c_caseD_6;
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
      return;
    case 0xf:
      if (0 < param_4) {
        iVar14 = 0;
        puVar10 = (undefined1 *)(param_2 + param_3 * 3 + (param_4 + -1) * param_6 + -3);
        do {
          if (0 < param_3) {
            puVar8 = puVar10;
            puVar13 = param_1;
            do {
              puVar6 = puVar8 + -3;
              *puVar8 = *(undefined1 *)puVar13;
              puVar8[1] = *(undefined1 *)((int)puVar13 + 1);
              puVar8[2] = *(undefined1 *)((int)puVar13 + 2);
              puVar8 = puVar6;
              puVar13 = (undefined4 *)((int)puVar13 + 3);
            } while (puVar10 + param_3 * -3 != puVar6);
          }
          iVar14 = iVar14 + 1;
          param_1 = (undefined4 *)((int)param_1 + param_5);
          puVar10 = puVar10 + -param_6;
        } while (param_4 != iVar14);
        return;
      }
      return;
    case 0x10:
    case 0x11:
      param_5 = param_5 >> 2;
      if (0 < param_4) {
        iVar14 = 0;
        puVar13 = (undefined4 *)(param_2 + ((param_4 + -1) * param_5 + param_3) * 4);
        do {
          if (0 < param_3) {
            puVar7 = param_1;
            puVar9 = puVar13;
            do {
              uVar12 = *puVar7;
              puVar9 = puVar9 + -1;
              puVar7 = puVar7 + 1;
              *puVar9 = uVar12;
            } while (puVar7 != param_1 + param_3);
          }
          iVar14 = iVar14 + 1;
          param_1 = param_1 + param_5;
          puVar13 = puVar13 + -param_5;
        } while (param_4 != iVar14);
        return;
      }
      return;
    case 0x12:
      if (param_4 < 1) {
        return;
      }
      iVar14 = 0;
      puVar11 = (undefined2 *)(param_2 + ((param_4 + -1) * (param_6 >> 1) + param_3) * 2);
      do {
        if (0 < param_3) {
          puVar13 = param_1;
          puVar3 = puVar11;
          do {
            uVar2 = *(undefined2 *)puVar13;
            puVar3 = puVar3 + -1;
            puVar13 = (undefined4 *)((int)puVar13 + 2);
            *puVar3 = uVar2;
          } while (puVar13 != (undefined4 *)((int)param_1 + param_3 * 2));
        }
        iVar14 = iVar14 + 1;
        param_1 = (undefined4 *)((int)param_1 + (param_5 & 0xfffffffe));
        puVar11 = puVar11 + -(param_6 >> 1);
      } while (param_4 != iVar14);
      return;
    default:
      return;
    }
  }
  switch(param_8) {
  case 6:
    if (0 < param_3) {
      puVar13 = (undefined4 *)((int)param_1 + param_3);
      puVar10 = (undefined1 *)((param_3 + -1) * param_6 + param_2);
      do {
        if (0 < param_4) {
          puVar8 = puVar10;
          puVar7 = param_1;
          do {
            uVar1 = *(undefined1 *)puVar7;
            puVar6 = puVar8 + 1;
            puVar7 = (undefined4 *)((int)puVar7 + param_5);
            *puVar8 = uVar1;
            puVar8 = puVar6;
          } while (puVar6 != puVar10 + param_4);
        }
        param_1 = (undefined4 *)((int)param_1 + 1);
        puVar10 = puVar10 + -param_6;
      } while (puVar13 != param_1);
      return;
    }
    break;
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    return;
  case 0xf:
    if (0 < param_3) {
      puVar10 = (undefined1 *)((param_3 + -1) * param_6 + param_2);
      puVar13 = (undefined4 *)(param_3 * 3 + (int)param_1);
      do {
        if (0 < param_4) {
          puVar8 = puVar10;
          puVar7 = param_1;
          do {
            puVar6 = puVar8 + 3;
            *puVar8 = *(undefined1 *)puVar7;
            puVar8[1] = *(undefined1 *)((int)puVar7 + 1);
            puVar11 = (undefined2 *)((int)puVar7 + 2);
            puVar7 = (undefined4 *)((int)puVar7 + param_5);
            puVar8[2] = *(undefined1 *)puVar11;
            puVar8 = puVar6;
          } while (puVar10 + param_4 * 3 != puVar6);
        }
        param_1 = (undefined4 *)((int)param_1 + 3);
        puVar10 = puVar10 + -param_6;
      } while (puVar13 != param_1);
      return;
    }
    break;
  case 0x10:
  case 0x11:
    if (0 < param_3) {
      iVar14 = 0;
      puVar13 = (undefined4 *)((param_3 + -1) * (param_6 >> 2) * 4 + param_2);
      do {
        if (0 < param_4) {
          puVar7 = puVar13;
          puVar9 = param_1;
          do {
            uVar12 = *puVar9;
            puVar5 = puVar7 + 1;
            puVar9 = (undefined4 *)((int)puVar9 + (param_5 & 0xfffffffc));
            *puVar7 = uVar12;
            puVar7 = puVar5;
          } while (puVar13 + param_4 != puVar5);
        }
        iVar14 = iVar14 + 1;
        param_1 = param_1 + 1;
        puVar13 = puVar13 + -(param_6 >> 2);
      } while (param_3 != iVar14);
      return;
    }
    return;
  case 0x12:
    if (param_3 < 1) {
      return;
    }
    puVar13 = (undefined4 *)((int)param_1 + param_3 * 2);
    puVar11 = (undefined2 *)((param_3 + -1) * (param_6 >> 1) * 2 + param_2);
    do {
      if (0 < param_4) {
        puVar3 = puVar11;
        puVar7 = param_1;
        do {
          uVar2 = *(undefined2 *)puVar7;
          puVar4 = puVar3 + 1;
          puVar7 = (undefined4 *)((int)puVar7 + (param_5 & 0xfffffffe));
          *puVar3 = uVar2;
          puVar3 = puVar4;
        } while (puVar11 + param_4 != puVar4);
      }
      param_1 = (undefined4 *)((int)param_1 + 2);
      puVar11 = puVar11 + -(param_6 >> 1);
    } while (puVar13 != param_1);
    return;
  }
  return;
switchD_0044aecc_caseD_6:
  if (0 < param_3) {
    puVar10 = (undefined1 *)(param_2 + param_4);
    puVar13 = (undefined4 *)((int)param_1 + param_3);
    do {
      if (0 < param_4) {
        puVar8 = puVar10;
        puVar7 = param_1;
        do {
          uVar1 = *(undefined1 *)puVar7;
          puVar8 = puVar8 + -1;
          puVar7 = (undefined4 *)((int)puVar7 + param_5);
          *puVar8 = uVar1;
        } while (puVar8 != puVar10 + -param_4);
      }
      param_1 = (undefined4 *)((int)param_1 + 1);
      puVar10 = puVar10 + param_6;
    } while (param_1 != puVar13);
    return;
  }
  return;
switchD_0044ae6c_caseD_6:
  if (0 < param_4) {
    iVar14 = 0;
    puVar10 = (undefined1 *)(param_2 + (param_4 + -1) * param_6 + param_3 + -1);
    do {
      if (0 < param_3) {
        puVar13 = param_1;
        puVar8 = puVar10;
        do {
          uVar1 = *(undefined1 *)puVar13;
          puVar13 = (undefined4 *)((int)puVar13 + 1);
          *puVar8 = uVar1;
          puVar8 = puVar8 + -1;
        } while (puVar13 != (undefined4 *)((int)param_1 + param_3));
      }
      iVar14 = iVar14 + 1;
      param_1 = (undefined4 *)((int)param_1 + param_5);
      puVar10 = puVar10 + -param_6;
    } while (param_4 != iVar14);
    return;
  }
  return;
}



// === lv_indev_enable @ 00456470 ===

void lv_indev_enable(int param_1,uint param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    for (iVar1 = lv_ll_get_head(&DAT_0084d674); iVar1 != 0; iVar1 = lv_indev_get_next(iVar1)) {
      *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) & 0xfb | (byte)((param_2 & 1) << 2);
    }
    return;
  }
  *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) & 0xfb | (byte)((param_2 & 1) << 2);
  return;
}



// === lv_indev_get_key @ 0045681c ===

int lv_indev_get_key(int *param_1)

{
  if (param_1 == (int *)0x0) {
    return 0;
  }
  if (*param_1 != 2) {
    return 0;
  }
  return param_1[0x2e];
}



// === flex_update @ 0045b350 ===

/* WARNING: Removing unreachable block (ram,0x0045bdc4) */
/* WARNING: Removing unreachable block (ram,0x0045ba00) */
/* WARNING: Removing unreachable block (ram,0x0045ba34) */
/* WARNING: Removing unreachable block (ram,0x0045bd70) */

void flex_update(int param_1)

{
  int *piVar1;
  ushort uVar2;
  code *pcVar3;
  bool bVar4;
  uint uVar5;
  undefined4 *in_zero;
  uint uVar6;
  undefined4 uVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  uint local_f0;
  int local_ec;
  int local_e8;
  undefined4 local_e4;
  int *local_e0;
  int local_dc;
  byte local_d8;
  uint local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  uint local_c4;
  uint local_c0;
  uint local_bc;
  uint local_b8;
  int local_b4;
  int local_b0;
  uint local_ac;
  int local_a8;
  int local_a4;
  int local_a0 [2];
  code *local_98;
  code *local_94;
  uint local_90;
  int local_8c;
  int local_88;
  code *local_84;
  uint local_80;
  code *local_7c;
  code *local_78;
  code *local_74;
  uint local_70;
  uint local_6c;
  int *local_68;
  undefined4 local_64;
  code *local_60;
  uint local_5c;
  uint *local_58;
  code *local_54;
  code *local_50;
  code *local_4c;
  code *local_48;
  code *local_44;
  code *local_40;
  code *local_3c;
  code *local_38;
  uint local_34;
  uint local_30;
  
  lv_obj_get_style_prop(&local_f0,param_1,0,0x7d);
  local_b8 = CONCAT31(local_b8._1_3_,
                      (byte)local_b8 & 0xf8 | ~(byte)local_f0 & 1 | (byte)((local_f0 >> 2 & 1) << 1)
                      | (byte)((local_f0 >> 3 & 1) << 2));
  lv_obj_get_style_prop(&local_f0,param_1,0,0x7e);
  local_c4 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x7f);
  local_c0 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x80);
  local_bc = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x27);
  local_6c = local_f0;
  if ((local_b8 & 1) == 0) {
    lv_obj_get_style_prop(&local_f0,param_1,0,0x15);
  }
  else {
    lv_obj_get_style_prop(&local_f0,param_1,0,0x14);
  }
  local_5c = local_f0;
  if ((local_b8 & 1) == 0) {
    lv_obj_get_style_prop(&local_f0,param_1,0,0x14);
  }
  else {
    lv_obj_get_style_prop(&local_f0,param_1,0,0x15);
  }
  local_90 = local_f0;
  if ((local_b8 & 1) == 0) {
    local_64 = lv_obj_get_content_height(param_1);
  }
  else {
    local_64 = lv_obj_get_content_width();
  }
  iVar15 = *(int *)(param_1 + 0x18);
  lv_obj_get_style_prop(&local_f0,param_1,0,0x10);
  uVar12 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x30);
  uVar16 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x34);
  if ((local_f0 & 2) != 0) {
    uVar12 = uVar12 + uVar16;
  }
  local_a0[0] = lv_obj_get_scroll_y(param_1);
  local_a0[0] = (iVar15 + uVar12) - local_a0[0];
  iVar15 = *(int *)(param_1 + 0x14);
  lv_obj_get_style_prop(&local_f0,param_1,0,0x12);
  uVar12 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x30);
  uVar16 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,0x34);
  if ((local_f0 & 4) != 0) {
    uVar12 = uVar12 + uVar16;
  }
  local_a4 = lv_obj_get_scroll_x(param_1);
  uVar16 = local_bc;
  local_a4 = (iVar15 + uVar12) - local_a4;
  local_68 = &local_a4;
  if ((local_b8 & 1) != 0) {
    local_68 = local_a0;
  }
  lv_obj_get_style_prop(&local_f0,param_1,0,1);
  local_34 = local_f0;
  lv_obj_get_style_prop(&local_f0,param_1,0,2);
  uVar5 = local_5c;
  uVar7 = local_64;
  uVar12 = local_90;
  uVar6 = local_b8 & 0xff;
  uVar11 = local_b8 & 1;
  local_30 = local_f0;
  if ((local_b8 & 1) == 0) {
    if ((local_34 != 0x3fffffff) || ((*(ushort *)(param_1 + 0x2a) & 0x800) != 0)) {
      if (local_6c != 1) goto LAB_0045b5e0;
      if (uVar16 == 0) goto LAB_0045c11c;
      local_a8 = 0;
      if (uVar16 == 1) {
        iVar15 = 0;
        goto LAB_0045b6b4;
      }
      goto LAB_0045b5ec;
    }
    if (local_6c != 1) goto LAB_0045c0f4;
LAB_0045c11c:
    uVar16 = 1;
    uVar2 = *(ushort *)(*(int *)(param_1 + 8) + 0x2c);
  }
  else {
    if ((local_f0 == 0x3fffffff) && ((*(ushort *)(param_1 + 0x2a) & 0x400) == 0)) {
LAB_0045c0f4:
      local_a8 = 0;
      iVar15 = 0;
      goto LAB_0045b6b4;
    }
LAB_0045b5e0:
    local_a8 = 0;
    iVar15 = 0;
    if (uVar16 == 0) goto LAB_0045b6b4;
LAB_0045b5ec:
    uVar2 = *(ushort *)(*(int *)(param_1 + 8) + 0x2c);
  }
  uVar6 = 0;
  if ((local_b8 & 4) != 0) {
    uVar6 = uVar2 - 1;
  }
  local_a8 = 0;
  iVar17 = 0;
  iVar15 = 0;
  if (uVar2 != 0) {
    do {
      local_d8 = local_d8 & 0xfe;
      uVar6 = find_track_end(param_1,&local_c4,uVar6,uVar7,uVar12,&local_f0);
      iVar17 = iVar17 + 1;
      iVar15 = iVar15 + uVar5 + local_f0;
    } while (uVar6 < *(ushort *)(*(int *)(param_1 + 8) + 0x2c));
    uVar11 = local_b8 & 1;
    if (iVar17 != 0) {
      iVar15 = iVar15 - local_5c;
    }
  }
  if (uVar11 == 0) {
    uVar7 = lv_obj_get_content_width();
  }
  else {
    uVar7 = lv_obj_get_content_height(param_1);
  }
  place_content(uVar16,uVar7,iVar15,iVar17,local_68,&local_a8);
  uVar6 = local_b8 & 0xff;
LAB_0045b6b4:
  uVar12 = (uint)*(ushort *)(*(int *)(param_1 + 8) + 0x2c);
  if ((uVar6 & 4) == 0) {
    uVar16 = 0;
  }
  else {
    uVar16 = uVar12 - 1;
  }
  if ((local_6c == 1) && ((uVar6 & 1) == 0)) {
    *local_68 = *local_68 + iVar15;
  }
  if (uVar16 < uVar12) {
    local_50 = lv_obj_get_style_margin_bottom;
    local_40 = lv_obj_get_style_margin_top;
    local_44 = lv_obj_get_style_margin_left;
    local_48 = lv_area_get_width;
    local_54 = lv_area_get_height;
    local_4c = lv_obj_get_style_margin_right;
    local_3c = lv_area_set_width;
    local_58 = &local_c4;
    local_38 = lv_area_set_height;
    do {
      local_d8 = local_d8 & 0xfe | 1;
      uVar12 = find_track_end(param_1,local_58,uVar16,local_64,local_90,&local_f0);
      if (local_6c == 1) {
        if ((local_b8 & 1) == 0) {
          local_84 = local_50;
          *local_68 = *local_68 - local_f0;
          goto LAB_0045b7b4;
        }
LAB_0045bf50:
        local_88 = local_a0[0];
        local_8c = local_a4;
        local_84 = local_4c;
        local_98 = local_44;
        local_74 = local_40;
        local_78 = local_54;
        local_60 = local_3c;
        local_94 = local_48;
        local_7c = local_50;
      }
      else {
        if ((local_b8 & 1) != 0) goto LAB_0045bf50;
        local_84 = local_50;
LAB_0045b7b4:
        local_98 = local_40;
        local_74 = local_44;
        local_78 = local_48;
        local_60 = local_38;
        local_94 = local_54;
        local_7c = local_4c;
        local_8c = local_a4;
        local_88 = local_a0[0];
      }
      do {
        local_ac = uVar16;
        local_a4 = local_8c;
        local_a0[0] = local_88;
        if (local_dc == 0) break;
        iVar17 = 0;
        piVar8 = local_e0;
        iVar15 = local_ec - local_e8;
        do {
          while ((*(byte *)(piVar8 + 5) & 1) == 0) {
            piVar1 = piVar8 + 4;
            piVar8 = piVar8 + 6;
            iVar17 = iVar17 + *piVar1;
            if (local_e0 + local_dc * 6 == piVar8) goto LAB_0045b848;
          }
          piVar1 = piVar8 + 3;
          piVar8 = piVar8 + 6;
          iVar15 = iVar15 - *piVar1;
        } while (local_e0 + local_dc * 6 != piVar8);
LAB_0045b848:
        bVar4 = false;
        iVar13 = 0;
        piVar8 = local_e0;
        do {
          if ((*(byte *)(piVar8 + 5) & 1) == 0) {
            if (iVar17 == 0) {
              lv_log_add(2,3,
                         "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/layouts/flex/lv_flex.c"
                         ,0x15d,"children_repos","Asserted at expression: %s","grow_value_sum != 0")
              ;
              *in_zero = 0;
                    /* WARNING: Does not return */
              pcVar3 = (code *)trap(0);
              (*pcVar3)();
            }
            if (iVar17 == 0) {
              trap(7);
            }
            iVar9 = (iVar15 / iVar17) * piVar8[4];
            iVar10 = piVar8[2];
            if (iVar9 < piVar8[2]) {
              iVar10 = iVar9;
            }
            iVar14 = piVar8[1];
            if (piVar8[1] <= iVar10) {
              iVar14 = iVar10;
            }
            if (iVar9 != iVar14) {
              *(byte *)(piVar8 + 5) = *(byte *)(piVar8 + 5) & 0xfe | 1;
              bVar4 = true;
            }
            piVar8[3] = iVar14;
            iVar17 = iVar17 - piVar8[4];
            iVar15 = iVar15 - iVar14;
          }
          iVar13 = iVar13 + 1;
          piVar8 = piVar8 + 6;
        } while (local_dc != iVar13);
      } while (bVar4);
      lv_obj_get_style_prop(&local_d4,param_1,0,0x27);
      local_80 = local_d4;
      local_b0 = 0;
      local_b4 = 0;
      place_content(local_c4,local_64,local_ec,local_e4,&local_b0,&local_b4);
      if (((local_b8 & 1) != 0) && (local_80 == 1)) {
        iVar15 = lv_obj_get_content_width(param_1,local_ac);
        local_b0 = local_b0 + iVar15;
      }
      iVar15 = lv_obj_get_child(param_1,local_ac);
      if ((iVar15 != 0) && (local_ac != uVar12)) {
        local_70 = 0x9fffffff;
        do {
          iVar17 = lv_obj_has_flag_any(iVar15,0x60001);
          if (iVar17 == 0) {
            lv_obj_get_style_prop(&local_d4,iVar15,0,0x81);
            if ((char)local_d4 == '\0') {
              *(ushort *)(iVar15 + 0x2a) = *(ushort *)(iVar15 + 0x2a) & 0xf3ff;
LAB_0045b9c4:
              if (local_c0 == 1) goto LAB_0045bcf8;
LAB_0045b9d4:
              if (local_c0 == 2) {
                uVar16 = local_f0 + 1;
                iVar17 = (*local_78)(iVar15 + 0x14);
                iVar13 = (*local_74)(iVar15,0);
                iVar9 = (*local_7c)(iVar15,0);
                iVar17 = (iVar13 - iVar9) / 2 + (int)((uVar16 & 0xfffffffe) - iVar17) / 2;
              }
              else {
                iVar17 = (*local_74)(iVar15,0);
              }
            }
            else {
              if (local_dc == 0) {
LAB_0045bc44:
                iVar17 = 0;
              }
              else {
                piVar8 = local_e0;
                if (iVar15 != *local_e0) {
                  iVar17 = 0;
                  do {
                    piVar8 = piVar8 + 6;
                    iVar17 = iVar17 + 1;
                    if (local_dc == iVar17) goto LAB_0045bc44;
                  } while (*piVar8 != iVar15);
                }
                iVar17 = piVar8[3];
              }
              if ((local_b8 & 1) == 0) {
                *(ushort *)(iVar15 + 0x2a) = *(ushort *)(iVar15 + 0x2a) & 0xf3ff | 0x400;
              }
              else {
                *(ushort *)(iVar15 + 0x2a) = *(ushort *)(iVar15 + 0x2a) & 0xf3ff | 0x800;
              }
              iVar13 = (*local_94)(iVar15 + 0x14);
              if (iVar13 == iVar17) goto LAB_0045b9c4;
              lv_obj_invalidate(iVar15);
              local_d4 = *(uint *)(iVar15 + 0x14);
              local_d0 = *(undefined4 *)(iVar15 + 0x18);
              local_cc = *(undefined4 *)(iVar15 + 0x1c);
              local_c8 = *(undefined4 *)(iVar15 + 0x20);
              (*local_60)(iVar15 + 0x14,iVar17);
              lv_obj_send_event(iVar15,0x31,&local_d4);
              uVar7 = lv_obj_get_parent(iVar15);
              lv_obj_send_event(uVar7,0x2a,iVar15);
              lv_obj_invalidate(iVar15);
              if (local_c0 != 1) goto LAB_0045b9d4;
LAB_0045bcf8:
              uVar16 = local_f0;
              iVar13 = (*local_78)(iVar15 + 0x14);
              iVar17 = (*local_7c)(iVar15,0);
              iVar17 = (uVar16 - iVar13) - iVar17;
            }
            if (((local_b8 & 1) != 0) && (local_80 == 1)) {
              iVar13 = (*local_94)(iVar15 + 0x14,iVar15);
              local_b0 = local_b0 - iVar13;
            }
            lv_obj_get_style_prop(&local_d4,iVar15,0,0x6a);
            uVar16 = local_d4;
            lv_obj_get_style_prop(&local_d4,iVar15,0,0x6b);
            uVar5 = local_d4;
            iVar13 = lv_obj_get_width(iVar15);
            iVar9 = lv_obj_get_height(iVar15);
            if (((uVar16 & 0x60000000) == 0x20000000) &&
               (uVar6 = uVar16 & local_70, uVar6 != 0x1fffffff)) {
              if (0xfffffff < (int)uVar6) {
                uVar6 = 0xfffffff - uVar6;
              }
              uVar16 = (int)(iVar13 * uVar6) / 100;
            }
            if (((uVar5 & 0x60000000) == 0x20000000) &&
               (uVar6 = uVar5 & local_70, uVar6 != 0x1fffffff)) {
              if (0xfffffff < (int)uVar6) {
                uVar6 = 0xfffffff - uVar6;
              }
              iVar13 = (local_8c - *(int *)(iVar15 + 0x14)) + uVar16;
              iVar9 = (local_88 - *(int *)(iVar15 + 0x18)) + (int)(iVar9 * uVar6) / 100;
              if ((local_b8 & 1) != 0) goto LAB_0045bb08;
LAB_0045bd88:
              iVar13 = iVar13 + iVar17;
LAB_0045bb30:
              iVar17 = (*local_98)(iVar15,0);
              iVar17 = iVar17 + local_b0;
            }
            else {
              iVar13 = (local_8c - *(int *)(iVar15 + 0x14)) + uVar16;
              iVar9 = (local_88 - *(int *)(iVar15 + 0x18)) + uVar5;
              if ((local_b8 & 1) == 0) goto LAB_0045bd88;
LAB_0045bb08:
              iVar10 = (*local_98)(iVar15,0);
              iVar13 = iVar10 + local_b0 + iVar13;
              if ((local_b8 & 1) == 0) goto LAB_0045bb30;
            }
            iVar9 = iVar9 + iVar17;
            if (iVar9 != 0 || iVar13 != 0) {
              lv_obj_invalidate(iVar15);
              *(int *)(iVar15 + 0x20) = *(int *)(iVar15 + 0x20) + iVar9;
              *(int *)(iVar15 + 0x14) = *(int *)(iVar15 + 0x14) + iVar13;
              *(int *)(iVar15 + 0x1c) = *(int *)(iVar15 + 0x1c) + iVar13;
              *(int *)(iVar15 + 0x18) = *(int *)(iVar15 + 0x18) + iVar9;
              lv_obj_invalidate(iVar15);
              lv_obj_move_children_by(iVar15,iVar13,iVar9,0);
            }
            if (((local_b8 & 1) == 0) || (local_80 != 1)) {
              iVar17 = (*local_94)(iVar15 + 0x14);
              iVar13 = local_90 + iVar17 + local_b4;
              iVar17 = (*local_98)(iVar15,0);
              iVar15 = (*local_84)(iVar15,0);
              local_b0 = local_b0 + iVar13 + iVar17 + iVar15;
            }
            else {
              local_b0 = local_b0 - (local_90 + local_b4);
            }
          }
          iVar15 = get_next_item_isra_0(param_1 + 8,(local_b8 << 0x1d) >> 0x1f,&local_ac);
        } while ((iVar15 != 0) && (uVar12 != local_ac));
      }
      lv_free(local_e0);
      local_e0 = (int *)0x0;
      if (local_6c == 1) {
        iVar15 = *local_68;
        if ((local_b8 & 1) != 0) goto LAB_0045be90;
        *local_68 = iVar15 - (local_5c + local_a8);
      }
      else {
        iVar15 = *local_68;
LAB_0045be90:
        *local_68 = local_a8 + local_f0 + local_5c + iVar15;
      }
      uVar16 = uVar12;
    } while (uVar12 < *(ushort *)(*(int *)(param_1 + 8) + 0x2c));
  }
  if ((local_34 == 0x3fffffff) || (local_30 == 0x3fffffff)) {
    lv_obj_refr_size(param_1);
  }
  lv_obj_send_event(param_1,0x33,0);
  return;
}



// === lv_cache_is_enabled @ 00462cd8 ===

bool lv_cache_is_enabled(int param_1)

{
  return *(int *)(param_1 + 8) != 0;
}



// === lv_image_cache_is_enabled @ 00464810 ===

void lv_image_cache_is_enabled(void)

{
  lv_cache_is_enabled(DAT_0084d74c);
  return;
}



// === lv_image_header_cache_is_enabled @ 00464c80 ===

void lv_image_header_cache_is_enabled(void)

{
  lv_cache_is_enabled(DAT_0084d750);
  return;
}



// === lv_array_assign @ 00466498 ===

bool lv_array_assign(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = lv_array_at();
  if (iVar1 != 0) {
    lv_memcpy(iVar1,param_3,*(undefined4 *)(param_1 + 0xc));
  }
  return iVar1 != 0;
}



// === lv_matrix_rotate @ 00468244 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void lv_matrix_rotate(undefined4 param_1,float param_2)

{
  float local_48;
  float local_44;
  undefined4 local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_c;
  
  local_c = 0;
  local_18 = param_1;
  sincosf((param_2 / DAT_00585fe4) * _DAT_005901e0,&local_20,&local_1c);
  local_c = 0;
  local_48 = local_1c;
  local_38 = local_1c;
  local_44 = -local_20;
  local_3c = local_20;
  local_28 = DAT_00586c20;
  local_40 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  lv_matrix_multiply(local_18,&local_48);
  return;
}



// === lv_style_set_transform_rotation @ 0046a980 ===

void lv_style_set_transform_rotation(undefined4 param_1,undefined4 param_2)

{
  lv_style_set_prop(param_1,0x6e,param_2);
  return;
}



// === lv_style_set_rotary_sensitivity @ 0046b060 ===

void lv_style_set_rotary_sensitivity(undefined4 param_1,undefined4 param_2)

{
  lv_style_set_prop(param_1,0x74,param_2);
  return;
}



// === lv_image_get_rotation @ 0046c5d8 ===

undefined4 lv_image_get_rotation(int param_1)

{
  return *(undefined4 *)(param_1 + 0x44);
}



// === scale_update @ 0046c630 ===

void scale_update(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined1 auStack_20 [8];
  
  lv_obj_update_layout();
  uVar1 = lv_obj_get_width(param_1);
  uVar2 = lv_obj_get_height(param_1);
  lv_image_get_pivot(param_1,auStack_20);
  lv_image_buf_get_transformed_area
            (&local_30,uVar1,uVar2,*(undefined4 *)(param_1 + 0x44),*(undefined2 *)(param_1 + 0x48),
             *(undefined2 *)(param_1 + 0x4c),auStack_20);
  local_30 = local_30 + *(int *)(param_1 + 0x14) + -1;
  local_2c = local_2c + *(int *)(param_1 + 0x18) + -1;
  local_28 = local_28 + *(int *)(param_1 + 0x14) + 1;
  local_24 = local_24 + *(int *)(param_1 + 0x18) + 1;
  lv_obj_invalidate_area(param_1,&local_30);
  *(undefined4 *)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x4c) = param_3;
  uVar3 = lv_obj_get_display(param_1);
  lv_display_enable_invalidation(uVar3,0);
  lv_obj_refresh_ext_draw_size(param_1);
  lv_display_enable_invalidation(uVar3,1);
  lv_image_buf_get_transformed_area
            (&local_30,uVar1,uVar2,*(undefined4 *)(param_1 + 0x44),*(undefined2 *)(param_1 + 0x48),
             *(undefined2 *)(param_1 + 0x4c),auStack_20);
  local_2c = local_2c + *(int *)(param_1 + 0x18) + -1;
  local_28 = local_28 + *(int *)(param_1 + 0x14) + 1;
  local_30 = local_30 + *(int *)(param_1 + 0x14) + -1;
  local_24 = local_24 + *(int *)(param_1 + 0x18) + 1;
  lv_obj_invalidate_area(param_1,&local_30);
  return;
}



// === lv_image_set_rotation @ 0046c87c ===

void lv_image_set_rotation(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined1 auStack_20 [12];
  
  iVar5 = 0;
  if ((uint)(*(int *)(param_1 + 0x58) << 0x14) >> 0x1c < 0xb) {
    if (param_2 < 0xe10) {
      for (; param_2 < 0; param_2 = param_2 + 0xe10) {
      }
      iVar1 = *(int *)(param_1 + 0x44);
      goto LAB_0046c8d0;
    }
    do {
      param_2 = param_2 + -0xe10;
      iVar5 = param_2;
    } while (0xe0f < param_2);
  }
  iVar1 = *(int *)(param_1 + 0x44);
  param_2 = iVar5;
LAB_0046c8d0:
  if (iVar1 != param_2) {
    lv_obj_update_layout(param_1);
    uVar2 = lv_obj_get_width(param_1);
    uVar3 = lv_obj_get_height(param_1);
    lv_image_get_pivot(param_1,auStack_20);
    lv_image_buf_get_transformed_area
              (&local_30,uVar2,uVar3,*(undefined4 *)(param_1 + 0x44),*(undefined2 *)(param_1 + 0x48)
               ,*(undefined2 *)(param_1 + 0x4c),auStack_20);
    local_30 = local_30 + *(int *)(param_1 + 0x14);
    local_28 = local_28 + *(int *)(param_1 + 0x14);
    local_2c = local_2c + *(int *)(param_1 + 0x18);
    local_24 = local_24 + *(int *)(param_1 + 0x18);
    lv_obj_invalidate_area(param_1,&local_30);
    *(int *)(param_1 + 0x44) = param_2;
    uVar4 = lv_obj_get_display(param_1);
    lv_display_enable_invalidation(uVar4,0);
    lv_obj_refresh_ext_draw_size(param_1);
    lv_display_enable_invalidation(uVar4,1);
    lv_image_buf_get_transformed_area
              (&local_30,uVar2,uVar3,*(undefined4 *)(param_1 + 0x44),*(undefined2 *)(param_1 + 0x48)
               ,*(undefined2 *)(param_1 + 0x4c),auStack_20);
    local_30 = local_30 + *(int *)(param_1 + 0x14);
    local_28 = local_28 + *(int *)(param_1 + 0x14);
    local_2c = local_2c + *(int *)(param_1 + 0x18);
    local_24 = local_24 + *(int *)(param_1 + 0x18);
    lv_obj_invalidate_area(param_1,&local_30);
  }
  return;
}



// === update_align @ 0046cc04 ===

void update_align(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = *(ushort *)(param_1 + 0x58) & 0xf00;
  if (uVar1 == 0xb00) {
    lv_image_set_rotation(param_1,0);
    lv_image_set_pivot(param_1,0,0);
    iVar2 = lv_obj_get_width(param_1);
    iVar4 = *(int *)(param_1 + 0x3c);
    if (iVar4 == 0) {
      trap(7);
    }
    iVar3 = lv_obj_get_height(param_1);
    if (*(int *)(param_1 + 0x40) == 0) {
      trap(7);
    }
    scale_update(param_1,(iVar2 << 8) / iVar4,(iVar3 << 8) / *(int *)(param_1 + 0x40));
    return;
  }
  if (uVar1 != 0xc00) {
    return;
  }
  lv_image_set_rotation(param_1,0);
  lv_image_set_pivot(param_1,0,0);
  scale_update(param_1,0x100,0x100);
  return;
}



// === lv_vector_dsc_rotate @ 0046faa8 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void lv_vector_dsc_rotate(int param_1,float param_2)

{
  float fStack_48;
  float fStack_44;
  undefined4 uStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_20;
  float fStack_1c;
  int iStack_18;
  undefined4 uStack_c;
  
  iStack_18 = param_1 + 0x154;
  uStack_c = 0;
  sincosf((param_2 / DAT_00585fe4) * _DAT_005901e0,&fStack_20,&fStack_1c);
  uStack_c = 0;
  fStack_48 = fStack_1c;
  fStack_38 = fStack_1c;
  fStack_44 = -fStack_20;
  fStack_3c = fStack_20;
  uStack_28 = DAT_00586c20;
  uStack_40 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  lv_matrix_multiply(iStack_18,&fStack_48);
  return;
}



// === grid_update @ 00482514 ===

/* WARNING: Removing unreachable block (ram,0x00483574) */
/* WARNING: Removing unreachable block (ram,0x00482a70) */
/* WARNING: Removing unreachable block (ram,0x004827b8) */
/* WARNING: Removing unreachable block (ram,0x00483774) */
/* WARNING: Removing unreachable block (ram,0x00483688) */
/* WARNING: Removing unreachable block (ram,0x004836d0) */
/* WARNING: Removing unreachable block (ram,0x004835b0) */

void grid_update(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  int *piVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  int iVar10;
  uint *puVar11;
  int iVar12;
  int iVar13;
  uint *puVar14;
  uint *local_88;
  int local_84;
  uint *local_80;
  uint *local_7c;
  uint *local_78;
  uint *local_74;
  undefined4 local_70;
  undefined4 local_6c;
  uint *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 auStack_58 [8];
  int local_50;
  int local_4c;
  int local_48;
  uint local_44;
  uint *local_40;
  uint *local_3c;
  uint *local_38;
  int local_34;
  int local_30;
  
  iVar1 = lv_obj_get_child(param_1,0);
  if (iVar1 == 0) {
    lv_memset(&local_88,0,0x20);
    goto LAB_00482c08;
  }
  lv_obj_get_style_prop(&local_88,param_1,0,0x84);
  local_3c = (uint *)0x0;
  puVar8 = local_88;
  if (local_88 == (uint *)0x0) {
    uVar2 = lv_obj_get_parent(param_1);
    lv_obj_get_style_prop(&local_88,uVar2,0,0x84);
    puVar14 = local_88;
    if (local_88 != (uint *)0x0) {
      lv_obj_get_style_prop(&local_88,param_1,0,0x89);
      puVar7 = local_88;
      lv_obj_get_style_prop(&local_88,param_1,0,0x8a);
      puVar11 = local_88;
      iVar1 = ((int)local_88 + 1) * 4;
      puVar8 = (uint *)lv_malloc(iVar1);
      lv_memcpy(puVar8,puVar14 + (int)puVar7,iVar1 + -4);
      puVar8[(int)puVar11] = 0x1fffffff;
      local_3c = (uint *)0x1;
      goto LAB_00482570;
    }
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/layouts/grid/lv_grid.c"
               ,0x179,"calc_rows","No row descriptor found even on the parent");
  }
  else {
LAB_00482570:
    if (*puVar8 == 0x1fffffff) {
      iVar1 = 0;
      local_74 = (uint *)0x0;
    }
    else {
      local_74 = (uint *)0x0;
      puVar14 = puVar8;
      do {
        puVar14 = puVar14 + 1;
        local_74 = (uint *)((int)local_74 + 1);
        iVar1 = (int)local_74 * 4;
      } while (*puVar14 != 0x1fffffff);
    }
    local_84 = lv_malloc(iVar1);
    local_7c = (uint *)lv_malloc((int)local_74 << 2);
    if (local_74 == (uint *)0x0) {
LAB_00483658:
      iVar1 = 0;
      iVar10 = 0;
    }
    else {
      local_44 = 0x1fffff9a;
      puVar11 = (uint *)0x0;
      local_38 = (uint *)0xe0000001;
      puVar14 = local_74;
      puVar7 = puVar8;
LAB_00482608:
      do {
        local_48 = (int)puVar11 << 2;
        if (*puVar7 == local_44) {
          uVar9 = 0;
          local_40 = local_38;
          iVar1 = lv_obj_get_child_count(param_1);
          if (iVar1 != 0) {
            do {
              uVar2 = lv_obj_get_child(param_1,uVar9);
              iVar1 = lv_obj_has_flag_any(uVar2,0x60001);
              if ((((iVar1 == 0) &&
                   (lv_obj_get_style_prop(&local_68,uVar2,0,0x8a), local_68 == (uint *)0x1)) &&
                  (lv_obj_get_style_prop(&local_68,uVar2,0,0x89), local_68 == puVar11)) &&
                 (iVar1 = lv_obj_get_height(uVar2), (int)local_40 <= iVar1)) {
                local_40 = (uint *)lv_obj_get_height(uVar2);
              }
              uVar9 = uVar9 + 1;
              uVar3 = lv_obj_get_child_count(param_1);
            } while (uVar9 < uVar3);
          }
          puVar14 = local_74;
          if (-1 < (int)local_40) {
            *(int *)((int)local_7c + local_48) = (int)local_40;
            puVar11 = (uint *)((int)puVar11 + 1);
            puVar7 = puVar7 + 1;
            if (local_74 <= puVar11) break;
            goto LAB_00482608;
          }
          *(int *)((int)local_7c + local_48) = 0;
        }
        puVar11 = (uint *)((int)puVar11 + 1);
        puVar7 = puVar7 + 1;
      } while (puVar11 < puVar14);
      if (puVar14 == (uint *)0x0) goto LAB_00483658;
      iVar1 = 0;
      iVar10 = 0;
      puVar5 = (uint *)0x0;
      puVar7 = local_7c;
      puVar11 = puVar8;
      do {
        while( true ) {
          uVar9 = *puVar11;
          if ((int)uVar9 < 0x1fffff9b) break;
          iVar10 = uVar9 + iVar10 + -0x1fffff9b;
LAB_004826f8:
          puVar5 = (uint *)((int)puVar5 + 1);
          puVar11 = puVar11 + 1;
          puVar7 = puVar7 + 1;
          if (puVar14 <= puVar5) goto LAB_00482744;
        }
        if (uVar9 == 0x1fffff9a) {
          iVar1 = iVar1 + *puVar7;
          goto LAB_004826f8;
        }
        *puVar7 = uVar9;
        puVar5 = (uint *)((int)puVar5 + 1);
        iVar1 = iVar1 + uVar9;
        puVar11 = puVar11 + 1;
        puVar7 = puVar7 + 1;
        puVar14 = local_74;
      } while (puVar5 < local_74);
    }
LAB_00482744:
    lv_obj_get_style_prop(&local_68,param_1,0,0x14);
    puVar14 = local_68;
    iVar4 = lv_obj_get_content_height(param_1);
    iVar1 = (iVar4 - ((int)local_74 + -1) * (int)puVar14) - iVar1;
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    if ((local_74 != (uint *)0x0) && (iVar10 != 0)) {
      puVar11 = (uint *)0x0;
      puVar14 = puVar8;
      puVar7 = local_7c;
      do {
        while (iVar4 = *puVar14 + 0xe0000065, (int)*puVar14 < 0x1fffff9b) {
          puVar11 = (uint *)((int)puVar11 + 1);
          puVar14 = puVar14 + 1;
          if (local_74 <= puVar11) goto LAB_004827fc;
          puVar7 = puVar7 + 1;
        }
        puVar11 = (uint *)((int)puVar11 + 1);
        puVar14 = puVar14 + 1;
        uVar9 = (iVar10 / 2 + iVar4 * iVar1) / iVar10;
        if (iVar10 == 0) {
          trap(7);
        }
        *puVar7 = uVar9;
        iVar1 = iVar1 - uVar9;
        iVar10 = iVar10 - iVar4;
      } while ((puVar11 < local_74) && (puVar7 = puVar7 + 1, iVar10 != 0));
    }
LAB_004827fc:
    if (local_3c != (uint *)0x0) {
      lv_free(puVar8);
    }
  }
  lv_obj_get_style_prop(&local_68,param_1,0,0x85);
  local_3c = (uint *)0x0;
  puVar8 = local_68;
  if (local_68 == (uint *)0x0) {
    uVar2 = lv_obj_get_parent(param_1);
    lv_obj_get_style_prop(&local_68,uVar2,0,0x85);
    puVar14 = local_68;
    if (local_68 != (uint *)0x0) {
      lv_obj_get_style_prop(&local_68,param_1,0,0x86);
      puVar7 = local_68;
      lv_obj_get_style_prop(&local_68,param_1,0,0x87);
      puVar11 = local_68;
      iVar1 = ((int)local_68 + 1) * 4;
      puVar8 = (uint *)lv_malloc(iVar1);
      lv_memcpy(puVar8,puVar14 + (int)puVar7,iVar1 + -4);
      puVar8[(int)puVar11] = 0x1fffffff;
      local_3c = (uint *)0x1;
      goto LAB_00482828;
    }
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/layouts/grid/lv_grid.c"
               ,0x11d,"calc_cols","No col descriptor found even on the parent");
  }
  else {
LAB_00482828:
    local_34 = lv_obj_get_content_width(param_1);
    if (*puVar8 == 0x1fffffff) {
      iVar1 = 0;
      local_78 = (uint *)0x0;
    }
    else {
      local_78 = (uint *)0x0;
      puVar14 = puVar8;
      do {
        puVar14 = puVar14 + 1;
        local_78 = (uint *)((int)local_78 + 1);
        iVar1 = (int)local_78 * 4;
      } while (*puVar14 != 0x1fffffff);
    }
    local_88 = (uint *)lv_malloc(iVar1);
    local_80 = (uint *)lv_malloc((int)local_78 << 2);
    if (local_78 == (uint *)0x0) {
LAB_004837f0:
      lv_obj_get_style_prop(&local_68,param_1,0,0x15);
    }
    else {
      local_44 = 0x1fffff9a;
      puVar11 = (uint *)0x0;
      local_38 = (uint *)0xe0000001;
      puVar14 = local_78;
      puVar7 = puVar8;
LAB_004828c4:
      do {
        local_48 = (int)puVar11 << 2;
        if (*puVar7 == local_44) {
          uVar9 = 0;
          local_40 = local_38;
          iVar1 = lv_obj_get_child_count(param_1);
          if (iVar1 != 0) {
            do {
              uVar2 = lv_obj_get_child(param_1,uVar9);
              iVar1 = lv_obj_has_flag_any(uVar2,0x60001);
              if ((((iVar1 == 0) &&
                   (lv_obj_get_style_prop(&local_68,uVar2,0,0x87), local_68 == (uint *)0x1)) &&
                  (lv_obj_get_style_prop(&local_68,uVar2,0,0x86), local_68 == puVar11)) &&
                 (iVar1 = lv_obj_get_width(uVar2), (int)local_40 <= iVar1)) {
                local_40 = (uint *)lv_obj_get_width(uVar2);
              }
              uVar9 = uVar9 + 1;
              uVar3 = lv_obj_get_child_count(param_1);
            } while (uVar9 < uVar3);
          }
          puVar14 = local_78;
          if (-1 < (int)local_40) {
            *(int *)((int)local_80 + local_48) = (int)local_40;
            puVar11 = (uint *)((int)puVar11 + 1);
            puVar7 = puVar7 + 1;
            if (local_78 <= puVar11) break;
            goto LAB_004828c4;
          }
          *(int *)((int)local_80 + local_48) = 0;
        }
        puVar11 = (uint *)((int)puVar11 + 1);
        puVar7 = puVar7 + 1;
      } while (puVar11 < puVar14);
      if (puVar14 == (uint *)0x0) goto LAB_004837f0;
      iVar1 = 0;
      iVar10 = 0;
      puVar5 = (uint *)0x0;
      puVar7 = local_80;
      puVar11 = puVar8;
      do {
        while( true ) {
          uVar9 = *puVar11;
          if ((int)uVar9 < 0x1fffff9b) break;
          iVar10 = uVar9 + iVar10 + -0x1fffff9b;
LAB_004829b4:
          puVar5 = (uint *)((int)puVar5 + 1);
          puVar11 = puVar11 + 1;
          puVar7 = puVar7 + 1;
          if (puVar14 <= puVar5) goto LAB_00482a00;
        }
        if (uVar9 == 0x1fffff9a) {
          iVar1 = iVar1 + *puVar7;
          goto LAB_004829b4;
        }
        *puVar7 = uVar9;
        puVar5 = (uint *)((int)puVar5 + 1);
        iVar1 = iVar1 + uVar9;
        puVar11 = puVar11 + 1;
        puVar7 = puVar7 + 1;
        puVar14 = local_78;
      } while (puVar5 < local_78);
LAB_00482a00:
      lv_obj_get_style_prop(&local_68,param_1,0,0x15);
      iVar1 = (local_34 - ((int)local_78 + -1) * (int)local_68) - iVar1;
      if (iVar1 < 0) {
        iVar1 = 0;
      }
      if ((local_78 != (uint *)0x0) && (iVar10 != 0)) {
        puVar11 = (uint *)0x0;
        puVar14 = puVar8;
        puVar7 = local_80;
        do {
          while (iVar4 = *puVar14 + 0xe0000065, (int)*puVar14 < 0x1fffff9b) {
            puVar11 = (uint *)((int)puVar11 + 1);
            puVar14 = puVar14 + 1;
            if (local_78 <= puVar11) goto joined_r0x00483808;
            puVar7 = puVar7 + 1;
          }
          puVar11 = (uint *)((int)puVar11 + 1);
          puVar14 = puVar14 + 1;
          uVar9 = (iVar10 / 2 + iVar4 * iVar1) / iVar10;
          if (iVar10 == 0) {
            trap(7);
          }
          *puVar7 = uVar9;
          iVar1 = iVar1 - uVar9;
          iVar10 = iVar10 - iVar4;
        } while ((puVar11 < local_78) && (puVar7 = puVar7 + 1, iVar10 != 0));
      }
    }
joined_r0x00483808:
    if (local_3c != (uint *)0x0) {
      lv_free(puVar8);
    }
  }
  lv_obj_get_style_prop(&local_68,param_1,0,0x15);
  puVar8 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,0x14);
  puVar14 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,0x27);
  puVar7 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,1);
  puVar11 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,2);
  puVar5 = local_68;
  uVar9 = 0;
  if (puVar11 == (uint *)0x3fffffff) {
    uVar9 = ((*(ushort *)(param_1 + 0x2a) ^ 0x800) << 0x14) >> 0x1f;
  }
  uVar2 = lv_obj_get_content_width(param_1);
  lv_obj_get_style_prop(&local_68,param_1,0,0x82);
  uVar3 = 0;
  local_70 = grid_align(uVar2,uVar9,local_68,puVar8,local_78,local_80,local_88,puVar7 == (uint *)0x1
                       );
  if (puVar5 == (uint *)0x3fffffff) {
    uVar3 = ((*(ushort *)(param_1 + 0x2a) ^ 0x400) << 0x15) >> 0x1f;
  }
  uVar2 = lv_obj_get_content_height(param_1);
  lv_obj_get_style_prop(&local_68,param_1,0,0x83);
  local_6c = grid_align(uVar2,uVar3,local_68,puVar14,local_74,local_7c,local_84,0);
LAB_00482c08:
  lv_memset(auStack_58,0,0x10);
  lv_obj_get_style_prop(&local_68,param_1,0,0x12);
  puVar8 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,0x30);
  puVar14 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,0x34);
  if (((uint)local_68 & 4) != 0) {
    puVar8 = (uint *)((int)puVar8 + (int)puVar14);
  }
  lv_obj_get_style_prop(&local_68,param_1,0,0x10);
  puVar14 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,0x30);
  puVar7 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,0x34);
  iVar1 = *(int *)(param_1 + 0x14);
  if (((uint)local_68 & 2) != 0) {
    puVar14 = (uint *)((int)puVar14 + (int)puVar7);
  }
  iVar10 = lv_obj_get_scroll_x(param_1);
  iVar4 = *(int *)(param_1 + 0x18);
  local_50 = (int)puVar8 + (iVar1 - iVar10);
  iVar1 = lv_obj_get_scroll_y(param_1);
  piVar6 = *(int **)(param_1 + 8);
  local_4c = (int)puVar14 + (iVar4 - iVar1);
  if ((short)piVar6[0xb] != 0) {
    local_48 = 0x3fffffff;
    uVar9 = 0;
    local_44 = 0x9fffffff;
    do {
      while( true ) {
        iVar10 = *(int *)(*piVar6 + uVar9 * 4);
        iVar1 = lv_obj_has_flag_any(iVar10,0x60001);
        if (iVar1 == 0) break;
LAB_00482d24:
        piVar6 = *(int **)(param_1 + 8);
        uVar9 = uVar9 + 1;
        if (*(ushort *)(piVar6 + 0xb) <= uVar9) goto LAB_00483100;
      }
      lv_obj_get_style_prop(&local_68,iVar10,0,0x87);
      puVar8 = local_68;
      lv_obj_get_style_prop(&local_68,iVar10,0,0x8a);
      puVar14 = local_68;
      if ((local_68 == (uint *)0x0) || (puVar8 == (uint *)0x0)) goto LAB_00482d24;
      lv_obj_get_style_prop(&local_68,iVar10,0,0x86);
      local_40 = local_68;
      lv_obj_get_style_prop(&local_68,iVar10,0,0x89);
      puVar7 = local_68;
      lv_obj_get_style_prop(&local_68,iVar10,0,0x88);
      puVar11 = local_68;
      lv_obj_get_style_prop(&local_68,iVar10,0,0x8b);
      puVar5 = local_68;
      iVar4 = (int)puVar8 + (int)local_40 + local_48;
      iVar1 = (int)puVar14 + (int)puVar7 + local_48;
      local_38 = (uint *)((int)local_40 * 4);
      local_3c = (uint *)((int)puVar7 * 4);
      local_30 = (local_7c[iVar1] + *(int *)(local_84 + iVar1 * 4)) -
                 *(int *)(local_84 + (int)local_3c);
      local_34 = (local_80[iVar4] + local_88[iVar4]) - local_88[(int)local_40];
      lv_obj_get_style_prop(&local_68,iVar10,0,0x27);
      iVar1 = iVar10 + 0x14;
      if (local_68 == (uint *)0x1) {
        if (puVar11 == (uint *)0x0) {
          iVar4 = lv_area_get_width(iVar1);
          local_40 = (uint *)lv_area_get_height(iVar1);
          goto LAB_004834f4;
        }
        if (puVar11 != (uint *)0x2) goto LAB_00482ea8;
        iVar4 = lv_area_get_width(iVar1);
        local_40 = (uint *)lv_area_get_height(iVar1);
LAB_00482edc:
        iVar12 = *(int *)((int)local_88 + (int)local_38);
        lv_obj_get_style_prop(&local_68,iVar10,0,0x1a);
        local_38 = (uint *)(iVar12 + (int)local_68);
        *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xf7ff;
LAB_00482f18:
        puVar8 = *(uint **)(local_84 + (int)local_3c);
        if (puVar5 != (uint *)0x2) goto LAB_00482f30;
LAB_0048342c:
        local_3c = puVar8;
        iVar12 = lv_obj_get_height(iVar10);
        puVar8 = local_3c;
        iVar12 = local_30 - iVar12;
        lv_obj_get_style_prop(&local_68,iVar10,0,0x19);
        iVar13 = (int)puVar8 + (iVar12 - (int)local_68);
        *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xfbff;
        iVar12 = lv_obj_get_width(iVar10);
        if (iVar12 == iVar4) goto LAB_00483480;
LAB_00482f80:
        local_68 = *(uint **)(iVar10 + 0x14);
        local_64 = *(undefined4 *)(iVar10 + 0x18);
        local_5c = *(undefined4 *)(iVar10 + 0x20);
        local_60 = *(undefined4 *)(iVar10 + 0x1c);
        lv_obj_invalidate(iVar10);
        lv_area_set_width(iVar1,iVar4);
        lv_area_set_height(iVar1,local_40);
        lv_obj_invalidate(iVar10);
        lv_obj_send_event(iVar10,0x31,&local_68);
        uVar2 = lv_obj_get_parent(iVar10);
        lv_obj_send_event(uVar2,0x2a,iVar10);
      }
      else {
LAB_00482ea8:
        iVar4 = lv_area_get_width(iVar1);
        local_40 = (uint *)lv_area_get_height(iVar1);
        if (puVar11 == (uint *)0x2) {
LAB_004834f4:
          iVar13 = local_34 + *(int *)((int)local_88 + (int)local_38);
          iVar12 = lv_obj_get_width(iVar10);
          lv_obj_get_style_prop(&local_68,iVar10,0,0x1b);
          local_38 = (uint *)((iVar13 - iVar12) - (int)local_68);
          *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xf7ff;
          goto LAB_00482f18;
        }
        if (puVar11 != (uint *)0x3) {
          if (puVar11 != (uint *)0x1) goto LAB_00482edc;
          iVar12 = local_34 - iVar4;
          iVar13 = *(int *)((int)local_88 + (int)local_38);
          local_34 = 2;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x1a);
          local_38 = local_68;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x1b);
          if (local_34 == 0) {
            trap(7);
          }
          *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xf7ff;
          local_38 = (uint *)(((int)local_38 - (int)local_68) / local_34 + iVar12 / 2 + iVar13);
          goto LAB_00482f18;
        }
        iVar4 = *(int *)((int)local_88 + (int)local_38);
        lv_obj_get_style_prop(&local_68,iVar10,0,0x1a);
        local_38 = (uint *)(iVar4 + (int)local_68);
        lv_obj_get_style_prop(&local_68,iVar10,0,0x1a);
        puVar8 = local_68;
        lv_obj_get_style_prop(&local_68,iVar10,0,0x1b);
        *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xf7ff | 0x800;
        iVar4 = local_34 - ((int)puVar8 + (int)local_68);
        puVar8 = *(uint **)(local_84 + (int)local_3c);
        if (puVar5 == (uint *)0x2) goto LAB_0048342c;
LAB_00482f30:
        if (puVar5 == (uint *)0x3) {
          local_40 = puVar8;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x18);
          iVar13 = (int)local_68 + (int)local_40;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x18);
          puVar8 = local_68;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x19);
          local_40 = (uint *)(local_30 - ((int)puVar8 + (int)local_68));
          *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xfbff | 0x400;
        }
        else if (puVar5 == (uint *)0x1) {
          local_34 = (local_30 - (int)local_40) / 2 + (int)puVar8;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x18);
          local_3c = local_68;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x19);
          *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xfbff;
          iVar13 = ((int)local_3c - (int)local_68) / 2 + local_34;
        }
        else {
          local_3c = puVar8;
          lv_obj_get_style_prop(&local_68,iVar10,0,0x18);
          *(ushort *)(iVar10 + 0x2a) = *(ushort *)(iVar10 + 0x2a) & 0xfbff;
          iVar13 = (int)local_68 + (int)local_3c;
        }
        iVar12 = lv_obj_get_width(iVar10);
        if (iVar12 != iVar4) goto LAB_00482f80;
LAB_00483480:
        iVar12 = lv_obj_get_height(iVar10);
        if ((uint *)iVar12 != local_40) goto LAB_00482f80;
      }
      lv_obj_get_style_prop(&local_68,iVar10,0,0x6a);
      puVar8 = local_68;
      lv_obj_get_style_prop(&local_68,iVar10,0,0x6b);
      puVar14 = local_68;
      iVar1 = lv_obj_get_width(iVar10);
      iVar4 = lv_obj_get_height(iVar10);
      if ((((uint)puVar8 & 0x60000000) == 0x20000000) &&
         (uVar3 = (uint)puVar8 & local_44, uVar3 != 0x1fffffff)) {
        if (0xfffffff < (int)uVar3) {
          uVar3 = 0xfffffff - uVar3;
        }
        puVar8 = (uint *)((int)(iVar1 * uVar3) / 100);
      }
      if ((((uint)puVar14 & 0x60000000) == 0x20000000) &&
         (uVar3 = (uint)puVar14 & local_44, uVar3 != 0x1fffffff)) {
        if (0xfffffff < (int)uVar3) {
          uVar3 = 0xfffffff - uVar3;
        }
        puVar14 = (uint *)((int)(iVar4 * uVar3) / 100);
      }
      iVar4 = (int)puVar8 + ((local_50 + (int)local_38) - *(int *)(iVar10 + 0x14));
      iVar1 = (int)puVar14 + ((local_4c + iVar13) - *(int *)(iVar10 + 0x18));
      if (iVar4 == 0 && iVar1 == 0) goto LAB_00482d24;
      lv_obj_invalidate(iVar10);
      *(int *)(iVar10 + 0x20) = *(int *)(iVar10 + 0x20) + iVar1;
      *(int *)(iVar10 + 0x14) = *(int *)(iVar10 + 0x14) + iVar4;
      *(int *)(iVar10 + 0x1c) = *(int *)(iVar10 + 0x1c) + iVar4;
      *(int *)(iVar10 + 0x18) = *(int *)(iVar10 + 0x18) + iVar1;
      lv_obj_invalidate(iVar10);
      lv_obj_move_children_by(iVar10,iVar4,iVar1,0);
      piVar6 = *(int **)(param_1 + 8);
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(ushort *)(piVar6 + 0xb));
  }
LAB_00483100:
  lv_free(local_88);
  lv_free(local_84);
  lv_free(local_80);
  lv_free(local_7c);
  lv_obj_get_style_prop(&local_68,param_1,0,1);
  puVar8 = local_68;
  lv_obj_get_style_prop(&local_68,param_1,0,2);
  if ((puVar8 == (uint *)0x3fffffff) || (local_68 == (uint *)0x3fffffff)) {
    lv_obj_refr_size(param_1);
  }
  lv_obj_send_event(param_1,0x33,0);
  return;
}



// === updateHashChain @ 00483da4 ===

void updateHashChain(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *param_1;
  *(int *)(param_1[2] + param_2 * 4) = param_3;
  piVar2 = (int *)(iVar1 + param_3 * 4);
  iVar1 = *piVar2;
  iVar3 = param_2 * 2;
  if (iVar1 != -1) {
    *(short *)(param_1[1] + iVar3) = (short)iVar1;
  }
  iVar1 = param_1[3];
  *piVar2 = param_2;
  piVar2 = (int *)(iVar1 + param_4 * 4);
  iVar1 = *piVar2;
  *(short *)(param_1[5] + iVar3) = (short)param_4;
  if (iVar1 != -1) {
    *(short *)(param_1[4] + iVar3) = (short)iVar1;
  }
  *piVar2 = param_2;
  return;
}



// === lodepng_assign_icc.part.23 @ 00488cc8 ===

undefined4
lodepng_assign_icc_part_23(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = param_2;
  if (*param_2 == '\0') {
    iVar2 = 0;
  }
  else {
    do {
      pcVar1 = pcVar1 + 1;
    } while (*pcVar1 != '\0');
    iVar2 = (int)pcVar1 - (int)param_2;
  }
  uVar3 = alloc_string_sized(param_2,iVar2);
  *(undefined4 *)(param_1 + 0xc0) = uVar3;
  iVar2 = lv_malloc(param_4);
  *(int *)(param_1 + 0xc4) = iVar2;
  if ((*(int *)(param_1 + 0xc0) != 0) && (iVar2 != 0)) {
    lv_memcpy(iVar2,param_3,param_4);
    *(undefined4 *)(param_1 + 200) = param_4;
    return 0;
  }
  return 0x53;
}



// === pr_cmd_gui_remote_close_errcode_update_proc @ 00493bac ===

undefined4 pr_cmd_gui_remote_close_errcode_update_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x3798,1);
  return 0;
}



// === pr_cmd_gui_local_network_update_proc @ 00493bd8 ===

undefined4 pr_cmd_gui_local_network_update_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x3778,1);
  return 0;
}



// === pr_cmd_gui_detect_new_version_update_proc @ 00493c04 ===

undefined4 pr_cmd_gui_detect_new_version_update_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x1098,1);
  return 0;
}



// === pr_cmd_gui_selftest_send_update_proc @ 00493c30 ===

undefined4 pr_cmd_gui_selftest_send_update_proc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = **(undefined4 **)(param_1 + 4);
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2b70,uVar2);
  return 0;
}



// === pr_cmd_gui_ai_detect_enable_state @ 00493c6c ===

undefined4 pr_cmd_gui_ai_detect_enable_state(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x1298,1);
  return 0;
}



// === pr_cmd_gui_video_elapse_enable_state @ 00493c98 ===

undefined4 pr_cmd_gui_video_elapse_enable_state(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x1278,1);
  return 0;
}



// === pr_cmd_gui_ota_download_state @ 00493cc4 ===

undefined4 pr_cmd_gui_ota_download_state(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x1258,1);
  return 0;
}



// === pr_cmd_gui_elapse_list_update_proc @ 00493cf0 ===

undefined4 pr_cmd_gui_elapse_list_update_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2b30,1);
  return 0;
}



// === pr_cmd_axis_e_status_update_proc @ 00493d1c ===

undefined4 pr_cmd_axis_e_status_update_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2b10,1);
  return 0;
}



// === pr_cmd_udisk_list_update @ 00493d48 ===

undefined4 pr_cmd_udisk_list_update(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2af0,1);
  return 0;
}



// === pr_show_ota_progress_proc @ 00493d74 ===

undefined4 pr_show_ota_progress_proc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = **(undefined4 **)(param_1 + 4);
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x11d8,uVar2);
  return 0;
}



// === pr_update_history_file_list_proc @ 00493db0 ===

undefined4 pr_update_history_file_list_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2a70,1);
  return 0;
}



// === wifi_signal_strength_symbol_proc @ 00494070 ===

undefined4 wifi_signal_strength_symbol_proc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = **(undefined4 **)(param_1 + 4);
  printf("wifi signal strength: %d\n",uVar2);
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0xf78,uVar2);
  return 0;
}



// === pr_cmd_gui_print_by_ai_proc @ 004940bc ===

undefined4 pr_cmd_gui_print_by_ai_proc(void)

{
  int iVar1;
  int iVar2;
  
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/localgui.c"
             ,0x2b5,"pr_cmd_gui_print_by_ai_proc","start print by ai");
  iVar1 = getodin();
  iVar2 = getodin();
  print_operation(9,iVar1 + 0xab4,*(undefined4 *)(iVar2 + 0xbb4));
  return 0;
}



// === pr_cmd_gui_toast_notify_proc @ 0049412c ===

undefined4 pr_cmd_gui_toast_notify_proc(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = lv_i18n_get_text(*(undefined4 *)(param_1 + 4));
  widget_toast_create(0,uVar1,0,1000);
  return 0;
}



// === pr_cmd_ota_state_receive @ 00494164 ===

undefined4 pr_cmd_ota_state_receive(void)

{
  int iVar1;
  
  puts("Received ota state");
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x1238,1);
  return 0;
}



// === pr_update_printer_related_state_proc @ 00494470 ===

undefined4 pr_update_printer_related_state_proc(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = **(int **)(param_1 + 4);
  iVar1 = getodin();
  if (iVar5 == 4) {
    uVar4 = get_printer_work_state();
    iVar2 = printer_is_working(uVar4);
    if (iVar2 == 0) {
      iVar2 = getodin();
      *(undefined1 *)(iVar2 + 0x1618) = 0;
      iVar2 = getodin();
      *(undefined1 *)(iVar2 + 0x2760) = 0;
    }
    iVar2 = getodin();
    uVar4 = get_printer_work_state();
    lv_subject_set_int(iVar2 + 0x28b0,uVar4);
LAB_004945b4:
    if (iVar5 == 5) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1158,1);
      goto LAB_004945d4;
    }
LAB_00494680:
    if (iVar5 == 6) {
      iVar2 = getodin();
      lv_subject_set_int(iVar2 + 0x1118,*(undefined1 *)(iVar1 + 0x26fc));
      goto LAB_004946a0;
    }
LAB_0049451c:
    if (iVar5 == 7) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1198,1);
      goto LAB_0049453c;
    }
    if (iVar5 != 8) goto LAB_00494828;
    iVar1 = getodin();
    lv_subject_set_int(iVar1 + 0x1178,1);
LAB_00494774:
    if (iVar5 == 0xe) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x2764,1);
      goto LAB_00494794;
    }
LAB_00494848:
    if (iVar5 == 0xf) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x2890,1);
      return 0;
    }
LAB_004945f4:
    if (iVar5 == 0xd) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x2ab0,1);
      return 0;
    }
LAB_004946c0:
    if (iVar5 == 0x10) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1018,1);
      return 0;
    }
  }
  else {
    if (iVar5 == 0) {
      iVar2 = getodin();
      lv_subject_set_int(iVar2 + 0x28d0,*(undefined1 *)(iVar1 + 0x26f8));
      goto LAB_004945b4;
    }
    if (iVar5 == 1) {
      iVar2 = getodin();
      iVar3 = getodin();
      lv_subject_set_int(iVar2 + 0x2990,(int)*(double *)(iVar3 + 0x2028));
      iVar2 = getodin();
      lv_subject_set_int(iVar2 + 0x10b8,*(undefined1 *)(iVar1 + 0x26f9));
      goto LAB_00494680;
    }
    if (iVar5 == 2) {
      iVar2 = getodin();
      iVar3 = getodin();
      lv_subject_set_int(iVar2 + 0x2970,(int)*(double *)(iVar3 + 0x2018));
      iVar2 = getodin();
      lv_subject_set_int(iVar2 + 0x10d8,*(undefined1 *)(iVar1 + 0x26fa));
      goto LAB_0049451c;
    }
    if (iVar5 != 3) goto LAB_004945b4;
    iVar2 = getodin();
    iVar3 = getodin();
    lv_subject_set_int(iVar2 + 0x29b0,(int)*(double *)(iVar3 + 0x2260));
    iVar2 = getodin();
    lv_subject_set_int(iVar2 + 0x10f8,*(undefined1 *)(iVar1 + 0x26fb));
LAB_00494828:
    if (iVar5 == 9) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0xfb8,1);
      goto LAB_00494848;
    }
LAB_004945d4:
    if (iVar5 == 10) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0xfd8,1);
      goto LAB_004945f4;
    }
LAB_004946a0:
    if (iVar5 == 0xb) {
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1038,1);
      goto LAB_004946c0;
    }
LAB_0049453c:
    if (iVar5 != 0xc) goto LAB_00494774;
    iVar1 = getodin();
    lv_subject_set_int(iVar1 + 0xff8,1);
  }
  if (iVar5 == 0x11) {
    iVar1 = getodin();
    lv_subject_set_int(iVar1 + 0x1058,1);
    return 0;
  }
LAB_00494794:
  if (iVar5 != 0x12) {
    return 0;
  }
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x1078,1);
  return 0;
}



// === pr_update_pendrive_file_list_proc @ 00495188 ===

undefined4 pr_update_pendrive_file_list_proc(void)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  
  iVar1 = getodin();
  iVar2 = getodin();
  sVar3 = strlen((char *)(iVar2 + 0x290));
  lv_subject_set_int(iVar1 + 0x2a50,sVar3);
  return 0;
}



// === pr_update_file_list_proc @ 004951c8 ===

undefined4 pr_update_file_list_proc(void)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  
  iVar1 = getodin();
  iVar2 = getodin();
  sVar3 = strlen((char *)(iVar2 + 0x81));
  lv_subject_set_int(iVar1 + 0x2a30,sVar3);
  return 0;
}



// === pr_cmd_gui_reset_z_offset_val_proc @ 00495438 ===

undefined4 pr_cmd_gui_reset_z_offset_val_proc(void)

{
  int iVar1;
  undefined4 in_a3;
  double dVar2;
  
  iVar1 = getodin();
  if (DAT_005959a0 < *(double *)(iVar1 + 0x2340)) {
    dVar2 = DAT_005959a0;
    iVar1 = getodin();
    dVar2 = dVar2 - *(double *)(iVar1 + 0x2340);
    iVar1 = getodin();
    if (*(char *)(iVar1 + 0x2712) == '\0') {
      ws_run_cmd("cx_set_zoffset_not_homed",1,"%0.3f",in_a3,dVar2);
    }
    else {
      ws_run_cmd("cx_set_zoffset_homed",1,"%0.3f",in_a3,dVar2);
    }
  }
  iVar1 = getodin();
  if (*(double *)(iVar1 + 0x2340) < DAT_005959a8) {
    dVar2 = DAT_005959a8;
    iVar1 = getodin();
    dVar2 = dVar2 - *(double *)(iVar1 + 0x2340);
    iVar1 = getodin();
    if (*(char *)(iVar1 + 0x2712) == '\0') {
      ws_run_cmd("cx_set_zoffset_not_homed",1,"%0.3f",in_a3,dVar2);
      return 0;
    }
    ws_run_cmd("cx_set_zoffset_homed",1,"%0.3f",in_a3,dVar2);
    return 0;
  }
  return 0;
}



// === pr_cmd_gui_remote_control_update_proc @ 00495634 ===

undefined4 pr_cmd_gui_remote_control_update_proc(void)

{
  int iVar1;
  
  iVar1 = getodin();
  if (*(char *)(iVar1 + 0x2bb0) == '\0') {
    iVar1 = getodin();
    lv_subject_set_int(iVar1 + 0x2b90,1);
  }
  return 0;
}



// === extrude_cmd_item_cb @ 00495674 ===

void extrude_cmd_item_cb(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  char acStack_48 [64];
  
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    if (iVar1 == 0) {
      uVar2 = ws_run_cmd("cx_printer_gcode_script",0,"%s",s_M83_n_G1_E80_F180_n_M400_006c4758);
      ws_reqcb_cache_add(uVar2,PTR_extrude_cmd_item_cb_006c4798,&DAT_006c47a0,300);
      iVar1 = getodin();
      *(undefined4 *)(iVar1 + 0x2700) = 2;
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1138,2);
      sync_odin_to_printstate(0);
      iVar1 = *param_1;
    }
    if (iVar1 == 1) {
      memset(acStack_48,0,0x40);
      snprintf(acStack_48,0x40,s_SET_HEATER_TEMPERATURE_HEATER_ex_006c47ac,0);
      ws_run_cmd("cx_printer_gcode_script",0,"%s",acStack_48);
      update_access_state_by_workstate();
      iVar1 = getodin();
      *(undefined4 *)(iVar1 + 0x2700) = 3;
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1138,3);
      sync_odin_to_printstate(0);
      return;
    }
  }
  return;
}



// === retract_cmd_item_cb @ 004957b0 ===

void retract_cmd_item_cb(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  char acStack_48 [64];
  
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    if (iVar1 == 0) {
      uVar2 = ws_run_cmd("cx_printer_gcode_script",0,"%s",s_M83_n_G1_E_50_F180_n_M400_006c4608);
      ws_reqcb_cache_add(uVar2,PTR_retract_cmd_item_cb_006c4648,&DAT_006c4650,300);
      iVar1 = getodin();
      *(undefined4 *)(iVar1 + 0x2700) = 0xd;
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1138,0xd);
      sync_odin_to_printstate(0);
      iVar1 = *param_1;
    }
    if (iVar1 == 1) {
      memset(acStack_48,0,0x40);
      snprintf(acStack_48,0x40,s_SET_HEATER_TEMPERATURE_HEATER_ex_006c465c,0);
      ws_run_cmd("cx_printer_gcode_script",0,"%s",acStack_48);
      update_access_state_by_workstate();
      iVar1 = getodin();
      *(undefined4 *)(iVar1 + 0x2700) = 0xe;
      iVar1 = getodin();
      lv_subject_set_int(iVar1 + 0x1138,0xe);
      sync_odin_to_printstate(0);
      return;
    }
  }
  return;
}



// === errcode_btn_reboot_event_cb @ 004978a8 ===

void errcode_btn_reboot_event_cb(undefined4 param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 local_18 [3];
  
  iVar2 = lv_event_get_code();
  lv_event_get_target(param_1);
  lv_event_get_user_data(param_1);
  if (iVar2 == 10) {
    local_18[0] = 0;
    service_gui_request(2,local_18,4);
    iVar2 = getodin();
    bVar1 = klipper_restart_delay_timer == 0;
    *(undefined1 *)(iVar2 + 0x36c6) = 1;
    if (bVar1) {
      klipper_restart_delay_timer = lv_timer_create(klipper_restart_delay_timer_callback,1000,0);
      lv_timer_set_repeat_count(klipper_restart_delay_timer,1);
    }
    else {
      lv_timer_reset();
    }
    iVar2 = getodin();
    if (*(char *)(iVar2 + 0x2bca) != '\0') {
      page_guide_restart_selftest();
      page_device_selftest_restart();
    }
    if (noti_master != 0) {
      lv_obj_clean();
    }
    clear_errcode_to_slicer();
    return;
  }
  return;
}



// === cbNotifyUpdateResponse @ 00498290 ===

undefined4 cbNotifyUpdateResponse(void)

{
  return 0;
}



// === cbGetAccessOneShotToken @ 00499254 ===

undefined4 cbGetAccessOneShotToken(int param_1,char *param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 4);
  if (iVar1 != 0) {
    printf("result: %s\n",*(undefined4 *)(iVar1 + 0x10));
    snprintf(param_2,0x24,"%s",*(undefined4 *)(iVar1 + 0x10));
  }
  return 0;
}



// === cbGetServerHistoryTotals @ 004994f4 ===

undefined4 cbGetServerHistoryTotals(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_1b0;
  undefined2 local_1ac;
  int local_1a4;
  int local_5c [2];
  char *local_54;
  undefined4 local_50;
  int local_4c;
  undefined4 local_48;
  char *local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 local_38;
  char *local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  char *local_24;
  undefined4 local_20;
  undefined4 local_18;
  
  local_18 = 0;
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 != 0) {
    iVar1 = getodin();
    iVar2 = cJSON_GetObjectItem(iVar2,"job_totals");
    if (iVar2 != 0) {
      local_5c[1] = 0x100;
      local_48 = 0x100;
      local_38 = 0x100;
      local_5c[0] = iVar1 + 0x4d8;
      local_34 = "total_time";
      local_28 = 8;
      local_4c = iVar1 + 0x4e0;
      local_3c = iVar1 + 0x4e8;
      local_2c = iVar1 + 0x4f0;
      local_54 = "total_filament_used";
      local_24 = "total_jobs";
      local_44 = "total_print_time";
      local_50 = 0;
      local_40 = 0;
      local_30 = 0;
      local_20 = 0;
      extract_from_json(iVar2,local_5c,4,1);
      dump_extracted_from_json(iVar2,local_5c,4);
      iVar2 = cJSON_GetObjectItem(iVar2,"total_print_time");
      if (iVar2 != 0) {
        memset(&local_1b0,0,0x154);
        local_1b0 = 0x3779656b;
        local_1ac = 0x3232;
        iVar2 = getodin();
        local_18 = 0;
        local_1a4 = (int)*(double *)(iVar2 + 0x4e0);
        start_data_buried(&local_1b0);
        iVar2 = getodin();
        local_18 = 0;
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
                   ,0x645,"cbGetServerHistoryTotals","total_print_time=%d",
                   (int)*(double *)(iVar2 + 0x4e0));
      }
    }
  }
  return 0;
}



// === cbNotifyUpdateRefreshed @ 0049b634 ===

undefined4 cbNotifyUpdateRefreshed(void)

{
  return 0;
}



// === cbNotifyProcStatUpdate @ 0049b644 ===

undefined4 cbNotifyProcStatUpdate(void)

{
  return 0;
}



// === set_update_printstate @ 0049b710 ===

void set_update_printstate(undefined1 param_1)

{
  update_printstate = param_1;
  return;
}



// === cbNotifyStatusUpdate @ 0049b8f4 ===

/* WARNING: Control flow encountered bad instruction data */

undefined4 cbNotifyStatusUpdate(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  size_t sVar9;
  int iVar10;
  uint uVar11;
  timespec *ptVar12;
  int iVar13;
  __time_t _Var14;
  __time_t _Var15;
  __time_t _Var16;
  __time_t _Var17;
  int iVar18;
  char *pcVar19;
  char *pcVar20;
  undefined1 *__s2;
  undefined **ppuVar21;
  char *pcVar22;
  uint uVar23;
  undefined8 uVar24;
  float fVar25;
  double dVar26;
  double dVar27;
  timespec local_188;
  char *local_180;
  long local_17c;
  int local_178;
  undefined4 local_174;
  char *local_170;
  undefined4 local_16c;
  int local_168;
  undefined4 local_164;
  char *local_160;
  undefined4 local_15c;
  int local_158;
  undefined4 local_154;
  char *local_150;
  undefined4 local_14c;
  int local_148;
  undefined4 local_144;
  char *local_140;
  undefined4 local_13c;
  int local_138;
  undefined4 local_134;
  char *local_130;
  undefined4 local_12c;
  int local_128;
  undefined4 local_124;
  char *local_120;
  char *local_88;
  undefined4 local_84;
  char *local_80;
  undefined4 local_7c;
  int local_78;
  undefined4 local_74;
  char *local_70;
  undefined4 local_6c;
  undefined8 local_68;
  char *local_60;
  char *local_5c;
  char *local_58;
  int local_54;
  char *local_50;
  char *local_4c;
  char *local_48;
  pthread_mutex_t *local_44;
  undefined4 local_3c;
  
  local_3c = 0;
  iVar18 = *(int *)(param_1 + 8);
  if (iVar18 == 0) {
    return 0;
  }
  update_printstate = '\0';
  uVar2 = cJSON_GetArrayItem(iVar18,0);
  cJSON_GetArrayItem(iVar18,1);
  iVar18 = getodin();
  iVar3 = cJSON_GetObjectItem(uVar2,"bed_mesh");
  if (((iVar3 != 0) && (iVar4 = cJSON_GetObjectItem(iVar3,"probed_matrix"), iVar4 != 0)) &&
     (iVar5 = cJSON_IsArray(iVar4), iVar5 != 0)) {
    iVar5 = cJSON_GetArraySize(iVar4);
    if (0 < iVar5) {
      uVar6 = cJSON_GetArrayItem(iVar4,0);
      iVar7 = cJSON_GetArraySize(uVar6);
      if ((iVar5 == 7) && (iVar7 == 7)) {
        iVar5 = 0;
        iVar3 = getodin();
        *(undefined4 *)(iVar3 + 0x163c) = 7;
        iVar3 = getodin();
        *(undefined4 *)(iVar3 + 0x1640) = 7;
        do {
          iVar3 = cJSON_GetArrayItem(iVar4,iVar5);
          if ((iVar3 != 0) && (iVar7 = cJSON_IsArray(iVar3), iVar7 != 0)) {
            iVar7 = 0;
            local_68 = (double)CONCAT44(local_68._4_4_,iVar5 * 7);
            do {
              iVar8 = cJSON_GetArrayItem(iVar3,iVar7);
              iVar10 = cJSON_IsNumber(iVar8);
              fVar25 = 0.0;
              if (iVar10 != 0) {
                fVar25 = (float)*(double *)(iVar8 + 0x18);
              }
              local_3c = 0;
              iVar8 = getodin();
              local_3c = 0;
              *(float *)(iVar8 + ((int)(char *)local_68 + iVar7 + 0x590) * 4 + 4) = fVar25;
              iVar7 = iVar7 + 1;
            } while (iVar7 != 7);
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 != 7);
        goto LAB_0049bb3c;
      }
    }
    iVar3 = cJSON_GetObjectItem(iVar3,"profiles");
    if ((((iVar3 != 0) && (iVar3 = cJSON_GetObjectItem(iVar3,"default"), iVar3 != 0)) &&
        (iVar3 = cJSON_GetObjectItem(iVar3,"points"), iVar3 != 0)) &&
       ((iVar4 = cJSON_IsArray(iVar3), iVar4 != 0 && (iVar4 = cJSON_GetArraySize(iVar3), 0 < iVar4))
       )) {
      uVar6 = cJSON_GetArrayItem(iVar3,0);
      iVar5 = cJSON_GetArraySize(uVar6);
      if ((iVar4 == 7) && (iVar5 == 7)) {
        iVar4 = getodin();
        *(undefined4 *)(iVar4 + 0x163c) = 7;
        iVar4 = getodin();
        *(undefined4 *)(iVar4 + 0x1640) = 7;
        iVar4 = 0;
        do {
          iVar5 = cJSON_GetArrayItem(iVar3,iVar4);
          if (iVar5 != 0) {
            iVar7 = cJSON_IsArray(iVar5);
            if (iVar7 != 0) {
              iVar7 = 0;
              local_68 = (double)CONCAT44(local_68._4_4_,iVar4 * 7);
              do {
                local_60 = (char *)cJSON_GetArrayItem(iVar5,iVar7);
                iVar8 = cJSON_IsNumber(local_60);
                fVar25 = 0.0;
                if (iVar8 != 0) {
                  fVar25 = (float)*(double *)((int)local_60 + 0x18);
                }
                local_3c = 0;
                iVar8 = getodin();
                local_3c = 0;
                iVar10 = (int)(char *)local_68 + iVar7;
                iVar7 = iVar7 + 1;
                *(float *)(iVar8 + (iVar10 + 0x590) * 4 + 4) = fVar25;
              } while (iVar7 != 7);
            }
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 != 7);
      }
    }
  }
LAB_0049bb3c:
  iVar3 = cJSON_GetObjectItem(uVar2,&DAT_00596568);
  if ((iVar3 != 0) && (iVar3 = cJSON_GetObjectItem(iVar3,"mcu_version"), iVar3 != 0)) {
    iVar4 = getodin();
    lv_snprintf(iVar4 + 0x1708,0x20,"%s",*(undefined4 *)(iVar3 + 0x10));
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
               ,0x9ee,"cbNotifyStatusUpdate","mcu_version : %s\n",*(undefined4 *)(iVar3 + 0x10));
  }
  iVar3 = cJSON_GetObjectItem(uVar2,"mcu leveling_mcu");
  if ((iVar3 != 0) && (iVar3 = cJSON_GetObjectItem(iVar3,"mcu_version"), iVar3 != 0)) {
    iVar4 = getodin();
    lv_snprintf(iVar4 + 0x1728,0x20,"%s",*(undefined4 *)(iVar3 + 0x10));
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
               ,0x9f7,"cbNotifyStatusUpdate","mcu_leveling_version : %s\n",
               *(undefined4 *)(iVar3 + 0x10));
  }
  iVar3 = cJSON_GetObjectItem(uVar2,"mcu nozzle_mcu");
  if ((iVar3 != 0) && (iVar3 = cJSON_GetObjectItem(iVar3,"mcu_version"), iVar3 != 0)) {
    iVar4 = getodin();
    lv_snprintf(iVar4 + 0x1748,0x20,"%s",*(undefined4 *)(iVar3 + 0x10));
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
               ,0xa00,"cbNotifyStatusUpdate","mcu_version : %s\n",*(undefined4 *)(iVar3 + 0x10));
  }
  iVar3 = cJSON_GetObjectItem(uVar2,"gcode_move");
  if (iVar3 != 0) {
    local_188.tv_sec = iVar18 + 0x2350;
    local_188.tv_nsec = 0x100;
    local_174 = 0x100;
    local_164 = 0x100;
    local_180 = "speed";
    local_154 = 8;
    local_178 = iVar18 + 0x2358;
    local_168 = iVar18 + 0x2360;
    local_158 = iVar18 + 0x236a;
    local_170 = "speed_factor";
    local_160 = "extrude_factor";
    local_150 = "qmode_status";
    local_17c = 0;
    local_16c = 0;
    local_15c = 0;
    local_14c = 0;
    extract_from_json(iVar3,&local_188,4,1);
    dump_extracted_from_json(iVar3,&local_188,4);
    iVar4 = cJSON_GetObjectItem(iVar3,"gcode_position");
    if ((iVar4 != 0) && (iVar5 = cJSON_IsArray(iVar4), iVar5 != 0)) {
      iVar5 = cJSON_GetArraySize(iVar4);
      if (0 < iVar5) {
        iVar7 = 0;
        do {
          iVar8 = cJSON_GetArrayItem(iVar4,iVar7);
          local_68 = (double)CONCAT44(local_68._4_4_,iVar8);
          if (iVar8 != 0) {
            iVar8 = getodin();
            local_3c = 0;
            *(undefined8 *)((iVar7 + 0x45e) * 8 + iVar8) =
                 *(undefined8 *)((int)(char *)local_68 + 0x18);
          }
          iVar7 = iVar7 + 1;
        } while (iVar5 != iVar7);
      }
      utilUpdateCurrentFileLayer();
    }
    iVar4 = cJSON_GetObjectItem(iVar3,"position");
    if (((iVar4 != 0) && (iVar5 = cJSON_IsArray(iVar4), iVar5 != 0)) &&
       (iVar5 = cJSON_GetArraySize(iVar4), 0 < iVar5)) {
      iVar7 = 0;
      do {
        iVar8 = cJSON_GetArrayItem(iVar4,iVar7);
        local_68 = (double)CONCAT44(local_68._4_4_,iVar8);
        if (iVar8 != 0) {
          iVar8 = getodin();
          local_3c = 0;
          *(undefined8 *)((iVar7 + 0x462) * 8 + iVar8) =
               *(undefined8 *)((int)(char *)local_68 + 0x18);
        }
        iVar7 = iVar7 + 1;
      } while (iVar5 != iVar7);
    }
    iVar4 = cJSON_GetObjectItem(iVar3,"homing_origin");
    if ((iVar4 != 0) && (iVar5 = cJSON_IsArray(iVar4), iVar5 != 0)) {
      iVar5 = cJSON_GetArraySize(iVar4,"extrude_factor");
      if (0 < iVar5) {
        local_3c = 0;
        dVar27 = 0.0;
        iVar7 = 0;
        dVar26 = DAT_005976d0;
        do {
          iVar8 = cJSON_GetArrayItem(iVar4,iVar7);
          if (iVar8 != 0) {
            local_3c = 0;
            local_68 = round(*(double *)(iVar8 + 0x18) * dVar26 + dVar27);
            local_3c = 0;
            iVar8 = getodin();
            local_3c = 0;
            *(double *)((iVar7 + 0x466) * 8 + iVar8) = local_68 / dVar26;
          }
          iVar7 = iVar7 + 1;
        } while (iVar5 != iVar7);
      }
      local_88 = (char *)0x9;
      service_gui_request(0xd,&local_88,4);
      iVar4 = getodin();
      local_3c = 0;
      if (*(double *)(iVar4 + 0x2340) <= DAT_005959a0) {
        iVar4 = getodin();
        local_3c = 0;
        if (DAT_005959a8 <= *(double *)(iVar4 + 0x2340)) goto LAB_0049bfbc;
      }
      local_3c = 0;
      service_gui_request(0x1f,0,0);
    }
LAB_0049bfbc:
    iVar4 = cJSON_GetObjectItem(iVar3,"extrude_factor");
    if (iVar4 != 0) {
      local_88 = (char *)0x10;
      service_gui_request(0xd,&local_88,4);
    }
    update_printstate = '\x01';
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"heater_bed");
  if (iVar4 == 0) {
LAB_0049c0c4:
    iVar4 = cJSON_GetObjectItem(uVar2,"extruder");
    if (iVar4 != 0) goto LAB_0049c0dc;
LAB_0049c19c:
    iVar4 = cJSON_GetObjectItem(uVar2,"temperature_fan main_board");
  }
  else {
    local_188.tv_sec = iVar18 + 0x2010;
    local_180 = "temperature";
    local_178 = iVar18 + 0x2018;
    local_188.tv_nsec = 0x100;
    local_174 = 0x100;
    local_170 = "target";
    local_17c = 0;
    local_16c = 0;
    extract_from_json(iVar4,&local_188,2,1);
    update_printstate = '\x01';
    iVar4 = getodin();
    local_88 = (char *)0x2;
    if (*(char *)(iVar4 + 0x26fa) == '\0') {
      local_3c = 0;
      uVar23 = (uint)(*(double *)(iVar18 + 0x2010) - *(double *)(iVar18 + 0x2018));
      uVar11 = (int)uVar23 >> 0x1f;
      if (((int)((uVar11 ^ uVar23) - uVar11) < 3) ||
         (local_3c = 0, *(double *)(iVar18 + 0x2018) == 0.0)) goto LAB_0049c0c4;
      iVar4 = getodin();
      *(undefined1 *)(iVar4 + 0x26fa) = 1;
      uVar6 = 0x10;
    }
    else {
      local_3c = 0;
      if (*(double *)(iVar18 + 0x2018) != 0.0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar4 = getodin();
      *(undefined1 *)(iVar4 + 0x26fa) = 0;
      uVar6 = 4;
    }
    service_gui_request(0xd,&local_88,uVar6);
    iVar4 = cJSON_GetObjectItem(uVar2,"extruder");
    if (iVar4 == 0) goto LAB_0049c19c;
LAB_0049c0dc:
    local_188.tv_sec = iVar18 + 0x2020;
    local_180 = "temperature";
    local_178 = iVar18 + 0x2028;
    local_188.tv_nsec = 0x100;
    local_174 = 0x100;
    local_170 = "target";
    local_17c = 0;
    local_16c = 0;
    extract_from_json(iVar4,&local_188,2,1);
    update_printstate = '\x01';
    iVar4 = getodin();
    local_3c = 0;
    local_88 = (char *)0x1;
    if (*(double *)(iVar18 + 0x2028) != 0.0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    if (*(char *)(iVar4 + 0x26f9) == '\0') goto LAB_0049c19c;
    iVar4 = getodin();
    *(undefined1 *)(iVar4 + 0x26f9) = 0;
    service_gui_request(0xd,&local_88,4);
    iVar4 = cJSON_GetObjectItem(uVar2,"temperature_fan main_board");
  }
  if (iVar4 != 0) {
    local_180 = "temperature";
    local_188.tv_sec = iVar18 + 0x2268;
    local_178 = iVar18 + 0x2270;
    local_17c = 0;
    local_16c = 0;
    local_188.tv_nsec = 0x100;
    local_174 = 0x100;
    local_170 = "target";
    extract_from_json(iVar4,&local_188,2,1);
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"temperature_sensor chassis");
  if (iVar4 == 0) {
LAB_0049c2f0:
    iVar4 = cJSON_GetObjectItem(uVar2,"toolhead");
  }
  else {
    iVar5 = getodin();
    if (*(char *)(iVar5 + 0x26fc) == '\0') {
      iVar5 = getodin();
      *(undefined1 *)(iVar5 + 0x26fc) = 1;
      local_188.tv_sec = 6;
      service_gui_request(0xd,&local_188,4);
    }
    local_188.tv_sec = iVar18 + 0x2258;
    local_180 = "temperature";
    local_178 = iVar18 + 0x2260;
    local_188.tv_nsec = 0x100;
    local_174 = 0x100;
    local_170 = "target";
    local_17c = 0;
    local_16c = 0;
    extract_from_json(iVar4,&local_188,2,1);
    iVar4 = getodin();
    local_88 = (char *)0x3;
    if (*(char *)(iVar4 + 0x26fb) == '\0') {
      local_3c = 0;
      uVar23 = (uint)(*(double *)(iVar18 + 0x2258) - *(double *)(iVar18 + 0x2260));
      uVar11 = (int)uVar23 >> 0x1f;
      if (((int)((uVar11 ^ uVar23) - uVar11) < 3) ||
         (local_3c = 0, *(double *)(iVar18 + 0x2260) == 0.0)) goto LAB_0049c2f0;
      iVar4 = getodin();
      *(undefined1 *)(iVar4 + 0x26fb) = 1;
      uVar6 = 0x10;
    }
    else {
      local_3c = 0;
      if (*(double *)(iVar18 + 0x2260) != 0.0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar4 = getodin();
      *(undefined1 *)(iVar4 + 0x26fb) = 0;
      uVar6 = 4;
    }
    service_gui_request(0xd,&local_88,uVar6);
    iVar4 = cJSON_GetObjectItem(uVar2,"toolhead");
  }
  if (iVar4 != 0) {
    memset(&local_17c,0,100);
    local_188.tv_sec = iVar18 + 0x2030;
    local_180 = "print_time";
    local_170 = "estimated_print_time";
    local_164 = 0x10;
    local_15c = 0x40;
    local_150 = "max_velocity";
    local_188.tv_nsec = 0x100;
    local_174 = 0x100;
    local_154 = 0x100;
    local_144 = 0x100;
    local_140 = "max_accel";
    local_134 = 0x100;
    local_124 = 0x100;
    local_178 = iVar18 + 0x2038;
    local_168 = iVar18 + 0x2040;
    local_158 = iVar18 + 0x2080;
    local_148 = iVar18 + 0x2088;
    local_138 = iVar18 + 0x2090;
    local_128 = iVar18 + 0x2098;
    local_130 = "square_corner_velocity";
    local_120 = "max_accel_to_decel";
    local_160 = "homed_axes";
    extract_from_json(iVar4,&local_188,7,1);
    iVar4 = cJSON_GetObjectItem(iVar4,"homed_axes");
    if (iVar4 != 0) {
      pcVar19 = strchr(*(char **)(iVar4 + 0x10),0x78);
      iVar5 = getodin();
      pcVar20 = *(char **)(iVar4 + 0x10);
      *(bool *)(iVar5 + 10000) = pcVar19 != (char *)0x0;
      pcVar19 = strchr(pcVar20,0x79);
      iVar5 = getodin();
      pcVar20 = *(char **)(iVar4 + 0x10);
      *(bool *)(iVar5 + 0x2711) = pcVar19 != (char *)0x0;
      pcVar19 = strchr(pcVar20,0x7a);
      iVar4 = getodin();
      *(bool *)(iVar4 + 0x2712) = pcVar19 != (char *)0x0;
      update_printstate = '\x01';
    }
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"print_stats");
  if (iVar4 != 0) {
    iVar5 = cJSON_GetObjectItem(iVar4,"filename");
    if ((iVar5 != 0) && (**(char **)(iVar5 + 0x10) != '\0')) {
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
                 ,0xacb,"cbNotifyStatusUpdate","print_stats.filename=%s",*(char **)(iVar5 + 0x10));
      ws_run_cmd("cx_server.files.metadata",0,"%s",*(undefined4 *)(iVar5 + 0x10));
      iVar7 = getodin();
      snprintf((char *)(iVar7 + 0xe6c),0x100,"%s",*(undefined4 *)(iVar5 + 0x10));
    }
    memset(&local_16c,0,0x54);
    local_168 = iVar18 + 0x20b8;
    local_188.tv_nsec = 0x10;
    local_17c = 0x10;
    local_144 = 0x10;
    local_134 = 0x10;
    local_174 = 0x100;
    local_164 = 0x100;
    local_160 = "total_duration";
    local_154 = 0x100;
    local_13c = 0x100;
    local_124 = 0x100;
    local_188.tv_sec = iVar18 + 0x20a0;
    local_178 = iVar18 + 0x20b0;
    local_158 = iVar18 + 0x20c0;
    local_148 = iVar18 + 0x20c8;
    local_138 = iVar18 + 0x21d0;
    local_128 = iVar18 + 0x2250;
    local_130 = "message";
    local_180 = "state";
    local_170 = "print_duration";
    local_150 = "filament_used";
    local_140 = "filename";
    local_12c = 0x80;
    local_120 = "z_pos";
    extract_from_json(iVar4,&local_188,7,1);
    iVar5 = cJSON_GetObjectItem(iVar4,"info");
    if (iVar5 != 0) {
      local_88 = (char *)(iVar18 + 0x21cc);
      local_78 = iVar18 + 0x21c8;
      local_7c = 0;
      local_6c = 0;
      local_84 = 8;
      local_80 = "current_layer";
      local_74 = 8;
      local_70 = "total_layer";
      extract_from_json(iVar5,&local_88,2,1);
    }
    iVar5 = cJSON_GetObjectItem(iVar4,"state");
    if (iVar5 != 0) {
      get_printer_work_state();
      accquire_print_state();
      iVar5 = strcasecmp(*(char **)(iVar5 + 0x10),"printing");
      if (iVar5 == 0) {
        utilUpdateCurrentPrintInfo();
        local_88 = (char *)0x5;
        service_gui_request(0xd,&local_88,4);
      }
    }
    iVar5 = cJSON_GetObjectItem(iVar4,"print_duration");
    if (iVar5 != 0) {
      utilUpdateCurrentPrintInfo();
    }
    cJSON_GetObjectItem(iVar4,"current_layer");
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"motion_report");
  if (iVar4 != 0) {
    iVar5 = cJSON_GetObjectItem(iVar4,"live_position");
    if (((iVar5 != 0) && (iVar7 = cJSON_IsArray(iVar5), iVar7 != 0)) &&
       (iVar7 = cJSON_GetArraySize(iVar5), 0 < iVar7)) {
      iVar8 = 0;
      do {
        iVar10 = cJSON_GetArrayItem(iVar5,iVar8);
        local_68 = (double)CONCAT44(local_68._4_4_,iVar10);
        if (iVar10 != 0) {
          iVar10 = getodin();
          local_3c = 0;
          *(undefined8 *)((iVar8 + 0x44f) * 8 + iVar10) =
               *(undefined8 *)((int)(char *)local_68 + 0x18);
        }
        iVar8 = iVar8 + 1;
      } while (iVar7 != iVar8);
    }
    iVar4 = cJSON_GetObjectItem(iVar4,"live_velocity");
    if (iVar4 != 0) {
      iVar5 = getodin();
      local_3c = 0;
      dVar27 = *(double *)(iVar5 + 0x2298);
      dVar26 = DAT_005976d8;
      local_68 = round(*(double *)(iVar4 + 0x18) * DAT_005976d8 + 0.0);
      local_3c = 0;
      iVar4 = getodin();
      local_3c = 0;
      *(double *)(iVar4 + 0x2298) = local_68 / dVar26;
      uVar6 = get_printer_work_state();
      iVar4 = printer_is_working(uVar6);
      if (iVar4 != 0) {
        iVar4 = getodin();
        local_3c = 0;
        if (*(double *)(iVar4 + 0x2298) != dVar27) {
          local_188.tv_sec = 0xb;
          service_gui_request(0xd,&local_188,4);
          update_printstate = '\x01';
          goto LAB_0049c7c0;
        }
      }
    }
    update_printstate = '\x01';
  }
LAB_0049c7c0:
  iVar4 = cJSON_GetObjectItem(uVar2,"virtual_sdcard");
  if (iVar4 != 0) {
    local_178 = iVar18 + 0x237d;
    local_174 = 0x10;
    local_170 = "file_path";
    local_164 = 8;
    local_188.tv_sec = iVar18 + 0x2370;
    local_168 = iVar18 + 0x2378;
    local_188.tv_nsec = 0x100;
    local_16c = 0x100;
    local_160 = "file_position";
    local_180 = "progress";
    local_17c = 0;
    local_15c = 0;
    extract_from_json(iVar4,&local_188,3,1);
    dump_extracted_from_json(iVar4,&local_188,3);
    utilUpdateCurrentFileLayer();
    iVar4 = cJSON_GetObjectItem(iVar4,"progress");
    if (iVar4 != 0) {
      utilUpdateCurrentPrintInfo();
    }
    update_printstate = '\x01';
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"display_status");
  if (iVar4 != 0) {
    local_188.tv_sec = iVar18 + 0x24a0;
    local_188.tv_nsec = 0x100;
    local_180 = "progress";
    local_17c = 0;
    extract_from_json(iVar4,&local_188,1,1);
    dump_extracted_from_json(iVar4,&local_188,1);
    iVar4 = cJSON_GetObjectItem(iVar4,"progress");
    if (iVar4 != 0) {
      utilUpdateCurrentPrintInfo();
    }
  }
  local_68._0_4_ = "rpm";
  local_60 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
  ppuVar21 = &fan_config_list;
  local_58 = "cbNotifyStatusUpdate";
  local_5c = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
  do {
    iVar4 = cJSON_GetObjectItem(uVar2,*ppuVar21);
    if (iVar4 != 0) {
      local_188.tv_nsec = 0x100;
      local_174 = 0x100;
      local_188.tv_sec = iVar18 + 0x2010 + (int)(ppuVar21[1] + 0x29) * 0x10;
      local_178 = iVar18 + 0x2010 + (int)(ppuVar21[1] + 0x29) * 0x10 + 8;
      local_170 = (char *)local_68;
      local_180 = "speed";
      local_17c = 0;
      local_16c = 0;
      extract_from_json(iVar4,&local_188,2,1);
      iVar5 = getodin();
      ppuVar21[1][iVar5 + 0x2784] = 1;
      update_printstate = '\x01';
      iVar4 = cJSON_GetObjectItem(iVar4,"speed");
      if (iVar4 != 0) {
        local_3c = 0;
        lv_log_add(2,4,local_5c + 0x5d8c,0xb4c,local_58,local_60 + 0x67e8,*ppuVar21);
        local_88 = (char *)0xc;
        service_gui_request(0xd,&local_88,0x10);
      }
    }
    ppuVar21 = ppuVar21 + 3;
  } while (ppuVar21 != &unpack_cgi_cmds);
  iVar4 = cJSON_GetObjectItem(uVar2,"webhooks");
  if ((iVar4 != 0) && (iVar5 = cJSON_GetObjectItem(iVar4,"state"), iVar5 != 0)) {
    iVar5 = strcmp(*(char **)(iVar5 + 0x10),(char *)(iVar18 + 0x24a8));
    if (iVar5 != 0) {
      local_84 = 0x10;
      local_7c = 10;
      local_80 = "state";
      local_88 = (char *)(iVar18 + 0x24a8);
      extract_from_json(iVar4,&local_88,1,1);
      iVar5 = getodin();
      iVar5 = strcmp((char *)(iVar5 + 0x24a8),"ready");
      if (iVar5 != 0) {
        iVar5 = getodin();
        iVar5 = strcmp((char *)(iVar5 + 0x24a8),"startup");
        if (iVar5 != 0) {
          iVar5 = getodin();
          *(undefined1 *)(iVar5 + 0x26f8) = 0;
          iVar4 = cJSON_GetObjectItem(iVar4,"state_message");
          if (iVar4 != 0) {
            local_60 = (char *)cJSON_Parse(*(undefined4 *)(iVar4 + 0x10));
            if (local_60 == (char *)0x0) {
              puts("unknown faultcode content");
            }
            else {
              iVar4 = cJSON_GetObjectItem(local_60,"code");
              if (iVar4 != 0) {
                pcVar19 = *(char **)(iVar4 + 0x10);
                if (pcVar19 != (char *)0x0) {
                  __s2 = restart_klipper_errcode;
                  pcVar20 = (char *)0x0;
                  local_68._0_4_ = (char *)0xc;
                  do {
                    iVar4 = strcmp(pcVar19,__s2);
                    if (iVar4 == 0) {
                      iVar4 = (int)pcVar20 * 0x10;
                      local_68._0_4_ = restart_klipper_errcode + iVar4;
                      clock_gettime(1,&local_188);
                      pcVar20 = (char *)local_68 + 0xc;
                      local_5c = (char *)local_68;
                      local_68._0_4_ = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
                      pcVar22 = (char *)local_188.tv_sec;
                      lv_log_add(2,4,
                                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
                                 ,0x924,"isNeedRestartErrorCode",
                                 "last_restart_time--%d -- ts.tv_sec --%d",*(undefined4 *)pcVar20,
                                 local_188.tv_sec);
                      if (((byte)local_5c[10] < (byte)local_5c[0xb]) &&
                         ((iVar5 = *(int *)(local_5c + 0xc), iVar5 == 0 ||
                          ((char *)0x90 < (char *)(local_188.tv_sec + (-6 - iVar5)))))) {
                        if ((uint)(local_188.tv_sec - iVar5) < 0x97) {
                          *(__time_t *)(restart_klipper_errcode + iVar4 + 0xc) = local_188.tv_sec;
                        }
                        else {
                          restart_klipper_errcode[iVar4 + 10] = local_5c[10] + 1;
                          *(__time_t *)(restart_klipper_errcode + iVar4 + 0xc) = local_188.tv_sec;
                        }
                        upload_error_code(pcVar19,0);
                        iVar4 = getodin();
                        lv_log_add(2,4,(char *)local_68 + 0x5d8c,0xb82,"cbNotifyStatusUpdate",
                                   "vectorp restart klipper is_klipper_start_by_gui=%d",
                                   *(undefined1 *)(iVar4 + 0x36c5),pcVar22);
                        iVar4 = getodin();
                        if (*(char *)(iVar4 + 0x36c5) == '\0') {
                          iVar4 = getodin();
                          *(undefined1 *)(iVar4 + 0x2bc8) = 0;
                          iVar4 = getodin();
                          *(undefined1 *)(iVar4 + 0x36c5) = 1;
                          memset(&local_158,0,0xd0);
                          pcVar20 = "/usr/apps/etc/init.d/CS55klipper_service restart";
                          ptVar12 = &local_188;
                          do {
                            _Var17 = *(__time_t *)pcVar20;
                            _Var16 = *(__time_t *)((int)pcVar20 + 4);
                            _Var15 = *(__time_t *)((int)pcVar20 + 8);
                            _Var14 = *(__time_t *)((int)pcVar20 + 0xc);
                            pcVar20 = (char *)((int)pcVar20 + 0x10);
                            ptVar12->tv_sec = _Var17;
                            ptVar12->tv_nsec = _Var16;
                            ptVar12[1].tv_sec = _Var15;
                            ptVar12[1].tv_nsec = _Var14;
                            ptVar12 = ptVar12 + 2;
                          } while ((__time_t *)pcVar20 != (__time_t *)0x595bb8);
                          *(char *)&ptVar12->tv_sec =
                               s__usr_apps_etc_init_d_CS55klipper_00595b88[0x30];
                          system((char *)&local_188);
                          iVar4 = getodin();
                          snprintf((char *)(iVar4 + 0x36c7),10,"%s",pcVar19);
                          if (klipper_restart_timeout_timer != 0) {
                            lv_timer_delete();
                          }
                          klipper_restart_timeout_timer = 0;
                          klipper_restart_timeout_timer =
                               lv_timer_create(kilpper_restart_timeout_timer_callback,60000,0);
                          lv_timer_set_repeat_count(klipper_restart_timeout_timer,1);
                        }
                        goto LAB_0049d3f4;
                      }
                      if (exit_printing_timer == 0) {
                        exit_printing_timer = lv_timer_create(exit_printing_timer_callback,2000,0);
                        lv_timer_set_repeat_count(exit_printing_timer,1);
                        *(__time_t *)(restart_klipper_errcode + iVar4 + 0xc) = local_188.tv_sec;
                      }
                      else {
                        lv_timer_reset();
                        *(__time_t *)(restart_klipper_errcode + iVar4 + 0xc) = local_188.tv_sec;
                      }
                      break;
                    }
                    pcVar20 = pcVar20 + 1;
                    __s2 = __s2 + 0x10;
                  } while (pcVar20 != (char *)local_68);
                  iVar4 = getodin();
                  if ((*(char *)(iVar4 + 0x2bca) == '\0') &&
                     ((iVar4 = isInNotifyDelayErrorCode(pcVar19,0), iVar4 == 0 ||
                      (iVar4 = isNotifyDelayErrorCode(), iVar4 == 0)))) {
                    sVar9 = strlen(pcVar19);
                    service_gui_request(0xf,pcVar19,sVar9 + 1);
                  }
                  else {
                    upload_error_code(pcVar19,0);
                  }
                }
              }
LAB_0049d3f4:
              cJSON_Delete(local_60);
            }
          }
        }
      }
    }
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"motor_music");
  if (iVar4 != 0) {
    local_188.tv_sec = iVar18 + 0x26f4;
    local_188.tv_nsec = 8;
    local_180 = "status";
    local_17c = 0;
    extract_from_json(iVar4,&local_188,1,1);
    local_88 = (char *)0x12;
    service_gui_request(0xd,&local_88,0x10);
  }
  iVar4 = cJSON_GetObjectItem(uVar2,"exclude_object");
  if (iVar4 != 0) {
    local_60 = (char *)(iVar18 + 0x20c8);
    local_5c = "cbNotifyStatusUpdate";
    local_68._0_4_ = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
    local_44 = (pthread_mutex_t *)(iVar18 + 0x26c4);
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
               ,3000,"cbNotifyStatusUpdate","get file: %s exclude_object",local_60);
    pthread_mutex_lock((pthread_mutex_t *)(iVar18 + 0x26c4));
    iVar5 = cJSON_GetObjectItem(iVar4,"excluded_objects");
    if (iVar5 != 0) {
      iVar7 = cJSON_GetArraySize(iVar5);
      if (*(int *)(iVar18 + 0x25b4) != 0) {
        lv_free();
      }
      uVar6 = lv_malloc_zeroed(iVar7 << 8);
      *(undefined4 *)(iVar18 + 0x25b4) = uVar6;
      *(int *)(iVar18 + 0x26b8) = iVar7;
      if (0 < iVar7) {
        iVar8 = 0;
        do {
          iVar10 = cJSON_GetArrayItem(iVar5,iVar8);
          iVar13 = iVar8 * 0x100;
          iVar8 = iVar8 + 1;
          if (iVar10 != 0) {
            strncpy((char *)(*(int *)(iVar18 + 0x25b4) + iVar13),*(char **)(iVar10 + 0x10),0x100);
          }
        } while (iVar7 != iVar8);
      }
    }
    local_58 = (char *)cJSON_GetObjectItem(iVar4,"objects");
    if (local_58 == (char *)0x0) {
LAB_0049cd58:
      local_60 = *(char **)(iVar18 + 0x26c0);
      if (0 < (int)local_60) {
        local_5c = *(char **)(iVar18 + 0x26bc);
        local_58 = (char *)(iVar18 + 0x24b4);
        local_68._0_4_ = (char *)0x0;
        pcVar19 = local_5c + 0x10;
        do {
          if (local_5c == (char *)0x0) break;
          pcVar19[0x108] = '\0';
          pcVar19[0x109] = '\0';
          pcVar19[0x10a] = '\0';
          pcVar19[0x10b] = '\0';
          iVar4 = strcmp(pcVar19,local_58);
          if (iVar4 == 0) {
            pcVar19[0x108] = '\x01';
            pcVar19[0x109] = '\0';
            pcVar19[0x10a] = '\0';
            pcVar19[0x10b] = '\0';
          }
          if (0 < *(int *)(iVar18 + 0x26b8)) {
            pcVar22 = *(char **)(iVar18 + 0x25b4);
            pcVar20 = pcVar22 + *(int *)(iVar18 + 0x26b8) * 0x100;
            do {
              iVar4 = strcmp(pcVar19,pcVar22);
              pcVar22 = pcVar22 + 0x100;
              if (iVar4 == 0) {
                pcVar19[0x108] = '\x02';
                pcVar19[0x109] = '\0';
                pcVar19[0x10a] = '\0';
                pcVar19[0x10b] = '\0';
              }
            } while (pcVar22 != pcVar20);
          }
          pcVar19 = pcVar19 + 0x120;
          local_68._0_4_ = (char *)0x1;
        } while (local_60 != (char *)0x1);
      }
    }
    else {
      local_54 = cJSON_GetArraySize(local_58);
      lv_log_add(2,4,(char *)local_68 + 0x5d8c,0xbd5,local_5c,"get file: %s exclude_object_size=%d",
                 local_60,local_54);
      if (*(int *)(iVar18 + 0x26bc) != 0) {
        lv_free();
      }
      iVar4 = local_54;
      uVar6 = lv_malloc_zeroed(local_54 * 0x120);
      *(undefined4 *)(iVar18 + 0x26bc) = uVar6;
      *(int *)(iVar18 + 0x26c0) = iVar4;
      if (0 < iVar4) {
        local_50 = "center";
        local_4c = "name";
        iVar4 = 0;
        local_48 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
        do {
          iVar5 = cJSON_GetArrayItem(local_58,iVar4);
          if (iVar5 != 0) {
            iVar7 = cJSON_GetObjectItem(iVar5,local_50);
            local_5c = (char *)(iVar4 * 0x120);
            if (iVar7 == 0) {
              local_188.tv_sec = (__time_t)(local_5c + *(int *)(iVar18 + 0x26bc));
            }
            else {
              iVar8 = cJSON_GetArraySize(iVar7);
              if (iVar8 == 2) {
                iVar8 = cJSON_GetArrayItem(iVar7,0);
                local_3c = 0;
                uVar24 = 0;
                if (iVar8 != 0) {
                  iVar8 = cJSON_GetArrayItem(iVar7,0);
                  uVar24 = *(undefined8 *)(iVar8 + 0x18);
                }
                local_3c = 0;
                *(undefined8 *)(local_5c + *(int *)(iVar18 + 0x26bc)) = uVar24;
                iVar8 = cJSON_GetArrayItem(iVar7,1);
                local_3c = 0;
                uVar24 = 0;
                if (iVar8 != 0) {
                  iVar7 = cJSON_GetArrayItem(iVar7,1);
                  uVar24 = *(undefined8 *)(iVar7 + 0x18);
                }
                local_3c = 0;
                local_188.tv_sec = (__time_t)(local_5c + *(int *)(iVar18 + 0x26bc));
                *(undefined8 *)(local_188.tv_sec + 8) = uVar24;
              }
              else {
                local_188.tv_sec = (__time_t)(local_5c + *(int *)(iVar18 + 0x26bc));
              }
            }
            local_188.tv_sec = local_188.tv_sec + 0x10;
            local_188.tv_nsec = 0x10;
            local_180 = local_4c;
            local_17c = 0x100;
            extract_from_json(iVar5,&local_188,1,0);
            iVar5 = cJSON_GetObjectItem(iVar5,local_48 + 0x6920);
            if (iVar5 != 0) {
              local_60 = (char *)cJSON_GetArraySize(iVar5);
              pcVar19 = local_5c + *(int *)(iVar18 + 0x26bc);
              if (*(int *)(pcVar19 + 0x110) != 0) {
                lv_free();
                pcVar19 = local_5c + *(int *)(iVar18 + 0x26bc);
              }
              uVar6 = lv_malloc_zeroed((int)local_60 << 4);
              iVar7 = *(int *)(iVar18 + 0x26bc);
              *(undefined4 *)(pcVar19 + 0x110) = uVar6;
              *(char **)(local_5c + iVar7 + 0x114) = local_60;
              if (0 < (int)local_60) {
                pcVar19 = (char *)0x0;
                do {
                  pcVar20 = (char *)cJSON_GetArrayItem(iVar5,pcVar19);
                  if (*(int *)(iVar18 + 0x26bc) == 0) goto LAB_0049cd64;
                  local_68._0_4_ = pcVar20;
                  if ((pcVar20 != (char *)0x0) && (iVar7 = cJSON_GetArraySize(pcVar20), iVar7 == 2))
                  {
                    iVar7 = cJSON_GetArrayItem((char *)local_68,0);
                    local_3c = 0;
                    uVar24 = 0;
                    if (iVar7 != 0) {
                      iVar7 = cJSON_GetArrayItem((char *)local_68,0);
                      uVar24 = *(undefined8 *)(iVar7 + 0x18);
                    }
                    local_68._0_4_ = (char *)0x0;
                    local_3c = 0;
                    *(undefined8 *)
                     ((int)pcVar19 * 0x10 + *(int *)(local_5c + *(int *)(iVar18 + 0x26bc) + 0x110))
                         = uVar24;
                    iVar7 = cJSON_GetArrayItem(0,1);
                    local_3c = 0;
                    uVar24 = 0;
                    if (iVar7 != 0) {
                      iVar7 = cJSON_GetArrayItem((char *)local_68,1);
                      uVar24 = *(undefined8 *)(iVar7 + 0x18);
                    }
                    local_3c = 0;
                    *(undefined8 *)
                     (*(int *)(local_5c + *(int *)(iVar18 + 0x26bc) + 0x110) + (int)pcVar19 * 0x10 +
                     8) = uVar24;
                  }
                  pcVar19 = pcVar19 + 1;
                } while (local_60 != pcVar19);
              }
            }
          }
          iVar4 = iVar4 + 1;
        } while (local_54 != iVar4);
        goto LAB_0049cd58;
      }
    }
LAB_0049cd64:
    pthread_mutex_unlock(local_44);
    local_188.tv_sec = 8;
    service_gui_request(0xd,&local_188,0x10);
    service_wsslicer_request(8,0,0);
  }
  if (iVar3 != 0) {
    json_qmode_status_18767 = cJSON_GetObjectItem(iVar3,"qmode_status");
    json_speed_factor_18768 = cJSON_GetObjectItem(iVar3,"speed_factor");
    if (json_qmode_status_18767 == 0) {
      if (json_speed_factor_18768 == 0) goto LAB_0049cdf4;
      utilUpdateSpeedMode();
    }
    else {
      utilUpdateSpeedMode();
    }
    if (json_speed_factor_18768 != 0) {
      utilUpdateCurrentPrintInfo();
    }
  }
LAB_0049cdf4:
  iVar3 = cJSON_GetObjectItem(uVar2,"filament_switch_sensor filament_sensor");
  if (iVar3 == 0) {
    iVar3 = cJSON_GetObjectItem(uVar2,"filament_switch_sensor filament_sensor_2");
    if (iVar3 == 0) goto LAB_0049ce84;
LAB_0049cf14:
    local_188.tv_sec = iVar18 + 0x26de;
    local_178 = iVar18 + 0x26df;
    local_188.tv_nsec = 2;
    local_174 = 2;
    local_17c = 0;
    local_16c = 0;
    local_180 = "enabled";
    local_170 = "filament_detected";
    extract_from_json(iVar3,&local_188,2,1);
    iVar18 = getodin();
    cVar1 = *(char *)(iVar18 + 0x26dc);
  }
  else {
    local_188.tv_sec = iVar18 + 0x26dc;
    local_178 = iVar18 + 0x26dd;
    local_188.tv_nsec = 2;
    local_174 = 2;
    local_180 = "enabled";
    local_170 = "filament_detected";
    local_17c = 0;
    local_16c = 0;
    extract_from_json(iVar3,&local_188,2,1);
    iVar3 = cJSON_GetObjectItem(uVar2,"filament_switch_sensor filament_sensor_2");
    if (iVar3 != 0) goto LAB_0049cf14;
    iVar18 = getodin();
    cVar1 = *(char *)(iVar18 + 0x26dc);
  }
  if (cVar1 != '\0') {
    local_188.tv_sec = 0xe;
    service_gui_request(0xd,&local_188,4);
  }
LAB_0049ce84:
  if (update_printstate != '\0') {
    sync_odin_to_printstate(0);
  }
  return 0;
}



// === cbGetServerFilesRoots @ 0049e260 ===

undefined4 cbGetServerFilesRoots(int param_1)

{
  uint uVar1;
  uint uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  
  iVar11 = *(int *)(param_1 + 4);
  if (((iVar11 != 0) && (iVar5 = cJSON_IsArray(iVar11), iVar5 != 0)) &&
     (iVar5 = cJSON_GetArraySize(iVar11), uVar2 = DAT_005955a0, 0 < iVar5)) {
    iVar10 = 0;
    do {
      iVar6 = cJSON_GetArrayItem(iVar11,iVar10);
      iVar10 = iVar10 + 1;
      if (((iVar6 != 0) && (iVar7 = cJSON_GetObjectItem(iVar6,"name"), iVar7 != 0)) &&
         ((iVar7 = strcmp(*(char **)(iVar7 + 0x10),"udisk"), iVar7 == 0 &&
          (iVar6 = cJSON_GetObjectItem(iVar6,&DAT_00595e10), iVar6 != 0)))) {
        iVar7 = getodin();
        snprintf((char *)(iVar7 + 0x2c34),0x20,"%s",*(undefined4 *)(iVar6 + 0x10));
        iVar6 = getodin();
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
                   ,0x6a0,"cbGetServerFilesRoots","Odinx->udisk_mount_root=%s\n",iVar6 + 0x2c34);
        iVar6 = getodin();
        lv_ll_clear(iVar6 + 0x494);
        iVar6 = getodin();
        puVar8 = (uint *)lv_ll_ins_head(iVar6 + 0x494);
        uVar4 = DAT_005955a5;
        uVar3 = DAT_005955a4;
        *puVar8 = uVar2;
        *(undefined1 *)(puVar8 + 1) = uVar3;
        *(undefined1 *)((int)puVar8 + 5) = uVar4;
        iVar6 = getodin();
        uVar1 = iVar6 + 0x393U & 3;
        puVar8 = (uint *)((iVar6 + 0x393U) - uVar1);
        *puVar8 = *puVar8 & -1 << (uVar1 + 1) * 8 | uVar2 >> (3 - uVar1) * 8;
        uVar1 = iVar6 + 0x390U & 3;
        puVar8 = (uint *)((iVar6 + 0x390U) - uVar1);
        *puVar8 = *puVar8 & 0xffffffffU >> (4 - uVar1) * 8 | uVar2 << uVar1 * 8;
        *(undefined1 *)(iVar6 + 0x394) = uVar3;
        *(undefined1 *)(iVar6 + 0x395) = uVar4;
        iVar6 = getodin();
        uVar1 = iVar6 + 0x293U & 3;
        puVar8 = (uint *)((iVar6 + 0x293U) - uVar1);
        *puVar8 = *puVar8 & -1 << (uVar1 + 1) * 8 | uVar2 >> (3 - uVar1) * 8;
        uVar1 = iVar6 + 0x290U & 3;
        puVar8 = (uint *)((iVar6 + 0x290U) - uVar1);
        *puVar8 = *puVar8 & 0xffffffffU >> (4 - uVar1) * 8 | uVar2 << uVar1 * 8;
        *(undefined1 *)(iVar6 + 0x294) = uVar3;
        *(undefined1 *)(iVar6 + 0x295) = uVar4;
        uVar9 = getodin();
        iVar6 = getodin();
        gcode_file_query_init(uVar9,iVar6 + 0x2f30,&DAT_005955a0,&DAT_005955a0);
        iVar6 = getodin();
        req_gui_gcode_file_list(iVar6 + 0x2f30);
      }
    } while (iVar5 != iVar10);
    return 0;
  }
  return 0;
}



// === cgi_GetAccessOneShotToken @ 0049f424 ===

undefined4 cgi_GetAccessOneShotToken(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  
  iVar1 = find_cgi_cmd("access.oneshot_token");
  if ((iVar1 == 0) || (*(int *)(iVar1 + 0xc) == 0)) {
    return 1;
  }
  iVar3 = 0x1d;
  do {
    printf("retry_countdown: %d\n",iVar3);
    http_get(iVar1,param_1);
    iVar3 = iVar3 + -1;
    if (*param_1 != '\0') {
      pcVar4 = "fetched ws-mid token\n";
      uVar2 = 0x3f5;
      goto LAB_0049f4c8;
    }
    sleep(1);
  } while (iVar3 != -1);
  pcVar4 = "fetch ws-mid token failed\n";
  uVar2 = 0x3fa;
LAB_0049f4c8:
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/cgi_cmd.c"
             ,uVar2,"cgi_GetAccessOneShotToken",pcVar4);
  return 0;
}



// === check_keyboard @ 004a18cc ===

void check_keyboard(void)

{
  FILE *__stream;
  char *pcVar1;
  int iVar2;
  char local_128 [256];
  undefined4 local_28 [2];
  
  __stream = fopen("/proc/bus/input/devices","r");
  if (__stream == (FILE *)0x0) {
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_factory_machine_sn.c"
               ,0x1a6,"check_keyboard","cant open /proc/bus/input/devices");
    return;
  }
  local_28[0] = 0xffffffff;
  iVar2 = 0;
  do {
    while( true ) {
      pcVar1 = fgets(local_128,0x100,__stream);
      if (pcVar1 == (char *)0x0) goto LAB_004a199c;
      if (local_128[0] == '\n') break;
      pcVar1 = strstr(local_128,"Name=");
      if ((pcVar1 == (char *)0x0) ||
         (pcVar1 = strstr(local_128,"Newtologic"), pcVar1 == (char *)0x0)) {
        if (iVar2 != 0) {
          pcVar1 = strstr(local_128,"Handlers");
          if (pcVar1 != (char *)0x0) {
            pcVar1 = strstr(local_128,"event");
            if (pcVar1 != (char *)0x0) {
              __isoc99_sscanf(pcVar1,"event%d",local_28);
              snprintf(keyboard_event_dev,0x20,"/dev/input/event%d",local_28[0]);
            }
          }
        }
      }
      else {
        iVar2 = 1;
      }
    }
  } while (iVar2 == 0);
LAB_004a199c:
  fclose(__stream);
  scannerStatus = iVar2;
  return;
}



// === udisk_list_update_observer_cb @ 004a2c30 ===

void udisk_list_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  iVar1 = lv_observer_get_target();
  if (*(int *)(iVar1 + 0x5c) == 4) {
    iVar2 = getodin();
    iVar5 = *(int *)(iVar1 + 0x34);
    if ((*(int *)(iVar2 + 0x3208) < 1) || (iVar5 == 0)) {
      lv_label_set_text(iVar5,&DAT_00612b84);
    }
    else {
      iVar2 = getodin();
      lv_label_set_text_fmt(iVar5,&DAT_00612b6c,*(undefined4 *)(iVar2 + 0x3208));
    }
    iVar2 = getodin();
    if (*(int *)(iVar2 + 0x3208) < 1) {
      uVar3 = lv_obj_get_parent(*(undefined4 *)(iVar1 + 0x38));
      lv_obj_add_flag(uVar3,1);
      return;
    }
    iVar2 = 0x320c;
    uVar3 = lv_obj_get_parent(*(undefined4 *)(iVar1 + 0x38));
    lv_obj_remove_flag(uVar3,1);
    lv_obj_clean(*(undefined4 *)(iVar1 + 0x38));
    for (iVar5 = 0; iVar4 = getodin(), iVar5 < *(int *)(iVar4 + 0x3208); iVar5 = iVar5 + 1) {
      iVar4 = getodin();
      if (iVar4 + iVar2 != 0) {
        uVar6 = *(undefined4 *)(iVar1 + 0x38);
        iVar4 = getodin();
        uVar3 = getcxfont(5);
        create_label(uVar6,iVar4 + iVar2,0,uVar3);
      }
      iVar2 = iVar2 + 0x20;
    }
  }
  return;
}



// === update_file_common_data_pointer @ 004a5b4c ===

void update_file_common_data_pointer(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0xd0) == '\0') {
    iVar1 = getodin();
    *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(iVar1 + 0x31b4);
    iVar1 = getodin();
    iVar2 = *(int *)(iVar1 + 0x31b0);
    iVar1 = getodin();
    *(int *)(param_1 + 0xdc) = iVar2 - *(int *)(iVar1 + 0x31b4);
    iVar1 = getodin();
    *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(iVar1 + 0x31b0);
    iVar1 = getodin();
    *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(iVar1 + 0x4d0);
    iVar1 = getodin();
    *(int *)(param_1 + 0xe8) = iVar1 + 0x494;
    iVar1 = getodin();
    *(int *)(param_1 + 0xec) = iVar1 + 0x390;
    iVar1 = getodin();
    *(int *)(param_1 + 0xf0) = iVar1 + 0x290;
    *(undefined4 **)(param_1 + 0xf4) = &DAT_005955a0;
    iVar1 = getodin();
    *(int *)(param_1 + 0xf8) = iVar1 + 0x31b8;
    iVar1 = getodin();
    *(int *)(param_1 + 0xfc) = iVar1 + 0x2c34;
    iVar1 = getodin();
    *(int *)(param_1 + 0x100) = iVar1 + 0x2a50;
    iVar1 = getodin();
    *(int *)(param_1 + 0x104) = iVar1 + 0x2f30;
    iVar1 = getodin();
    *(int *)(param_1 + 0x124) = iVar1 + 0x36f4;
    return;
  }
  iVar1 = getodin();
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(iVar1 + 0x2f24);
  iVar1 = getodin();
  iVar2 = *(int *)(iVar1 + 0x2f20);
  iVar1 = getodin();
  *(int *)(param_1 + 0xdc) = iVar2 - *(int *)(iVar1 + 0x2f24);
  iVar1 = getodin();
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(iVar1 + 0x2f20);
  iVar1 = getodin();
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(iVar1 + 0x4cc);
  iVar1 = getodin();
  *(int *)(param_1 + 0xe8) = iVar1 + 0x284;
  iVar1 = getodin();
  *(int *)(param_1 + 0xec) = iVar1 + 0x181;
  iVar1 = getodin();
  *(int *)(param_1 + 0xf0) = iVar1 + 0x81;
  *(char **)(param_1 + 0xf4) = "gcodes";
  iVar1 = getodin();
  *(int *)(param_1 + 0xf8) = iVar1 + 0x2f28;
  *(char **)(param_1 + 0xfc) = "/usr/data/printer_data/gcodes";
  iVar1 = getodin();
  *(int *)(param_1 + 0x100) = iVar1 + 0x2a30;
  iVar1 = getodin();
  *(int *)(param_1 + 0x104) = iVar1 + 0x2ca0;
  iVar1 = getodin();
  *(int *)(param_1 + 0x124) = iVar1 + 0x36dc;
  return;
}



// === update_sort_icon_style @ 004a6020 ===

void update_sort_icon_style(int param_1)

{
  char cVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [2];
  
  piVar2 = (int *)(param_1 + 0x9c);
  do {
    if (*piVar2 != 0) {
      lv_label_set_text(*piVar2,&DAT_00613288);
      iVar4 = *piVar2;
      lv_color_white(local_20);
      lv_obj_set_style_text_color(iVar4,local_20[0],0);
    }
    piVar2 = piVar2 + 3;
  } while (piVar2 != (int *)(param_1 + 0xc0));
  cVar1 = **(char **)(param_1 + 0xf8);
  if (cVar1 == '\x01') {
    lv_label_set_text(*(undefined4 *)(param_1 + 0x9c),&DAT_0061328c);
    uVar3 = *(undefined4 *)(param_1 + 0x9c);
    lv_color_make(&local_28,0x17,0xcc,0x5f);
    lv_obj_set_style_text_color(uVar3,local_28,0);
    return;
  }
  if (cVar1 == '\0') {
    lv_label_set_text(*(undefined4 *)(param_1 + 0x9c),&DAT_00613288);
    uVar3 = *(undefined4 *)(param_1 + 0x9c);
    lv_color_make(&local_24,0x17,0xcc,0x5f);
    lv_obj_set_style_text_color(uVar3,local_24,0);
    return;
  }
  if (cVar1 != '\x02') {
    if (cVar1 == '\x03') {
      lv_label_set_text(*(undefined4 *)(param_1 + 0xa8),&DAT_0061328c);
      uVar3 = *(undefined4 *)(param_1 + 0xa8);
      lv_color_make(&local_30,0x17,0xcc,0x5f);
      lv_obj_set_style_text_color(uVar3,local_30,0);
      return;
    }
    return;
  }
  lv_label_set_text(*(undefined4 *)(param_1 + 0xa8),&DAT_00613288);
  uVar3 = *(undefined4 *)(param_1 + 0xa8);
  lv_color_make(&local_2c,0x17,0xcc,0x5f);
  lv_obj_set_style_text_color(uVar3,local_2c,0);
  return;
}



// === start_print_verify_stop_print_cb @ 004a6220 ===

void start_print_verify_stop_print_cb(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_event_get_user_data();
  iVar2 = *(int *)(iVar1 + 0x2c);
  widget_alert_close(iVar1);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x10c) = 0;
  }
  return;
}



// === start_print_verify_continue_print_cb @ 004a6708 ===

void start_print_verify_continue_print_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = lv_event_get_user_data();
  if (*(int *)(iVar1 + 0x2c) != 0) {
    *(undefined4 *)(*(int *)(iVar1 + 0x2c) + 0x10c) = 0;
    iVar2 = getodin();
    uVar3 = *(undefined4 *)(iVar1 + 0x2c);
    *(undefined1 *)(iVar2 + 0x2760) = 1;
    start_print_handler(uVar3);
    return;
  }
  return;
}



// === update_thumb_src.isra.0 @ 004a7b68 ===

void update_thumb_src_isra_0(int param_1,char *param_2,int param_3)

{
  size_t sVar1;
  int iVar2;
  char *__s2;
  undefined4 uVar3;
  undefined4 *puVar4;
  char *__s1;
  char acStack_218 [2];
  char acStack_216 [510];
  
  if ((param_1 == 0) || (*(int *)(param_1 + 0x5c) == 0)) {
    return;
  }
  if (1 < param_3) {
    if (param_2 == (char *)0x0) {
      return;
    }
    sVar1 = strnlen(param_2,0x200);
    if (0x1fd < sVar1 - 1) {
      return;
    }
    if (*param_2 != '\0') {
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_files_common.c"
                 ,0x30f,"update_thumb_src","pthumb->relative_path=%s",param_2);
      memset(acStack_218,0,0x200);
      if (*(char *)(param_1 + 0xd0) == '\0') {
        snprintf(acStack_218,0x200,"A:%s",param_2);
      }
      else {
        iVar2 = lv_malloc_zeroed(0x200);
        if (iVar2 != 0) {
          puVar4 = *(undefined4 **)(param_1 + 0xe8);
          get_sub_full_path_util(iVar2,*puVar4,puVar4[1],puVar4[2]);
          snprintf(acStack_218,0x200,"A:%s/%s%s",*(undefined4 *)(param_1 + 0xfc),iVar2,param_2);
          lv_free(iVar2);
        }
      }
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_files_common.c"
                 ,800,"update_thumb_src","img_thumb_path_in_files_common=%s",acStack_218);
      iVar2 = access(acStack_216,0);
      if (iVar2 == 0) {
        *(char **)(param_1 + 0x30) = acStack_218;
        lv_image_set_src(*(undefined4 *)(param_1 + 0x5c),acStack_218);
        return;
      }
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_files_common.c"
                 ,0x324,"update_thumb_src","===This path cannot be accessed=====%s\n",acStack_216);
      __s1 = *(char **)(param_1 + 0x30);
      goto LAB_004a7cc4;
    }
  }
  __s1 = *(char **)(param_1 + 0x30);
LAB_004a7cc4:
  __s2 = (char *)pack_res_full_path("pictures/file_default.png",1);
  iVar2 = strcmp(__s1,__s2);
  if (iVar2 != 0) {
    uVar3 = pack_res_full_path("pictures/file_default.png",1);
    *(undefined4 *)(param_1 + 0x30) = uVar3;
    lv_image_set_src(*(undefined4 *)(param_1 + 0x5c),uVar3);
  }
  return;
}



// === selftest_send_update_observer_cb @ 004af700 ===

void selftest_send_update_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  char local_20 [16];
  
  iVar1 = lv_subject_get_int(param_2);
  if (iVar1 != 0) {
    iVar2 = lv_observer_get_target(param_1);
    iVar2 = *(int *)(iVar2 + 0x2c);
    if ((iVar2 != 0) && (*(char *)(iVar2 + 0x52) != '\0')) {
      if (iVar1 == 1) {
        klipper_ready_wait_timer_del(iVar2);
        *(undefined1 *)(iVar2 + 0x52) = 0;
        iVar1 = getodin();
        *(undefined4 *)(iVar1 + 0x1ee8) = 1;
        uVar4 = ws_run_cmd("cx_printer_gcode_script",0,"%s",s_INPUT_SHAPER_K_K_006d2484);
        ws_reqcb_cache_add(uVar4,PTR_selftest_guide_item_cb_006d24c4,&DAT_006d24cc,0x5dc);
      }
      else if (iVar1 == 2) {
        klipper_ready_wait_timer_del(iVar2);
        *(undefined1 *)(iVar2 + 0x52) = 0;
        *(undefined1 *)(*(int *)(iVar2 + 0x44) + 0x1a2) = 0;
        local_20[0] = '\0';
        local_20[1] = '\0';
        local_20[2] = '\0';
        local_20[3] = '\0';
        local_20[4] = '\0';
        local_20[5] = '\0';
        local_20[6] = '\0';
        local_20[7] = '\0';
        local_20[8] = '\0';
        local_20[9] = '\0';
        strncpy(local_20,guide_selftest_step_error + 0x28,9);
        sVar3 = strlen(local_20);
        service_gui_request(0xf,local_20,sVar3 + 1);
        *(undefined1 *)(*(int *)(iVar2 + 0x44) + 0x1a0) = 1;
        *(undefined4 *)(iVar2 + 0x40) = 5;
        page_dev_selftest_draw_items(iVar2);
      }
    }
  }
  return;
}



// === home_temperature_update_callback @ 004b099c ===

void home_temperature_update_callback(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = *(int *)(param_1 + 0xc);
  iVar1 = getodin();
  dVar3 = *(double *)(*(int *)(iVar1 + 0x6c) + 0x638);
  lv_chart_set_next_value
            (*(undefined4 *)(iVar2 + 0x48),*(undefined4 *)(iVar2 + 0x50),
             (int)*(double *)(*(int *)(iVar1 + 0x68) + 0x638));
  lv_chart_set_next_value(*(undefined4 *)(iVar2 + 0x48),*(undefined4 *)(iVar2 + 0x4c),(int)dVar3);
  lv_chart_refresh(*(undefined4 *)(iVar2 + 0x48));
  return;
}



// === chart_temperature_update_observer_cb @ 004b0a6c ===

void chart_temperature_update_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double *pdVar4;
  double *pdVar5;
  double *pdVar6;
  double dVar7;
  
  iVar1 = lv_observer_get_target();
  iVar2 = lv_subject_get_int(param_2);
  iVar3 = getodin();
  if (iVar2 != 0) {
    pdVar4 = *(double **)(iVar3 + 0x6c);
    pdVar5 = *(double **)(iVar3 + 0x68);
    pdVar6 = pdVar4 + 200;
    do {
      dVar7 = *pdVar4;
      pdVar4 = pdVar4 + 1;
      lv_chart_set_next_value
                (*(undefined4 *)(iVar1 + 0x48),*(undefined4 *)(iVar1 + 0x50),(int)*pdVar5);
      pdVar5 = pdVar5 + 1;
      lv_chart_set_next_value
                (*(undefined4 *)(iVar1 + 0x48),*(undefined4 *)(iVar1 + 0x4c),(int)dVar7);
    } while (pdVar4 != pdVar6);
    lv_chart_refresh(*(undefined4 *)(iVar1 + 0x48));
    return;
  }
  return;
}



// === fan_speed_update_observer_cb @ 004b0bb8 ===

void fan_speed_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  double dVar4;
  undefined4 local_28;
  undefined4 local_24 [2];
  undefined4 local_1c;
  
  local_1c = 0;
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  local_1c = 0;
  dVar4 = 0.0;
  if (*(double *)(iVar2 + 0x22a0) <= 0.0) {
    iVar2 = getodin();
    local_1c = 0;
    if (*(double *)(iVar2 + 0x22b0) <= dVar4) {
      iVar2 = getodin();
      local_1c = 0;
      if (*(double *)(iVar2 + 0x22c0) <= dVar4) {
        uVar3 = *(undefined4 *)(iVar1 + 0x414);
        lv_color_make(&local_28,0x83,0x86,0x8b);
        lv_obj_set_style_text_color(uVar3,local_28,0);
        lv_anim_delete(*(undefined4 *)(iVar1 + 0x414),fan_rotate_cb);
        local_1c = 0;
        lv_obj_set_style_transform_rotation(*(undefined4 *)(iVar1 + 0x414),100,0);
        return;
      }
    }
  }
  local_1c = 0;
  uVar3 = *(undefined4 *)(iVar1 + 0x414);
  lv_color_make(local_24,0x17,0xcc,0x5f);
  lv_obj_set_style_text_color(uVar3,local_24[0],0);
  local_1c = 0;
  lv_anim_start(iVar1 + 0x418);
  return;
}



// === fan_rotate_cb @ 004b0d54 ===

void fan_rotate_cb(undefined4 param_1,undefined4 param_2)

{
  lv_obj_set_local_style_prop(param_1,0x6e,param_2,0);
  return;
}



// === led_light_update_observer_cb @ 004b0d5c ===

void led_light_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  iVar2 = strcasecmp((char *)(iVar2 + 0x147c),"ENDER3V3Plus");
  if (iVar2 != 0) {
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x40c),1);
  }
  iVar2 = getodin();
  if (0 < *(int *)(iVar2 + 0x1528)) {
    lv_label_set_text(*(undefined4 *)(iVar1 + 0x410),&DAT_00613b50);
    uVar3 = *(undefined4 *)(iVar1 + 0x410);
    lv_color_make(&local_c,0x17,0xcc,0x5f);
    lv_obj_set_style_text_color(uVar3,local_c,0);
    return;
  }
  lv_label_set_text(*(undefined4 *)(iVar1 + 0x410),&DAT_00613b54);
  uVar3 = *(undefined4 *)(iVar1 + 0x410);
  lv_color_make(&local_10,0x83,0x86,0x8b);
  lv_obj_set_style_text_color(uVar3,local_10,0);
  return;
}



// === print_thumb_without_waterprogress_update @ 004b1fa8 ===

void print_thumb_without_waterprogress_update(int param_1)

{
  int iVar1;
  char *__s2;
  undefined4 uVar2;
  int iVar3;
  char *__s1;
  undefined1 *puVar4;
  undefined1 auStack_418 [512];
  char acStack_218 [516];
  
  iVar1 = getodin();
  __s1 = (char *)(param_1 + 0xb8);
  if ((((*(int *)(iVar1 + 0x664) < 2) || (iVar1 = getodin(), iVar1 == -0x654)) ||
      (*(char **)(iVar1 + 0x660) == (char *)0x0)) || (**(char **)(iVar1 + 0x660) == '\0')) {
    __s2 = (char *)pack_res_full_path("pictures/thumb_placeholder.png",1);
    iVar1 = strcmp(__s1,__s2);
    if ((iVar1 != 0) && (iVar1 = *(int *)(param_1 + 0x94), iVar1 != 0)) {
      uVar2 = pack_res_full_path("pictures/thumb_placeholder.png",1);
      lv_image_set_src(iVar1,uVar2);
      uVar2 = pack_res_full_path("pictures/thumb_placeholder.png",1);
      snprintf(__s1,0x200,"%s",uVar2);
    }
  }
  else {
    memset(acStack_218,0,0x200);
    puVar4 = auStack_418;
    iVar3 = getodin();
    get_directory_from_full_path(iVar3 + 0x678,puVar4);
    uVar2 = *(undefined4 *)(iVar1 + 0x660);
    snprintf(acStack_218,0x200,"A:%s/%s%s","/usr/data/printer_data/gcodes",puVar4,uVar2);
    iVar1 = strcmp(__s1,acStack_218);
    if ((iVar1 != 0) && (*(int *)(param_1 + 0x94) != 0)) {
      snprintf(__s1,0x200,"%s",acStack_218,puVar4,uVar2);
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_home.c"
                 ,0x4bd,"print_thumb_without_waterprogress_update","thumbnail src src = %s",__s1);
      lv_image_set_src(*(undefined4 *)(param_1 + 0x94),acStack_218);
    }
  }
  return;
}



// === current_print_info_update_observer_cb @ 004b2150 ===

/* WARNING: Removing unreachable block (ram,0x004b24ac) */
/* WARNING: Removing unreachable block (ram,0x004b237c) */
/* WARNING: Removing unreachable block (ram,0x004b230c) */
/* WARNING: Removing unreachable block (ram,0x004b2474) */
/* WARNING: Removing unreachable block (ram,0x004b22b8) */
/* WARNING: Removing unreachable block (ram,0x004b2458) */
/* WARNING: Removing unreachable block (ram,0x004b2484) */
/* WARNING: Removing unreachable block (ram,0x004b2360) */
/* WARNING: Removing unreachable block (ram,0x004b238c) */
/* WARNING: Removing unreachable block (ram,0x004b23c8) */

void current_print_info_update_observer_cb(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  double dVar5;
  double dVar6;
  char local_48 [12];
  char local_3c [16];
  undefined4 local_2c;
  
  local_2c = 0;
  iVar1 = lv_observer_get_target();
  uVar2 = get_printer_work_state();
  iVar3 = printer_is_working(uVar2);
  if (iVar3 != 0) {
    if (*(char *)(iVar1 + 0x2c0) == '\0') {
      uVar2 = *(undefined4 *)(iVar1 + 0xa0);
      iVar3 = getodin();
      lv_label_set_text(uVar2,iVar3 + 0x678);
      iVar3 = getodin();
      snprintf((char *)(iVar1 + 0x2c0),0x100,"%s",iVar3 + 0x678);
    }
    print_thumb_without_waterprogress_update(iVar1);
    uVar2 = *(undefined4 *)(iVar1 + 0x7c);
    iVar3 = getodin();
    local_2c = 0;
    dVar5 = 0.0;
    dVar6 = DAT_00613d68;
    lv_bar_set_value(uVar2,(int)(*(double *)(iVar3 + 0x888) * DAT_00613d68 + 0.0),1);
    uVar2 = *(undefined4 *)(iVar1 + 0x90);
    iVar3 = getodin();
    local_2c = 0;
    lv_label_set_text_fmt(uVar2,&DAT_00613bf0,(int)(*(double *)(iVar3 + 0x888) * dVar6 + dVar5));
    local_3c[0] = '\0';
    local_3c[1] = '\0';
    local_3c[2] = '\0';
    local_3c[3] = '\0';
    local_3c[4] = '\0';
    local_3c[5] = '\0';
    local_3c[6] = '\0';
    local_3c[7] = '\0';
    local_3c[8] = '\0';
    local_3c[9] = '\0';
    iVar3 = getodin();
    local_2c = 0;
    if ((int)*(double *)(iVar3 + 0x20b0) < 0xe10) {
      iVar3 = getodin();
      local_2c = 0;
      snprintf(local_3c,10,"%dm%02ds",(int)*(double *)(iVar3 + 0x20b0) / 0x3c,
               (int)*(double *)(iVar3 + 0x20b0) % 0x3c);
      uVar2 = *(undefined4 *)(iVar1 + 0xa4);
    }
    else {
      iVar3 = getodin();
      local_2c = 0;
      snprintf(local_3c,10,"%dh%02dm",(int)*(double *)(iVar3 + 0x20b0) / 0xe10,
               ((int)*(double *)(iVar3 + 0x20b0) / 0x3c) % 0x3c);
      uVar2 = *(undefined4 *)(iVar1 + 0xa4);
    }
    lv_label_set_text(uVar2,local_3c);
    lv_obj_update_layout(*(undefined4 *)(iVar1 + 0xa4));
    uVar2 = *(undefined4 *)(iVar1 + 0xa8);
    uVar4 = *(undefined4 *)(iVar1 + 0xa4);
    iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
    lv_obj_align_to(uVar2,uVar4,0x11,-iVar3 / 4,0);
    local_48[0] = '\0';
    local_48[1] = '\0';
    local_48[2] = '\0';
    local_48[3] = '\0';
    local_48[4] = '\0';
    local_48[5] = '\0';
    local_48[6] = '\0';
    local_48[7] = '\0';
    local_48[8] = '\0';
    local_48[9] = '\0';
    iVar3 = getodin();
    if (*(int *)(iVar3 + 0x894) < 0xe10) {
      iVar3 = getodin();
      snprintf(local_48,10,"%dm%02ds",*(int *)(iVar3 + 0x894) / 0x3c,*(int *)(iVar3 + 0x894) % 0x3c)
      ;
      uVar2 = *(undefined4 *)(iVar1 + 0xac);
    }
    else {
      iVar3 = getodin();
      snprintf(local_48,10,"%dh%02dm",*(int *)(iVar3 + 0x894) / 0xe10,
               (*(int *)(iVar3 + 0x894) / 0x3c) % 0x3c);
      uVar2 = *(undefined4 *)(iVar1 + 0xac);
    }
    lv_label_set_text(uVar2,local_48);
    lv_obj_update_layout(*(undefined4 *)(iVar1 + 0xac));
    uVar4 = *(undefined4 *)(iVar1 + 0xb0);
    uVar2 = *(undefined4 *)(iVar1 + 0xac);
    iVar1 = lv_font_get_line_height(lv_font_montserrat_14);
    lv_obj_align_to(uVar4,uVar2,0x11,-iVar1 / 4,0);
  }
  return;
}



// === confirm_ota_start_reself_test_cb @ 004b34a0 ===

void confirm_ota_start_reself_test_cb(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = lv_event_get_code();
  uVar2 = lv_event_get_user_data(param_1);
  if (iVar1 != 10) {
    return;
  }
  widget_alert_close(uVar2);
  iVar1 = page_obj_pop(1);
  uVar2 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x34),3);
  lv_obj_send_event(uVar2,10,iVar1);
  iVar1 = page_obj_pop(0xe);
  lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x2c),1);
  page_settings_system_selfcheck_create(iVar1);
  return;
}



// === exclude_object_update_observer_cb @ 004b3534 ===

void exclude_object_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40 [2];
  uint local_38;
  int local_34;
  undefined *local_30;
  int local_2c;
  
  iVar1 = lv_observer_get_target();
  local_2c = iVar1;
  iVar2 = getodin();
  if (0 < *(int *)(iVar2 + 0x26c0)) {
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x60),1);
    iVar1 = page_obj_pop(2);
    iVar2 = getodin();
    iVar7 = *(int *)(iVar2 + 0x26c0);
    iVar2 = lv_obj_get_child_count(*(undefined4 *)(iVar1 + 0x6c));
    if (iVar2 == iVar7) {
      iVar2 = 0;
      if (0 < iVar7) {
        do {
          while( true ) {
            iVar3 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x6c),iVar2);
            if (iVar3 == 0) goto LAB_004b362c;
            iVar4 = getodin();
            if (*(int *)(iVar2 * 0x120 + *(int *)(iVar4 + 0x26bc) + 0x118) == 2) {
              set_exclude_checkbox_status(iVar3,0x80);
              iVar4 = getodin();
              *(undefined1 *)(iVar4 + iVar2 + 0x25b8) = 0;
            }
            iVar4 = getodin();
            iVar4 = iVar4 + iVar2;
            iVar2 = iVar2 + 1;
            if (*(char *)(iVar4 + 0x25b8) == '\0') break;
            set_exclude_checkbox_status(iVar3,0x1000);
            if (iVar7 == iVar2) goto LAB_004b362c;
          }
        } while (iVar7 != iVar2);
      }
    }
    else {
      lv_obj_clean(*(undefined4 *)(iVar1 + 0x6c));
      lv_obj_update_layout(*(undefined4 *)(iVar1 + 0x6c));
      lv_obj_get_width(*(undefined4 *)(iVar1 + 0x6c));
      uVar5 = getcxfont(5);
      iVar2 = lv_font_get_line_height(uVar5);
      if (iVar7 != 0) {
        local_30 = &DAT_005e0000;
        iVar3 = 0;
        local_34 = 0x4b0000;
        do {
          iVar4 = getodin();
          iVar8 = *(int *)(*(int *)(iVar4 + 0x26bc) + iVar3 * 0x120 + 0x118);
          uVar5 = lv_checkbox_create(*(undefined4 *)(iVar1 + 0x6c));
          lv_obj_set_size(uVar5,0x20000064,iVar2 + 4);
          lv_obj_set_style_base_dir(uVar5,1,0);
          lv_checkbox_set_text(uVar5,local_30 + 0x5bec);
          uVar6 = getcxfont(5);
          lv_obj_set_style_text_font(uVar5,uVar6,0);
          lv_obj_set_style_transform_width(uVar5,0,0x20020);
          lv_obj_set_style_transform_height(uVar5,0,0x20020);
          lv_obj_set_style_radius(uVar5,2,0x20000);
          lv_color_make(local_40,0x88,0x89,0x89);
          lv_obj_set_style_border_color(uVar5,local_40[0],0x20000);
          lv_obj_set_style_border_opa(uVar5,0xff,0x20000);
          lv_obj_set_style_bg_opa(uVar5,0,0x20000);
          lv_color_make(&local_44,0x17,0xcc,0x5f);
          lv_obj_set_style_bg_color(uVar5,local_44,0x20001);
          lv_obj_set_style_bg_opa(uVar5,0xff,0x20001);
          lv_color_make(&local_48,0x17,0xcc,0x5f);
          lv_obj_set_style_border_color(uVar5,local_48,0x20001);
          lv_obj_set_style_border_width(uVar5,0,0x20080);
          iVar4 = getodin();
          iVar4 = *(int *)(iVar4 + 0x26bc);
          uVar6 = getcxfont(5);
          uVar6 = create_label(uVar5,iVar4 + iVar3 * 0x120 + 0x10,0,uVar6);
          lv_obj_align(uVar6,7,0,0);
          lv_obj_set_size(uVar6,0x20000055,iVar2 + 4);
          lv_color_white(&local_4c);
          lv_obj_set_style_text_color(uVar6,local_4c,0);
          lv_color_make(&local_50,0x17,0xcc,0x5f);
          lv_obj_set_style_text_color(uVar6,local_50,1);
          local_38 = 0x750000;
          lv_color_hex(&local_54,0x75767b);
          lv_obj_set_style_text_color(uVar6,local_54,0x80);
          lv_color_hex(&local_58,local_38 | 0x767b);
          lv_obj_set_style_text_color(uVar6,local_58,0x1000);
          lv_label_set_long_mode(uVar6,1);
          if (iVar8 == 2) {
            set_exclude_checkbox_status(uVar5,0x80);
          }
          iVar4 = getodin();
          if (*(char *)(iVar4 + iVar3 + 0x25b8) != '\0') {
            set_exclude_checkbox_status(uVar5,0x1000);
          }
          iVar3 = iVar3 + 1;
          lv_obj_add_event_cb(uVar5,local_34 + 0x1598,0x23,0);
        } while (iVar7 != iVar3);
      }
    }
LAB_004b362c:
    iVar1 = local_2c;
    uVar5 = page_home_refresh_polygon(*(undefined4 *)(local_2c + 0x5c));
    *(undefined4 *)(iVar1 + 100) = uVar5;
  }
  return;
}



// === remote_close_errcode_update_observer_cb @ 004b66f4 ===

void remote_close_errcode_update_observer_cb(void)

{
  int iVar1;
  
  iVar1 = lv_observer_get_target();
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x2c24) != 0)) {
    widget_alert_close();
    *(undefined4 *)(iVar1 + 0x2c24) = 0;
  }
  remote_close_errcode();
  return;
}



// === powerloss_continue_info_update_observer_cb @ 004b6734 ===

void powerloss_continue_info_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = lv_observer_get_target();
  iVar2 = page_obj_pop(0);
  if (*(int *)(iVar2 + 0x278c) == 1) {
    if (*(int *)(iVar1 + 0x2c28) == 0) {
      local_20 = lv_i18n_get_text("ContinuePrint");
      local_1c = 0;
      local_18 = lv_i18n_get_text("Cancel");
      uVar3 = lv_i18n_get_text("WarmRemind");
      uVar4 = lv_i18n_get_text("PowerLossContinueMsg");
      uVar3 = widget_alert_create(0,uVar3,uVar4,&local_20,iVar1);
      *(undefined4 *)(iVar1 + 0x2c28) = uVar3;
      uVar4 = lv_pct(0x3c);
      uVar5 = lv_pct(0x32);
      lv_obj_set_size(uVar3,uVar4,uVar5);
      widget_alert_add_cancel_event_cb(*(undefined4 *)(iVar1 + 0x2c28),powerloss_continue_cancel_cb)
      ;
      widget_alert_add_confirm_event_cb
                (*(undefined4 *)(iVar1 + 0x2c28),powerloss_continue_confirm_cb);
    }
  }
  else if (*(int *)(iVar1 + 0x2c28) != 0) {
    widget_alert_close();
    *(undefined4 *)(iVar1 + 0x2c28) = 0;
  }
  return;
}



// === material_detect_info_update_observer_cb @ 004b6970 ===

void material_detect_info_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = lv_observer_get_target();
  iVar2 = page_obj_pop(1);
  iVar3 = page_obj_pop(0);
  if (((*(char *)(iVar3 + 0x26dd) == '\0') ||
      ((iVar3 = page_obj_pop(0), *(char *)(iVar3 + 0x26df) == '\0' &&
       (iVar3 = page_obj_pop(0), *(char *)(iVar3 + 0x26de) != '\0')))) &&
     (iVar3 = page_obj_pop(0), *(char *)(iVar3 + 0x26dc) != '\0')) {
    if (iVar2 != 0) {
      lv_obj_remove_flag(*(undefined4 *)(iVar2 + 100),1);
    }
  }
  else if (iVar2 != 0) {
    lv_obj_add_flag(*(undefined4 *)(iVar2 + 100),1);
  }
  iVar2 = page_obj_pop(0);
  lv_subject_set_int(iVar2 + 0x2b10,1);
  iVar2 = page_obj_pop(0);
  if (*(char *)(iVar2 + 0x26dc) != '\0') {
    uVar4 = get_printer_work_state();
    iVar2 = printer_is_working(uVar4);
    if (iVar2 != 0) {
      iVar2 = page_obj_pop(0);
      if ((*(char *)(iVar2 + 0x26dd) == '\0') ||
         ((iVar2 = page_obj_pop(0), *(char *)(iVar2 + 0x26df) == '\0' &&
          (iVar2 = page_obj_pop(0), *(char *)(iVar2 + 0x26de) != '\0')))) {
        iVar2 = get_printer_work_state();
        if ((iVar2 == 9) && (iVar2 = page_obj_pop(0), *(int *)(iVar2 + 0x2718) == 1)) {
          lv_log_add(2,4,
                     "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_odin.c"
                     ,0x200,"material_detect_info_update_observer_cb","AI_DETECT material runout");
          iVar2 = page_obj_pop(0);
          iVar3 = page_obj_pop(0);
          print_operation(6,iVar2 + 0x678,*(undefined4 *)(iVar3 + 0xbb4));
        }
        iVar2 = page_obj_pop(0);
        if (*(char *)(iVar2 + 0x2760) == '\0') {
          if (*(int *)(iVar1 + 0x2c24) == 0) {
            local_20 = lv_i18n_get_text("ToChangeFilament");
            local_1c = 0;
            local_18 = lv_i18n_get_text("Forget");
            uVar4 = lv_i18n_get_text("WarmRemind");
            uVar6 = lv_i18n_get_text("FilamentRunOutMsg");
            uVar4 = widget_alert_create(0,uVar4,uVar6,&local_20,iVar1);
            *(undefined4 *)(iVar1 + 0x2c24) = uVar4;
            iVar2 = lv_pct(0x3c);
            uVar6 = lv_pct(0x32);
            lv_obj_set_size(uVar4,iVar2 + 5,uVar6);
            uVar4 = *(undefined4 *)(iVar1 + 0x2c24);
          }
          else {
            uVar6 = *(undefined4 *)(*(int *)(iVar1 + 0x2c24) + 0x38);
            uVar4 = lv_i18n_get_text("FilamentRunOutMsg");
            lv_label_set_text(uVar6,uVar4);
            uVar4 = lv_obj_get_child(*(undefined4 *)(*(int *)(iVar1 + 0x2c24) + 0x4c),0xffffffff);
            uVar6 = lv_obj_get_child(*(undefined4 *)(*(int *)(iVar1 + 0x2c24) + 0x44),0xffffffff);
            uVar5 = lv_i18n_get_text("Forget");
            lv_label_set_text(uVar4,uVar5);
            uVar4 = lv_i18n_get_text("ToChangeFilament");
            lv_label_set_text(uVar6,uVar4);
            uVar4 = *(undefined4 *)(iVar1 + 0x2c24);
          }
          widget_alert_add_cancel_event_cb(uVar4,material_detect_runout_cancel_cb);
          widget_alert_add_confirm_event_cb
                    (*(undefined4 *)(iVar1 + 0x2c24),material_detect_runout_confirm_cb);
          iVar1 = page_obj_pop(0);
          *(undefined1 *)(iVar1 + 0x2760) = 1;
          update_errcode_to_slicer("TR0116");
        }
      }
      else {
        iVar1 = page_obj_pop(0);
        *(undefined1 *)(iVar1 + 0x2760) = 0;
      }
    }
  }
  return;
}



// === page_reboot_timeout_close_timer_callback @ 004b6e14 ===

void page_reboot_timeout_close_timer_callback(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = page_obj_pop(0);
  if (*(int *)(iVar1 + 0x36d4) != 0) {
    iVar1 = page_obj_pop(0);
    lv_timer_delete(*(undefined4 *)(iVar1 + 0x36d4));
  }
  iVar1 = page_obj_pop(0);
  iVar2 = *(int *)(param_1 + 0xc);
  *(undefined4 *)(iVar1 + 0x36d4) = 0;
  if (*(int *)(iVar2 + 0x2c) != 0) {
    lv_obj_delete();
    *(undefined4 *)(iVar2 + 0x2c) = 0;
  }
  iVar1 = page_obj_pop(0);
  *(undefined1 *)(iVar1 + 0x36c6) = 0;
  return;
}



// === remote_control_update_observer_cb @ 004b817c ===

void remote_control_update_observer_cb(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  uVar1 = lv_observer_get_target();
  iVar2 = lv_subject_get_int(param_2);
  iVar3 = page_obj_pop(0);
  if ((*(char *)(iVar3 + 0x2bb0) == '\0') && (iVar2 != 0)) {
    iVar2 = page_obj_pop(0);
    *(undefined1 *)(iVar2 + 0x2bb0) = 1;
    local_20 = 0;
    local_1c = 0;
    local_18 = lv_i18n_get_text(&DAT_005a0230);
    uVar4 = lv_i18n_get_text("RemoteControlling");
    iVar2 = widget_alert_create(0,uVar4,0,&local_20,uVar1);
    uVar1 = lv_pct(0x3c);
    lv_obj_set_size(iVar2,uVar1,0x20000050);
    uVar1 = create_remote_control_info(iVar2);
    widget_alert_attach_body(iVar2,uVar1);
    uVar5 = *(undefined4 *)(iVar2 + 0x3c);
    uVar1 = lv_pct(100);
    uVar4 = lv_pct(0x46);
    lv_obj_set_size(uVar5,uVar1,uVar4);
    widget_alert_add_cancel_event_cb(iVar2,cancel_remote_control_exit_cb);
    return;
  }
  return;
}



// === update_access_state_by_workstate @ 004bb58c ===

void update_access_state_by_workstate(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = get_printer_work_state();
  iVar2 = printer_is_working(uVar1);
  if (iVar2 == 0) {
    iVar2 = getodin();
    *(undefined4 *)(iVar2 + 0x2714) = 0;
  }
  else {
    iVar2 = get_printer_work_state();
    if ((((iVar2 == 9) || (iVar2 = get_printer_work_state(), iVar2 == 1)) ||
        (iVar2 = get_printer_work_state(), iVar2 == 7)) ||
       (iVar2 = get_printer_work_state(), iVar2 == 8)) {
      iVar2 = getodin();
      *(undefined4 *)(iVar2 + 0x2714) = 3;
    }
    iVar2 = get_printer_work_state();
    if ((iVar2 == 6) || (iVar2 = get_printer_work_state(), iVar2 == 5)) {
      iVar2 = getodin();
      *(undefined4 *)(iVar2 + 0x2714) = 4;
      return;
    }
  }
  return;
}



// === pre_print_material_runout_verify @ 004bb670 ===

char pre_print_material_runout_verify(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = getodin();
  cVar1 = *(char *)(iVar2 + 0x26dc);
  if (cVar1 != '\0') {
    iVar2 = getodin();
    if (*(char *)(iVar2 + 0x26dd) == '\0') {
      return cVar1;
    }
    iVar2 = getodin();
    if (*(char *)(iVar2 + 0x26df) == '\0') {
      iVar2 = getodin();
      return *(char *)(iVar2 + 0x26de);
    }
  }
  return '\0';
}



// === check_upgrade_result @ 004bb7a8 ===

undefined4 check_upgrade_result(void)

{
  int iVar1;
  FILE *__stream;
  char *pcVar2;
  size_t sVar3;
  undefined4 uVar4;
  char local_180 [256];
  char local_80 [32];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  char local_40 [32];
  
  iVar1 = access("/usr/data/upgrade/upgresult",0);
  if (iVar1 == 0) {
    __stream = fopen("/usr/data/upgrade/upgresult","r");
    if (__stream == (FILE *)0x0) {
      uVar4 = 0xffffffff;
    }
    else {
      local_180[0] = '\0';
      local_180[1] = '\0';
      local_180[2] = '\0';
      local_180[3] = '\0';
      memset(local_180 + 4,0,0xfc);
      local_40[0] = '\0';
      local_40[1] = '\0';
      local_40[2] = '\0';
      local_40[3] = '\0';
      local_40[4] = '\0';
      local_40[5] = '\0';
      local_40[6] = '\0';
      local_40[7] = '\0';
      local_40[8] = '\0';
      local_40[9] = '\0';
      local_40[10] = '\0';
      local_40[0xb] = '\0';
      local_40[0xc] = '\0';
      local_40[0xd] = '\0';
      local_40[0xe] = '\0';
      local_40[0xf] = '\0';
      local_40[0x10] = '\0';
      local_40[0x11] = '\0';
      local_40[0x12] = '\0';
      local_40[0x13] = '\0';
      local_40[0x14] = '\0';
      local_40[0x15] = '\0';
      local_40[0x16] = '\0';
      local_40[0x17] = '\0';
      local_40[0x18] = '\0';
      local_40[0x19] = '\0';
      local_40[0x1a] = '\0';
      local_40[0x1b] = '\0';
      local_40[0x1c] = '\0';
      local_40[0x1d] = '\0';
      local_40[0x1e] = '\0';
      local_40[0x1f] = '\0';
      local_60 = 0;
      local_5c = 0;
      local_58 = 0;
      local_54 = 0;
      local_50 = 0;
      local_4c = 0;
      local_48 = 0;
      local_44 = 0;
      local_80[0] = '\0';
      local_80[1] = '\0';
      local_80[2] = '\0';
      local_80[3] = '\0';
      local_80[4] = '\0';
      local_80[5] = '\0';
      local_80[6] = '\0';
      local_80[7] = '\0';
      local_80[8] = '\0';
      local_80[9] = '\0';
      local_80[10] = '\0';
      local_80[0xb] = '\0';
      local_80[0xc] = '\0';
      local_80[0xd] = '\0';
      local_80[0xe] = '\0';
      local_80[0xf] = '\0';
      local_80[0x10] = '\0';
      local_80[0x11] = '\0';
      local_80[0x12] = '\0';
      local_80[0x13] = '\0';
      local_80[0x14] = '\0';
      local_80[0x15] = '\0';
      local_80[0x16] = '\0';
      local_80[0x17] = '\0';
      local_80[0x18] = '\0';
      local_80[0x19] = '\0';
      local_80[0x1a] = '\0';
      local_80[0x1b] = '\0';
      local_80[0x1c] = '\0';
      local_80[0x1d] = '\0';
      local_80[0x1e] = '\0';
      local_80[0x1f] = '\0';
      while( true ) {
        pcVar2 = fgets(local_180,0x100,__stream);
        if (pcVar2 == (char *)0x0) break;
        iVar1 = strncmp(local_180,"upgresult:",10);
        if (iVar1 == 0) {
          __isoc99_sscanf(local_180,"upgresult: %31s",local_40);
        }
        else {
          iVar1 = strncmp(local_180,"upgdate:",8);
          if (iVar1 == 0) {
            __isoc99_sscanf(local_180,"upgdate: %31s",&local_60);
          }
        }
      }
      fclose(__stream);
      iVar1 = strcmp(local_40,"succeed");
      if (iVar1 == 0) {
        strncpy(local_80,"UpgradeSuccess",0x20);
      }
      else {
        iVar1 = strcmp(local_40,"failed");
        if (iVar1 == 0) {
          strncpy(local_80,"SystemUpgradeFailed",0x20);
        }
        else {
          iVar1 = strcmp(local_40,"file_inexistence");
          if (iVar1 != 0) {
            remove("/usr/data/upgrade/upgresult");
            return 0xffffffff;
          }
          strncpy(local_80,"UpgradeFileNotExist",0x20);
        }
      }
      sVar3 = strlen(local_80);
      service_gui_request(0x1c,local_80,sVar3 + 1);
      remove("/usr/data/upgrade/upgresult");
      DAT_0084c8d0 = 4;
      uVar4 = 0;
    }
  }
  else {
    puts("Error: OTA result file not exist");
    uVar4 = 0xffffffff;
  }
  return uVar4;
}



// === wifi_get_signal_level @ 004bba1c ===

char wifi_get_signal_level(int param_1)

{
  char cVar1;
  
  cVar1 = '\0';
  if (param_1 != 0) {
    if (-0x33 < param_1) {
      return '\x03';
    }
    cVar1 = (-0x47 < param_1) + '\x01';
  }
  return cVar1;
}



// === update_model_name @ 004bbd08 ===

void update_model_name(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = getodin();
  iVar1 = strcasecmp((char *)(iVar1 + 0x147c),"K1C");
  if (iVar1 != 0) {
    iVar1 = getodin();
    iVar1 = strcasecmp((char *)(iVar1 + 0x147c),"K1SE");
    if (iVar1 == 0) {
      *param_1 = 0x3ea;
      return;
    }
    iVar1 = getodin();
    iVar1 = strcasecmp((char *)(iVar1 + 0x147c),"K1");
    if (iVar1 == 0) {
      *param_1 = 0x3eb;
      return;
    }
    iVar1 = getodin();
    iVar1 = strcasecmp((char *)(iVar1 + 0x147c),"K1Max");
    if (iVar1 == 0) {
      *param_1 = 0x3ec;
      return;
    }
    iVar1 = getodin();
    iVar1 = strcasecmp((char *)(iVar1 + 0x147c),"ENDER3V3Plus");
    if (iVar1 == 0) {
      *param_1 = 0x3ed;
      iVar1 = getodin();
      if (*(int *)(iVar1 + 0x149c) != 0x3ee) {
        return;
      }
      *param_1 = 0x3ee;
      return;
    }
  }
  *param_1 = 0x3e9;
  return;
}



// === elapse_video_list_update @ 004bdcf4 ===

void elapse_video_list_update(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  uVar1 = lv_observer_get_target();
  iVar2 = page_obj_pop(0x20);
  iVar3 = lv_subject_get_int(param_2);
  iVar5 = *(int *)(iVar2 + 0x30);
  if ((iVar5 != 0) && (iVar3 != 0)) {
    iVar3 = *(int *)(iVar2 + 0x34) + -1;
    if (-1 < iVar3) {
      do {
        uVar4 = lv_obj_get_child(iVar5,iVar3);
        iVar3 = iVar3 + -1;
        lv_obj_delete(uVar4);
        iVar5 = *(int *)(iVar2 + 0x30);
      } while (iVar3 != -1);
    }
    lv_obj_delete();
    lv_obj_delete(*(undefined4 *)(iVar2 + 0x3c));
    page_settings_camera_videolist_fetch_list(uVar1);
    page_settings_camera_videolist_create_content(uVar1);
    page_settings_camera_videolist_create_buttons(uVar1);
    return;
  }
  return;
}



// === page_settings_system_updatenotification_in @ 004be59c ===

undefined4 page_settings_system_updatenotification_in(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = lv_obj_create();
  lv_obj_remove_style_all(uVar1);
  lv_obj_set_size(uVar1,0x20000014,0x20000064);
  lv_obj_align(uVar1,8,0,0);
  iVar2 = getodin();
  iVar2 = *(int *)(iVar2 + 0x1588);
  uVar3 = getcxfont(7);
  uVar3 = create_switch(uVar1,0,0,iVar2 != 0,uVar3);
  lv_obj_align(uVar3,8,0,0);
  lv_obj_add_event_cb(uVar3,upgradenotification_switch_event_cb,0x23,param_1);
  return uVar1;
}



// === upgradenotification_switch_event_cb @ 004be748 ===

void upgradenotification_switch_event_cb(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lv_event_get_target();
  uVar1 = lv_obj_has_state(uVar1,1);
  iVar2 = getodin();
  *(undefined4 *)(iVar2 + 0x1588) = uVar1;
  iVar2 = getodin();
  save_systemconfig(iVar2 + 0x12b8);
  return;
}



// === ota_download_progress_observer_cb @ 004bea40 ===

void ota_download_progress_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar1 = page_obj_pop(0xf);
  iVar2 = lv_observer_get_target(param_1);
  uVar3 = lv_observer_get_user_data(param_1);
  iVar4 = lv_subject_get_int(param_2);
  lv_bar_set_value(uVar3,iVar4,1);
  lv_obj_send_event(uVar3,0x23,0);
  if (iVar4 < 100) {
    return;
  }
  lv_obj_add_flag(uVar3,1);
  lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x50),1);
  uVar3 = lv_obj_get_child(*(undefined4 *)(iVar2 + 0x4c),0);
  uVar5 = lv_i18n_get_text("InstallingFirmware");
  lv_label_set_text(uVar3,uVar5);
  lv_obj_add_state(*(undefined4 *)(iVar2 + 0x4c),0x80);
  return;
}



// === ota_download_state_cb @ 004beb38 ===

void ota_download_state_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = lv_observer_get_target();
  iVar2 = lv_subject_get_int(param_2);
  if ((iVar2 != 0) && (iVar1 != 0)) {
    service_httpchunk_download_cancel();
    iVar2 = page_obj_pop(0xf);
    iVar3 = lv_obj_has_flag(*(undefined4 *)(iVar2 + 0x30),1);
    if (iVar3 == 0) {
      uVar4 = lv_i18n_get_text("DownloadFailRetry");
      widget_toast_create(0,uVar4,0,3000);
      uVar4 = *(undefined4 *)(iVar1 + 0x44);
    }
    else {
      uVar4 = *(undefined4 *)(iVar1 + 0x44);
    }
    lv_obj_remove_flag(uVar4,1);
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x4c),0x20000);
    lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x30),1);
    lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x50),1);
    return;
  }
  return;
}



// === cancel_ota_download_cb @ 004bec08 ===

undefined4 cancel_ota_download_cb(void)

{
  cancel_download = 1;
  return 0;
}



// === confirm_ota_start_download_cb @ 004bec10 ===

void confirm_ota_start_download_cb(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  char acStack_118 [256];
  undefined4 local_18;
  
  iVar1 = page_obj_pop(0xf);
  iVar2 = lv_event_get_user_data(param_1);
  lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x44),1);
  lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x4c),0x20000);
  lv_obj_center(*(undefined4 *)(iVar2 + 0x4c));
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x30),1);
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x50),1);
  widget_alert_add_cancel_event_cb(iVar2,cancel_ota_download_cb);
  iVar1 = getodin();
  strncpy(acStack_118,(char *)(iVar1 + 0x1de0),0x100);
  local_18 = 1;
  service_httpchunk_request(1,acStack_118,0x104);
  return;
}



// === ota_state_receive_cb @ 004bf514 ===

void ota_state_receive_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = lv_subject_get_int(param_2);
  if (iVar1 == 0) {
    return;
  }
  iVar1 = getodin();
  if (*(int *)(iVar1 + 0x1ff0) == 2) {
    widget_toast_close(widget_toast);
    local_20 = lv_i18n_get_text("Confirm");
    local_1c = 0;
    local_18 = 0;
    uVar2 = lv_i18n_get_text("WarmRemind");
    pcVar5 = "UpdateFileErr";
  }
  else {
    iVar1 = getodin();
    if (*(int *)(iVar1 + 0x1ff0) != 3) {
      return;
    }
    widget_toast_close(widget_toast);
    local_20 = lv_i18n_get_text("Confirm");
    local_1c = 0;
    local_18 = 0;
    uVar2 = lv_i18n_get_text("WarmRemind");
    pcVar5 = "UpdateErr";
  }
  uVar3 = lv_i18n_get_text(pcVar5);
  uVar2 = widget_alert_create(0,uVar2,uVar3,&local_20,0);
  uVar3 = lv_pct(0x46);
  uVar4 = lv_pct(0x3c);
  lv_obj_set_size(uVar2,uVar3,uVar4);
  return;
}



// === ota_local_copy_state_receive_cb @ 004bf640 ===

void ota_local_copy_state_receive_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  
  iVar1 = lv_subject_get_int(param_2);
  if (iVar1 < 100) {
    if (-1 < iVar1) {
      return;
    }
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_settings_system.c"
               ,0x328,"ota_local_copy_state_receive_cb","local ota copy fail");
    widget_toast_close(widget_toast);
    widget_toast = 0;
    local_118 = lv_i18n_get_text("Confirm");
    local_114 = 0;
    local_110 = 0;
    uVar3 = lv_i18n_get_text("WarmRemind");
    uVar4 = lv_i18n_get_text("UpdateErr");
    uVar3 = widget_alert_create(0,uVar3,uVar4,&local_118,0);
    uVar4 = lv_pct(0x46);
    uVar5 = lv_pct(0x3c);
    lv_obj_set_size(uVar3,uVar4,uVar5);
    iVar1 = getodin();
    if (*(int *)(iVar1 + 0x370c) != 0) {
      iVar1 = getodin();
      lv_free(*(undefined4 *)(iVar1 + 0x370c));
    }
  }
  else {
    iVar1 = getodin();
    if (*(int *)(iVar1 + 0x370c) != 0) {
      memset(&local_118,0,0x104);
      iVar1 = getodin();
      pcVar2 = strrchr((char *)(*(int *)(iVar1 + 0x370c) + 0x91),0x2f);
      if (pcVar2 == (char *)0x0) {
        iVar1 = getodin();
        pcVar2 = (char *)(*(int *)(iVar1 + 0x370c) + 0x91);
      }
      else {
        pcVar2 = pcVar2 + 1;
      }
      snprintf((char *)&local_118,0x100,"%s/%s","/usr/data",pcVar2);
      iVar1 = getodin();
      lv_free(*(undefined4 *)(iVar1 + 0x370c));
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_settings_system.c"
                 ,0x322,"ota_local_copy_state_receive_cb","local ota copy success: %s\n",&local_118)
      ;
      service_extcom_request(8,&local_118,0x104);
    }
  }
  iVar1 = getodin();
  *(undefined4 *)(iVar1 + 0x370c) = 0;
  return;
}



// === create_ota_version_info @ 004bfd18 ===

/* WARNING: Removing unreachable block (ram,0x004bff84) */
/* WARNING: Removing unreachable block (ram,0x004c002c) */

undefined4 create_ota_version_info(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  double dVar7;
  undefined *puVar8;
  char acStack_d0 [128];
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  
  local_2c = 0;
  uVar1 = lv_obj_create();
  lv_obj_set_style_pad_top(uVar1,0,0);
  lv_obj_set_style_pad_bottom(uVar1,0,0);
  lv_obj_set_style_bg_opa(uVar1,0,0);
  lv_obj_set_style_pad_left(uVar1,0,0);
  lv_obj_set_style_pad_right(uVar1,0,0);
  lv_obj_set_style_pad_top(uVar1,0,0);
  lv_obj_set_style_pad_bottom(uVar1,0,0);
  lv_obj_set_style_border_width(uVar1,0,0);
  lv_obj_set_scrollbar_mode(uVar1,0);
  lv_obj_set_flex_flow(uVar1,1);
  lv_obj_set_flex_align(uVar1,0,0,5);
  uVar2 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_row(uVar1,uVar2,0);
  uVar2 = lv_obj_create(uVar1);
  lv_obj_set_style_pad_top(uVar2,0,0);
  lv_obj_set_style_pad_bottom(uVar2,0,0);
  lv_obj_set_style_bg_opa(uVar2,0,0);
  lv_obj_set_style_border_width(uVar2,0,0);
  uVar3 = lv_pct(100);
  lv_obj_set_size(uVar2,uVar3,0x3fffffff);
  lv_obj_remove_flag(uVar2,0x10);
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  iVar4 = getodin();
  uVar3 = get_version(iVar4 + 0x12b8,&local_50);
  uVar5 = lv_i18n_get_text("CurVersion");
  snprintf(acStack_d0,0x80,"%s %s",uVar5,uVar3);
  uVar3 = getcxfont(6);
  uVar3 = create_label(uVar2,acStack_d0,0,uVar3);
  lv_obj_set_style_text_align(uVar3,1,0);
  lv_obj_align(uVar3,1,0,0);
  uVar5 = lv_i18n_get_text("NewVersion");
  uVar6 = getcxfont(6);
  uVar5 = create_label(uVar2,uVar5,0,uVar6);
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_align_to(uVar5,uVar3,0xd,0,iVar4 / 2);
  uVar3 = get_version(param_2 + 0x11,&local_50);
  snprintf(acStack_d0,0x80,"%s",uVar3);
  uVar3 = getcxfont(6);
  uVar3 = create_label(uVar2,acStack_d0,0,uVar3);
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_size(uVar3,iVar4 * 10,0x3fffffff);
  lv_label_set_long_mode(uVar3,2);
  lv_obj_set_style_text_align(uVar3,1,0);
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_align_to(uVar3,uVar5,0x14,iVar4 / 2,0);
  lv_obj_update_layout(uVar3);
  local_2c = 0;
  dVar7 = (double)*(int *)(param_2 + 0x194) * DAT_00614970 + 0.0;
  puVar8 = &DAT_00614758;
  snprintf(acStack_d0,0x80,"%.2f %s");
  uVar5 = getcxfont(6);
  uVar2 = create_label(uVar2,acStack_d0,0,uVar5,dVar7,puVar8);
  uVar3 = lv_obj_get_y(uVar3);
  lv_obj_align(uVar2,3,0,uVar3);
  uVar2 = lv_obj_create(uVar1);
  lv_obj_set_style_pad_top(uVar2,0,0);
  lv_obj_set_style_pad_bottom(uVar2,0,0);
  lv_obj_set_style_bg_opa(uVar2,0,0);
  lv_obj_set_style_border_width(uVar2,0,0);
  uVar3 = lv_pct(100);
  lv_obj_set_size(uVar2,uVar3,0x3fffffff);
  lv_obj_set_scrollbar_mode(uVar2,0);
  lv_obj_set_scroll_dir(uVar2,0xc);
  iVar4 = *(int *)(param_2 + 0x298);
  if (iVar4 != 0) {
    uVar3 = getcxfont(6);
    uVar2 = create_label(uVar2,iVar4,0,uVar3);
    uVar3 = lv_pct(100);
    lv_obj_set_size(uVar2,uVar3,0x3fffffff);
  }
  return uVar1;
}



// === ota_upgrade_start_event_handler @ 004c01d4 ===

/* WARNING: Removing unreachable block (ram,0x004c02e4) */

void ota_upgrade_start_event_handler(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  
  uVar1 = lv_event_get_user_data();
  iVar2 = page_obj_pop(0xf);
  uVar3 = get_printer_work_state();
  iVar4 = printer_is_working(uVar3);
  if (iVar4 != 0) {
    uVar1 = lv_i18n_get_text("WarningInPrintting");
    widget_toast_create(0,uVar1,0,1000);
    return;
  }
  iVar4 = getodin();
  if (*(int *)(iVar4 + 0x1ee0) == 0) {
    local_38 = 0;
    local_34 = 0;
    local_30 = lv_i18n_get_text("Confirm");
    uVar1 = lv_i18n_get_text("WarmRemind");
    uVar3 = lv_i18n_get_text("CurVersionIsLastest");
    uVar1 = widget_alert_create(0,uVar1,uVar3,&local_38,0);
    uVar3 = lv_pct(0x3c);
    lv_obj_set_size(uVar1,uVar3,0x20000050);
    return;
  }
  iVar4 = getodin();
  uVar3 = create_ota_version_info(iVar2,iVar4 + 0x1c48);
  uVar5 = lv_obj_create(uVar3);
  lv_obj_set_style_pad_top(uVar5,0,0);
  lv_obj_set_style_pad_bottom(uVar5,0,0);
  lv_obj_set_style_bg_opa(uVar5,0,0);
  lv_obj_set_style_border_width(uVar5,0,0);
  uVar6 = lv_pct(100);
  lv_obj_set_size(uVar5,uVar6,0x1e);
  lv_obj_align(uVar5,5,0,0);
  uVar6 = lv_bar_create(uVar5);
  *(undefined4 *)(iVar2 + 0x30) = uVar6;
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_size(uVar6,0x20000064,iVar4 / 4);
  lv_bar_set_value(uVar6,0,1);
  lv_color_make(local_24,0x17,0xcc,0x5f);
  lv_obj_set_style_bg_color(uVar6,local_24[0],0x30000);
  lv_color_make(&local_28,0x17,0xcc,0x5f);
  lv_obj_set_style_bg_color(uVar6,local_28,0);
  lv_color_make(&local_2c,0x17,0xcc,0x5f);
  lv_obj_set_style_bg_color(uVar6,local_2c,0x20000);
  lv_obj_align(uVar6,5,0,0);
  lv_obj_add_flag(uVar6,1);
  uVar7 = getcxfont(5);
  uVar5 = create_label(uVar5,&DAT_00613cbc,0,uVar7);
  *(undefined4 *)(iVar2 + 0x50) = uVar5;
  lv_obj_align(uVar5,5,0,0);
  lv_obj_add_flag(uVar5,1);
  lv_obj_add_event_cb(uVar6,bar_changed_event_cb,0x23,uVar5);
  local_38 = lv_i18n_get_text("Update");
  local_34 = 0;
  local_30 = lv_i18n_get_text("Cancel");
  uVar5 = lv_i18n_get_text("FoundHigherVersion");
  iVar4 = widget_alert_create(0,uVar5,0,&local_38,uVar1);
  widget_alert_add_confirm_event_cb(iVar4,confirm_ota_start_download_cb);
  uVar1 = lv_pct(0x3c);
  lv_obj_set_size(iVar4,uVar1,0x20000050);
  widget_alert_attach_body(iVar4,uVar3);
  uVar5 = *(undefined4 *)(iVar4 + 0x3c);
  uVar1 = lv_pct(100);
  uVar3 = lv_pct(0x46);
  lv_obj_set_size(uVar5,uVar1,uVar3);
  iVar8 = getodin();
  uVar1 = lv_subject_add_observer_obj(iVar8 + 0x1258,ota_download_state_cb,iVar4,0);
  *(undefined4 *)(iVar2 + 0x6c) = uVar1;
  iVar8 = getodin();
  uVar1 = lv_subject_add_observer_obj(iVar8 + 0x11d8,ota_download_progress_observer_cb,iVar4,uVar6);
  *(undefined4 *)(iVar2 + 0x68) = uVar1;
  return;
}



// === confirm_local_ota_upgrades_start_cb @ 004c05d4 ===

void confirm_local_ota_upgrades_start_cb(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  uVar1 = lv_event_get_user_data();
  widget_alert_close(uVar1);
  local_20 = lv_i18n_get_text("Reboot");
  local_1c = 0;
  local_18 = 0;
  uVar1 = lv_i18n_get_text("WarmRemind");
  uVar2 = lv_i18n_get_text("UpgradeRestartCaution");
  uVar1 = widget_alert_create(0,uVar1,uVar2,&local_20,0);
  uVar2 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_left(uVar1,uVar2,0);
  lv_obj_set_style_pad_right(uVar1,uVar2,0);
  lv_obj_set_style_pad_top(uVar1,uVar2,0);
  lv_obj_set_style_pad_bottom(uVar1,uVar2,0);
  uVar2 = lv_pct(0x3c);
  uVar3 = lv_pct(0x3c);
  lv_obj_set_size(uVar1,uVar2,uVar3);
  widget_alert_add_cancel_event_cb(uVar1,confirm_local_ota_start_cb);
  return;
}



// === confirm_local_ota_start_cb @ 004c06d8 ===

/* WARNING: Removing unreachable block (ram,0x004c07e8) */

void confirm_local_ota_start_cb(void)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  char acStack_420 [512];
  char acStack_220 [512];
  undefined4 local_20 [2];
  
  uVar1 = lv_event_get_target();
  widget_alert_close(uVar1);
  iVar2 = getodin();
  *(undefined4 *)(iVar2 + 0x370c) = alert_userobj;
  iVar2 = getodin();
  lv_subject_set_int(iVar2 + 0x1218,0);
  memset(acStack_420,0,0x400);
  iVar2 = getodin();
  snprintf(acStack_420,0x200,"%s",*(int *)(iVar2 + 0x370c) + 0x91);
  iVar2 = getodin();
  pcVar3 = strrchr((char *)(*(int *)(iVar2 + 0x370c) + 0x91),0x2f);
  if (pcVar3 == (char *)0x0) {
    iVar2 = getodin();
    pcVar3 = (char *)(*(int *)(iVar2 + 0x370c) + 0x91);
  }
  else {
    pcVar3 = pcVar3 + 1;
  }
  snprintf(acStack_220,0x200,"%s/%s","/usr/data",pcVar3);
  copy_file_with_progress(acStack_420);
  uVar1 = lv_i18n_get_text("RebootingPleaseWait");
  iVar2 = widget_toast_create(0,uVar1,0,0);
  uVar1 = *(undefined4 *)(iVar2 + 0x38);
  widget_toast = iVar2;
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  iVar4 = iVar4 / 4;
  lv_obj_set_style_pad_left(uVar1,iVar4,0);
  lv_obj_set_style_pad_right(uVar1,iVar4,0);
  lv_obj_set_style_pad_top(uVar1,iVar4,0);
  lv_obj_set_style_pad_bottom(uVar1,iVar4,0);
  uVar1 = lv_spinner_create(*(undefined4 *)(iVar2 + 0x38));
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  iVar5 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_size(uVar1,iVar4 << 1,iVar5 << 1);
  lv_obj_set_style_arc_width(uVar1,2,0);
  lv_obj_set_style_arc_width(uVar1,2,0x20000);
  lv_palette_main(local_20,9);
  lv_obj_set_style_arc_color(uVar1,local_20[0],0x20000);
  lv_spinner_set_anim_params(uVar1,2000,200);
  lv_obj_align_to(uVar1,*(undefined4 *)(iVar2 + 0x30),7,0,0);
  iVar2 = getodin();
  lv_subject_add_observer_obj(iVar2 + 0x1218,ota_local_copy_state_receive_cb,widget_toast,0);
  iVar2 = getodin();
  lv_subject_add_observer_obj(iVar2 + 0x1238,ota_state_receive_cb,widget_toast,0);
  return;
}



// === notify_local_ota_img_upgradable @ 004c09c4 ===

int notify_local_ota_img_upgradable(undefined4 param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  puVar2 = (undefined4 *)lv_malloc(0x29c);
  puVar1 = puVar2;
  puVar8 = param_2;
  do {
    puVar7 = puVar8;
    puVar3 = puVar1;
    uVar9 = puVar7[1];
    uVar5 = puVar7[3];
    uVar6 = puVar7[2];
    *puVar3 = *puVar7;
    puVar3[1] = uVar9;
    puVar3[2] = uVar6;
    puVar8 = puVar7 + 4;
    puVar3[3] = uVar5;
    puVar1 = puVar3 + 4;
  } while (puVar8 != param_2 + 0xa4);
  uVar6 = puVar7[5];
  uVar5 = puVar7[6];
  puVar3[4] = *puVar8;
  puVar3[5] = uVar6;
  puVar3[6] = uVar5;
  uVar5 = create_ota_version_info(param_1,puVar2);
  local_20 = lv_i18n_get_text("Update");
  local_1c = 0;
  local_18 = lv_i18n_get_text("Cancel");
  uVar6 = lv_i18n_get_text("FoundHigherVersion");
  iVar4 = widget_alert_create(0,uVar6,0,&local_20,puVar2);
  widget_alert_add_confirm_event_cb(iVar4,confirm_local_ota_upgrades_start_cb);
  lv_obj_set_size(iVar4,0x20000041,0x20000050);
  widget_alert_attach_body(iVar4,uVar5);
  uVar9 = *(undefined4 *)(iVar4 + 0x3c);
  uVar5 = lv_pct(100);
  uVar6 = lv_pct(0x46);
  lv_obj_set_size(uVar9,uVar5,uVar6);
  lv_obj_add_event_cb(iVar4,widget_alert_close_event_cb,0x29,0);
  alert_userobj = *(undefined4 *)(iVar4 + 0x2c);
  return iVar4;
}



// === avatar_update_observer_cb @ 004c2900 ===

void avatar_update_observer_cb(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = lv_observer_get_target();
  iVar2 = getodin();
  iVar2 = lv_subject_get_int(iVar2 + 0xf78);
  iVar3 = getodin();
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_settings_system_cloud.c"
             ,0x367,"avatar_update_observer_cb","Scan the QR code to log in successfully====%f",
             *(undefined8 *)(iVar3 + 0x19f8));
  iVar3 = getodin();
  iVar3 = strcasecmp((char *)(iVar3 + 0x147c),"K1Max");
  if (iVar3 == 0) {
    iVar3 = getodin();
    if (((*(double *)(iVar3 + 0x19f8) != 0.0) && (0 < iVar2)) ||
       ((iVar2 = getodin(), *(double *)(iVar2 + 0x19f8) != 0.0 &&
        (iVar2 = getodin(), *(int *)(iVar2 + 0x3710) != 0)))) {
LAB_004c29ec:
      page_settings_system_cloud_show_userinfo(uVar1);
      return;
    }
  }
  else {
    iVar3 = getodin();
    if ((*(double *)(iVar3 + 0x19f8) != 0.0) && (0 < iVar2)) goto LAB_004c29ec;
  }
  return;
}



// === cloud_qrcode_update_callback @ 004c2be4 ===

void cloud_qrcode_update_callback(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar1 = getodin();
  if (*(char *)(iVar1 + 0x368c) == '\0') {
    lv_obj_add_flag(*(undefined4 *)(iVar3 + 0x84),1);
    lv_obj_remove_flag(*(undefined4 *)(iVar3 + 0x8c),1);
    uVar4 = *(undefined4 *)(iVar3 + 0x7c);
    uVar2 = lv_i18n_get_text("UpdateQRFailed");
    lv_label_set_text(uVar4,uVar2);
    uVar2 = *(undefined4 *)(iVar3 + 0x4c);
  }
  else {
    lv_obj_add_flag(*(undefined4 *)(iVar3 + 0x88),1);
    lv_obj_add_flag(*(undefined4 *)(iVar3 + 0x84),1);
    lv_obj_add_flag(*(undefined4 *)(iVar3 + 0x8c),1);
    lv_obj_add_flag(*(undefined4 *)(iVar3 + 0x7c),1);
    lv_obj_add_flag(*(undefined4 *)(iVar3 + 0x80),1);
    lv_obj_remove_flag(*(undefined4 *)(iVar3 + 0x78),1);
    uVar2 = *(undefined4 *)(iVar3 + 0x4c);
  }
  lv_obj_remove_state(uVar2,0x80);
  lv_obj_remove_state(*(undefined4 *)(iVar3 + 0x50),0x80);
  if (*(int *)(iVar3 + 0x94) != 0) {
    lv_timer_delete();
    *(undefined4 *)(iVar3 + 0x94) = 0;
  }
  return;
}



// === page_set_update_cloud_qrcode_loading @ 004c2e10 ===

void page_set_update_cloud_qrcode_loading(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  lv_obj_add_state(*(undefined4 *)(param_1 + 0x4c),0x80);
  lv_obj_add_state(*(undefined4 *)(param_1 + 0x50),0x80);
  lv_obj_add_flag(*(undefined4 *)(param_1 + 0x78),1);
  lv_obj_remove_flag(*(undefined4 *)(param_1 + 0x88),1);
  lv_obj_add_flag(*(undefined4 *)(param_1 + 0x88),0x20000);
  uVar2 = *(undefined4 *)(param_1 + 0x88);
  iVar1 = lv_obj_get_parent(uVar2);
  if (iVar1 == 0) {
    lv_log_add(2,2,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/lv_api_map_v8.h"
               ,0x5a,"lv_obj_move_foreground","parent is NULL");
    uVar2 = *(undefined4 *)(param_1 + 0x8c);
  }
  else {
    iVar1 = lv_obj_get_child_count(iVar1);
    lv_obj_move_to_index(uVar2,iVar1 + -1);
    uVar2 = *(undefined4 *)(param_1 + 0x8c);
  }
  lv_obj_add_flag(uVar2,1);
  lv_obj_remove_flag(*(undefined4 *)(param_1 + 0x84),1);
  lv_obj_remove_flag(*(undefined4 *)(param_1 + 0x7c),1);
  uVar3 = *(undefined4 *)(param_1 + 0x7c);
  uVar2 = lv_i18n_get_text("UpdateQRCode");
  lv_label_set_text(uVar3,uVar2);
  lv_obj_remove_flag(*(undefined4 *)(param_1 + 0x80),1);
  return;
}



// === reset_style_cloud_qrcode_update_info.part.3 @ 004c2f18 ===

void reset_style_cloud_qrcode_update_info_part_3(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18 [3];
  
  if (*(int *)(param_1 + 0x88) != 0) {
    lv_obj_add_flag(*(int *)(param_1 + 0x88),0x20000);
    lv_obj_set_style_bg_opa(*(undefined4 *)(param_1 + 0x88),0x7f,0);
    uVar2 = *(undefined4 *)(param_1 + 0x88);
    lv_color_black(local_18);
    lv_obj_set_style_bg_color(uVar2,local_18[0],0);
    lv_obj_align(*(undefined4 *)(param_1 + 0x88),5,0,0xffffffba);
    uVar2 = *(undefined4 *)(param_1 + 0x88);
    iVar1 = lv_obj_get_parent(uVar2);
    if (iVar1 == 0) {
      lv_log_add(2,2,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/lv_api_map_v8.h"
                 ,0x5a,"lv_obj_move_foreground","parent is NULL");
      uVar2 = *(undefined4 *)(param_1 + 0x7c);
    }
    else {
      iVar1 = lv_obj_get_child_count(iVar1);
      lv_obj_move_to_index(uVar2,iVar1 + -1);
      uVar2 = *(undefined4 *)(param_1 + 0x7c);
    }
    lv_obj_add_flag(uVar2,0x20000);
    lv_obj_align_to(*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x88),0xe,0,0);
    lv_obj_add_flag(*(undefined4 *)(param_1 + 0x80),0x20000);
    lv_obj_align_to(*(undefined4 *)(param_1 + 0x80),*(undefined4 *)(param_1 + 0x7c),0xe,0,0xfffffffb
                   );
    return;
  }
  return;
}



// === zoffset_setting_update_observer_cb @ 004c47cc ===

void zoffset_setting_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  double dVar5;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  undefined4 local_1c;
  
  local_1c = 0;
  iVar1 = lv_observer_get_target();
  if (iVar1 == 0) {
    return;
  }
  iVar2 = *(int *)(iVar1 + 0x30);
  if (iVar2 == 0) {
    return;
  }
  if (*(int *)(iVar2 + 0x5c) != 0) {
    iVar2 = getodin();
    if (*(char *)(iVar2 + 0x2bcd) == '\0') {
      iVar2 = getodin();
      local_1c = 0;
      if (DAT_005959a8 < *(double *)(iVar2 + 0x2340)) {
        dVar5 = DAT_005959a8;
        iVar3 = getodin();
        local_1c = 0;
        iVar2 = *(int *)(iVar1 + 0x30);
        if (dVar5 < *(double *)(iVar3 + 0x2340)) {
          lv_imagebutton_set_state(*(undefined4 *)(iVar2 + 0x5c),0);
          lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x5c),0,0);
          uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x5c);
          lv_color_make(&local_28,0x2d,0x2e,0x31);
          lv_obj_set_style_image_recolor(uVar4,local_28,0);
          iVar2 = *(int *)(iVar1 + 0x30);
        }
        goto LAB_004c489c;
      }
    }
    lv_imagebutton_set_state(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x5c),2);
    lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x5c),0x4c,0);
    uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x5c);
    lv_color_make(local_24,0x22,0x23,0x25);
    lv_obj_set_style_image_recolor(uVar4,local_24[0],0);
    iVar2 = *(int *)(iVar1 + 0x30);
  }
LAB_004c489c:
  if (*(int *)(iVar2 + 0x60) == 0) {
    return;
  }
  iVar2 = getodin();
  if (*(char *)(iVar2 + 0x2bce) == '\0') {
    iVar2 = getodin();
    local_1c = 0;
    if (*(double *)(iVar2 + 0x2340) < DAT_005959a0) {
      dVar5 = DAT_005959a0;
      iVar2 = getodin();
      local_1c = 0;
      if (dVar5 <= *(double *)(iVar2 + 0x2340)) {
        return;
      }
      lv_imagebutton_set_state(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x60),0);
      lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x60),0,0);
      uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x60);
      lv_color_make(&local_30,0x2d,0x2e,0x31);
      local_2c = local_30;
      goto LAB_004c498c;
    }
  }
  lv_imagebutton_set_state(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x60),2);
  lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x60),0x4c,0);
  uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x30) + 0x60);
  lv_color_make(&local_2c,0x22,0x23,0x25);
LAB_004c498c:
  local_1c = 0;
  lv_obj_set_style_image_recolor(uVar4,local_2c,0);
  return;
}



// === print_flow_update_observer_cb @ 004c4b30 ===

void print_flow_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_observer_get_target();
  if (((iVar1 != 0) && (*(int *)(iVar1 + 0x34) != 0)) &&
     (iVar1 = *(int *)(*(int *)(iVar1 + 0x34) + 0x4c), iVar1 != 0)) {
    iVar2 = getodin();
    lv_label_set_text_fmt
              (iVar1,&DAT_00613bf0,(int)(*(double *)(iVar2 + 0x2360) * DAT_00613d68 + DAT_00614dc0))
    ;
    return;
  }
  return;
}



// === zoffset_update_observer_cb @ 004c4bf4 ===

void zoffset_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_observer_get_target();
  if (((iVar1 != 0) && (*(int *)(iVar1 + 0x30) != 0)) &&
     (iVar1 = *(int *)(*(int *)(iVar1 + 0x30) + 0x4c), iVar1 != 0)) {
    iVar2 = getodin();
    lv_label_set_text_fmt
              (iVar1,"%0.3lfmm",*(undefined4 *)(iVar2 + 0x2340),*(undefined4 *)(iVar2 + 0x2344));
  }
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2bd0,1);
  return;
}



// === extruder_pid_state_update_observer_cb @ 004c628c ===

void extruder_pid_state_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  iVar2 = *(int *)(iVar2 + 0x2704);
  if (iVar2 == 1) {
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x38),1);
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x3c),1);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x40),1);
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x44),1);
    uVar4 = *(undefined4 *)(iVar1 + 0x48);
    uVar3 = lv_i18n_get_text("PIDExtruderCaliTip");
    lv_label_set_text(uVar4,uVar3);
    uVar4 = *(undefined4 *)(iVar1 + 0x4c);
    uVar3 = lv_i18n_get_text("PIDExtruderCaliTimeTip");
    lv_label_set_text(uVar4,uVar3);
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x50),1);
    lv_obj_add_state(*(undefined4 *)(iVar1 + 0x30),0x80);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x2c),1);
    return;
  }
  if (iVar2 != 0) {
    if (iVar2 == 2) {
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x38),1);
      lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x3c),1);
      lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x40),1);
      lv_label_set_text(*(undefined4 *)(iVar1 + 0x40),&DAT_006133c8);
      uVar3 = *(undefined4 *)(iVar1 + 0x40);
      lv_color_make(&local_18,0x17,0xcc,0x5f);
      lv_obj_set_style_text_color(uVar3,local_18,0);
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x44),1);
      uVar4 = *(undefined4 *)(iVar1 + 0x48);
      uVar3 = lv_i18n_get_text("PIDExtruderCaliComplete");
      lv_label_set_text(uVar4,uVar3);
      uVar4 = *(undefined4 *)(iVar1 + 0x4c);
      uVar3 = lv_i18n_get_text("PIDExtruderCaliSuccess");
      lv_label_set_text(uVar4,uVar3);
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x50),1);
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x34),1);
      uVar3 = *(undefined4 *)(iVar1 + 0x5c);
    }
    else {
      if (iVar2 != 3) {
        return;
      }
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x38),1);
      lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x3c),1);
      lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x40),1);
      lv_label_set_text(*(undefined4 *)(iVar1 + 0x40),&DAT_00613430);
      uVar3 = *(undefined4 *)(iVar1 + 0x40);
      lv_palette_main(local_14,0);
      lv_obj_set_style_text_color(uVar3,local_14[0],0);
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x44),1);
      uVar4 = *(undefined4 *)(iVar1 + 0x48);
      uVar3 = lv_i18n_get_text("PIDExtruderCaliComplete");
      lv_label_set_text(uVar4,uVar3);
      uVar4 = *(undefined4 *)(iVar1 + 0x4c);
      uVar3 = lv_i18n_get_text("PIDExtruderCaliFail");
      lv_label_set_text(uVar4,uVar3);
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x50),1);
      lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x5c),1);
      uVar3 = *(undefined4 *)(iVar1 + 0x34);
    }
    iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
    lv_obj_align(uVar3,9,0,iVar2 << 2);
    lv_obj_remove_state(*(undefined4 *)(iVar1 + 0x30),0x80);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x2c),1);
    return;
  }
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x38),1);
  lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x3c),1);
  lv_obj_remove_state(*(undefined4 *)(iVar1 + 0x30),0x80);
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x2c),1);
  return;
}



// === local_network_connect_update_observer_cb @ 004c9bcc ===

void local_network_connect_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  iVar2 = lv_subject_get_int(iVar2 + 0x3778);
  if (iVar2 == 0) {
    return;
  }
  iVar2 = getodin();
  uVar4 = *(undefined4 *)(iVar1 + 0x3c);
  if (*(int *)(iVar2 + 0x3710) != 0) {
    uVar3 = lv_i18n_get_text("ConnectedNetwork");
    lv_label_set_text_fmt(uVar4,uVar3);
    return;
  }
  uVar3 = lv_i18n_get_text("UnConnectedNetwork");
  lv_label_set_text_fmt(uVar4,uVar3);
  return;
}



// === auth_wifi_delete_handler @ 004c9c5c ===

void auth_wifi_delete_handler(void)

{
  int iVar1;
  
  iVar1 = lv_event_get_user_data();
  *(undefined4 *)(iVar1 + 0x34) = 0;
  return;
}



// === auth_wifi_event_handler @ 004c9e7c ===

void auth_wifi_event_handler(undefined4 param_1)

{
  undefined4 uVar1;
  
  lv_event_get_code();
  lv_event_get_target(param_1);
  uVar1 = lv_event_get_param(param_1);
  page_obj_pop(0x1c);
  service_wifi_request(3,uVar1,0x180);
  scan_ap_count = 1;
  scan_ap_cycle = 10;
  return;
}



// === page_settings_wifi_update_scan_list @ 004cab18 ===

/* WARNING: Removing unreachable block (ram,0x004cb06c) */
/* WARNING: Removing unreachable block (ram,0x004cae48) */
/* WARNING: Removing unreachable block (ram,0x004cad08) */

void page_settings_wifi_update_scan_list(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  undefined4 local_38 [2];
  undefined4 local_30;
  
  local_30 = 0;
  lv_obj_clean(*(undefined4 *)(param_1 + 0x2c));
  iVar2 = getodin();
  iVar2 = strcasecmp((char *)(iVar2 + 0x147c),"K1Max");
  if (iVar2 == 0) {
    uVar4 = lv_obj_create(*(undefined4 *)(param_1 + 0x2c));
    lv_obj_remove_style_all(uVar4);
    iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
    local_30 = 0;
    dVar10 = 0.0;
    lv_obj_set_style_pad_top(uVar4,-iVar2 / 2,0);
    lv_obj_set_style_pad_bottom(uVar4,-iVar2 / 2,0);
    lv_obj_set_size(uVar4,0x20000064,0x32);
    uVar5 = lv_image_create(uVar4);
    lv_obj_set_size(uVar5,0x3fffffff);
    lv_image_set_src(uVar5,local_network);
    lv_obj_set_style_bg_image_opa(uVar5,0xff,0);
    uVar6 = lv_font_get_line_height(lv_font_montserrat_14);
    lv_obj_align(uVar5,7,uVar6,0);
    uVar5 = lv_i18n_get_text("LocalNetwork");
    uVar6 = getcxfont(7);
    uVar5 = create_label(uVar4,uVar5,0,uVar6);
    lv_obj_set_size(uVar5,0x3fffffff);
    lv_obj_set_style_text_align(uVar5,1,0);
    iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
    local_30 = 0;
    lv_obj_align(uVar5,7,(int)((double)iVar2 * DAT_00613568 + dVar10),0);
    lv_obj_add_event_cb(uVar4,local_network_event_handler,10,param_1);
    iVar2 = getodin();
    if (*(int *)(iVar2 + 0x3710) == 0) {
      pcVar7 = "UnConnectedNetwork";
    }
    else {
      pcVar7 = "ConnectedNetwork";
    }
    uVar5 = lv_i18n_get_text(pcVar7);
    uVar6 = getcxfont(7);
    uVar5 = create_label(uVar4,uVar5,0,uVar6);
    *(undefined4 *)(param_1 + 0x3c) = uVar5;
    lv_obj_set_size(uVar5,0x3fffffff);
    iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
    local_30 = 0;
    lv_obj_align(uVar5,8,(int)((double)-iVar2 * DAT_00612550 + dVar10),0);
    uVar5 = create_label(uVar4,&DAT_00614360,0,DAT_0084d934);
    iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
    lv_obj_align(uVar5,8,-iVar2 / 2,0);
    lv_color_make(local_38,0x43,0x45,0x49);
    lv_obj_set_style_border_color(uVar4,local_38[0],0);
    lv_obj_set_style_border_width(uVar4,1,0);
    lv_obj_set_style_border_side(uVar4,1,0);
    page_settings_wifi_fetch_list(param_1);
    iVar2 = *(int *)(param_1 + 0x44);
  }
  else {
    page_settings_wifi_fetch_list(param_1);
    iVar2 = *(int *)(param_1 + 0x44);
  }
  if (iVar2 == 0) {
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_settings_wifi.c"
               ,0x2c8,"page_settings_wifi_update_scan_list","NULL active_scan_info\n");
    uVar4 = *(undefined4 *)(param_1 + 0x2c);
  }
  else {
    iVar9 = 0;
    if (0 < *(int *)(param_1 + 0x48)) {
      iVar2 = iVar2 + 200;
      iVar8 = iVar2;
      do {
        while( true ) {
          iVar3 = is_connected_ssid(iVar8);
          iVar9 = iVar9 + 1;
          if (iVar3 == 0) break;
          page_settings_wifi_draw_ap_item(param_1,iVar8 + -200);
          piVar1 = (int *)(iVar8 + -0x84);
          iVar8 = iVar8 + 0x1c8;
          uVar4 = wifi_get_signal_level(-*piVar1);
          iVar3 = getodin();
          lv_subject_set_int(iVar3 + 0xf78,uVar4);
          iVar3 = *(int *)(param_1 + 0x48);
          if (iVar3 <= iVar9) goto LAB_004cac28;
        }
        iVar3 = *(int *)(param_1 + 0x48);
        iVar8 = iVar8 + 0x1c8;
      } while (iVar9 < iVar3);
LAB_004cac28:
      iVar8 = 0;
      iVar9 = iVar2;
      if (iVar3 < 1) {
        uVar4 = *(undefined4 *)(param_1 + 0x2c);
        goto LAB_004cace4;
      }
      do {
        while( true ) {
          iVar3 = is_connected_ssid(iVar9);
          iVar8 = iVar8 + 1;
          if ((iVar3 != 0) || (iVar3 = is_saved_ssid(iVar9), iVar3 == 0)) break;
          page_settings_wifi_draw_ap_item(param_1,iVar9 + -200);
          iVar3 = *(int *)(param_1 + 0x48);
          iVar9 = iVar9 + 0x1c8;
          if (iVar3 <= iVar8) goto LAB_004cac84;
        }
        iVar3 = *(int *)(param_1 + 0x48);
        iVar9 = iVar9 + 0x1c8;
      } while (iVar8 < iVar3);
LAB_004cac84:
      if (0 < iVar3) {
        iVar9 = 0;
        do {
          while( true ) {
            iVar8 = is_connected_ssid(iVar2);
            iVar9 = iVar9 + 1;
            if ((iVar8 != 0) || (iVar8 = is_saved_ssid(iVar2), iVar8 != 0)) break;
            page_settings_wifi_draw_ap_item(param_1,iVar2 + -200);
            iVar2 = iVar2 + 0x1c8;
            if (*(int *)(param_1 + 0x48) <= iVar9) goto LAB_004cace0;
          }
          iVar2 = iVar2 + 0x1c8;
        } while (iVar9 < *(int *)(param_1 + 0x48));
      }
    }
LAB_004cace0:
    uVar4 = *(undefined4 *)(param_1 + 0x2c);
  }
LAB_004cace4:
  uVar4 = lv_obj_create(uVar4);
  lv_obj_remove_style_all(uVar4);
  iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_top(uVar4,iVar2 / 2,0);
  lv_obj_set_style_pad_bottom(uVar4,iVar2 / 2,0);
  lv_obj_set_size(uVar4,0x20000064,0x3fffffff);
  uVar5 = lv_i18n_get_text("WiFiOther");
  uVar6 = getcxfont(7);
  uVar5 = create_label(uVar4,uVar5,0,uVar6);
  lv_obj_set_size(uVar5,0x3fffffff);
  lv_obj_set_style_text_align(uVar5,1,0);
  uVar6 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_align(uVar5,7,uVar6,0);
  local_30 = 0;
  lv_obj_add_event_cb(uVar4,wifi_entry_event_handler,10,0);
  return;
}



// === create_update_udisk_list @ 004cc4c4 ===

/* WARNING: Removing unreachable block (ram,0x004cc728) */

void create_update_udisk_list(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  double dVar7;
  undefined1 auStack_a0 [64];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  undefined *local_44;
  int local_40;
  undefined4 local_34;
  
  local_34 = 0;
  iVar1 = page_obj_pop(0x27);
  iVar2 = getodin();
  if (*(int *)(iVar2 + 0x2c98) < 5) {
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x40),0x10);
    lv_obj_set_flex_align(*(undefined4 *)(iVar1 + 0x40),2,2,5);
  }
  else {
    lv_obj_add_flag();
    lv_obj_set_flex_align(*(undefined4 *)(iVar1 + 0x40),0,2,5);
  }
  iVar3 = lv_obj_get_child_count(*(undefined4 *)(iVar1 + 0x40));
  iVar2 = iVar3 + -1;
  if (0 < iVar3) {
    do {
      while (iVar3 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x40),iVar2), iVar3 == 0) {
        iVar3 = iVar2 + -1;
        printf("Failed to get child at index %d\n",iVar2);
        iVar2 = iVar3;
        if (iVar3 == -1) goto LAB_004cc5bc;
      }
      iVar2 = iVar2 + -1;
      lv_obj_delete(iVar3);
    } while (iVar2 != -1);
  }
LAB_004cc5bc:
  local_34 = 0;
  local_48 = 0x4d0000;
  local_44 = &DAT_006133b8;
  dVar7 = DAT_00612550;
  iVar2 = getodin();
  uVar6 = 0;
  if (*(int *)(iVar2 + 0x2c98) != 0) {
    do {
      uVar4 = lv_obj_create(param_1);
      lv_obj_set_size(uVar4,0x62,0x3fffffff);
      lv_obj_remove_flag(uVar4,0x10);
      lv_color_make(&local_4c,0x60,0x62,0x66);
      lv_obj_set_style_bg_color(uVar4,local_4c,0);
      lv_obj_set_style_bg_opa(uVar4,0xcc,0);
      lv_obj_set_style_border_width(uVar4,1,0);
      lv_color_make(&local_50,0x60,0x62,0x66);
      lv_obj_set_style_border_color(uVar4,local_50,0);
      lv_obj_add_event_cb(uVar4,local_48 + -0x36c8,10,param_1);
      uVar5 = create_label(uVar4,local_44,0,DAT_0084d948);
      lv_color_make(&local_54,0xff,0xff,0xff);
      lv_obj_set_style_text_color(uVar5,local_54,0);
      lv_color_make(&local_58,0x74,0x74,0x74);
      lv_obj_set_style_bg_color(uVar5,local_58,0);
      iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
      lv_obj_align(uVar5,2,0,-iVar2 / 2);
      iVar2 = getodin();
      lv_snprintf(auStack_a0,0x40,"%s",*(int *)(iVar2 + 0x2c9c) + uVar6 * 0x100);
      uVar5 = getcxfont(4);
      uVar5 = create_label(uVar4,auStack_a0,0,uVar5);
      lv_obj_set_style_text_align(uVar5,1,0);
      iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
      local_34 = 0;
      lv_obj_align_to(uVar5,uVar4,2,0,(int)((double)iVar2 * dVar7 + 0.0));
      if (uVar6 == 0) {
        iVar2 = getodin();
        snprintf((char *)(iVar1 + 0x14c),0x100,"%s",*(undefined4 *)(iVar2 + 0x2c9c));
        local_40 = getodin();
        iVar2 = getodin();
        snprintf((char *)(iVar1 + 0x4c),0x100,"%s/%s",local_40 + 0x2c34,
                 *(undefined4 *)(iVar2 + 0x2c9c));
        strncpy((char *)(iVar1 + 0x24c),(char *)(iVar1 + 0x4c),0xff);
        *(undefined1 *)(iVar1 + 0x34b) = 0;
        lv_color_make(&local_5c,0x17,0xcc,0x5f);
        lv_obj_set_style_bg_color(uVar4,local_5c,0);
        lv_obj_set_style_bg_opa(uVar4,0x4c,0);
        lv_color_make(&local_60,0x17,0xcc,0x5f);
        lv_obj_set_style_border_color(uVar4,local_60,0);
      }
      uVar6 = uVar6 + 1;
      iVar2 = getodin();
    } while (uVar6 < *(uint *)(iVar2 + 0x2c98));
  }
  return;
}



// === udisk_list_log_update_observer_cb @ 004cd01c ===

void udisk_list_log_update_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *__dest;
  
  iVar1 = lv_observer_get_target();
  iVar2 = lv_subject_get_int(param_2);
  if ((*(int *)(iVar1 + 0x40) == 0) || (iVar2 == 0)) {
    iVar2 = getodin();
    iVar2 = *(int *)(iVar2 + 0x2c98);
  }
  else {
    create_update_udisk_list();
    iVar2 = getodin();
    iVar2 = *(int *)(iVar2 + 0x2c98);
  }
  if (iVar2 == 0) {
    if (*(int *)(iVar1 + 0x40) != 0) {
      widget_alert_close(*(undefined4 *)(iVar1 + 0x44));
      *(undefined4 *)(iVar1 + 0x40) = 0;
    }
    if (*(int *)(iVar1 + 0x34) != 0) {
      lv_obj_delete();
    }
    if (*(int *)(iVar1 + 0x38) != 0) {
      lv_obj_clean();
    }
    iVar2 = getodin();
    lv_ll_clear(iVar2 + 0x4a0);
    back_to_parent(iVar1);
    return;
  }
  iVar2 = getodin();
  if (0 < *(int *)(iVar2 + 0x2c98)) {
    *(undefined4 *)(iVar1 + 0x48) = 0;
    iVar2 = getodin();
    snprintf((char *)(iVar1 + 0x14c),0x100,"%s",*(undefined4 *)(iVar2 + 0x2c9c));
    iVar2 = getodin();
    iVar3 = getodin();
    snprintf((char *)(iVar1 + 0x4c),0x100,"%s/%s",iVar2 + 0x2c34,*(undefined4 *)(iVar3 + 0x2c9c));
    strncpy((char *)(iVar1 + 0x24c),(char *)(iVar1 + 0x4c),0xff);
    *(undefined1 *)(iVar1 + 0x34b) = 0;
    iVar2 = getodin();
    lv_ll_clear(iVar2 + 0x4a0);
    iVar2 = getodin();
    __dest = (char *)lv_ll_ins_head(iVar2 + 0x4a0);
    strcpy(__dest,(char *)(iVar1 + 0x24c));
    if (*(int *)(iVar1 + 0x34) != 0) {
      lv_obj_delete();
      page_support_faultreport_export_create_navi(iVar1);
    }
    if (*(int *)(iVar1 + 0x38) != 0) {
      lv_obj_clean();
      page_support_faultreport_export_create_foldlist(iVar1);
      return;
    }
  }
  return;
}



// === speed_value_update_observer_cb @ 004cf028 ===

/* WARNING: Control flow encountered bad instruction data */

void speed_value_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  if (ABS(*(double *)(iVar2 + 0x2298)) <= DAT_00615960) {
    lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x40),"%.1fmm/s",0,0);
    return;
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === speed_mode_update_observer_cb @ 004cf284 ===

void speed_mode_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  if (*(int *)(iVar2 + 0xf6c) != 3) {
    lv_obj_add_flag();
    return;
  }
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x68),1);
  return;
}



// === wifi_signal_strength_observer_cb @ 004cf37c ===

void wifi_signal_strength_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = lv_observer_get_target();
  uVar2 = lv_subject_get_int(param_2);
  if (3 < uVar2) {
    return;
  }
  lv_label_set_text(*(undefined4 *)(iVar1 + 0x60),*(undefined4 *)(wifi_signal_icons + uVar2 * 4));
  return;
}



// === axis_position_update_update_callback @ 004d1d50 ===

void axis_position_update_update_callback(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  
  iVar2 = 0;
  puVar3 = (undefined4 *)(*(int *)(param_1 + 0xc) + 0x50);
  do {
    uVar4 = *puVar3;
    iVar1 = getodin();
    uVar5 = *(undefined8 *)((iVar2 + 0x44f) * 8 + iVar1);
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 1;
    lv_label_set_text_fmt(uVar4,"%0.2lf",(int)uVar5,(int)((ulonglong)uVar5 >> 0x20));
  } while (iVar2 != 3);
  return;
}



// === zoffset_setting_update_observer_cb @ 004d1e0c ===

void zoffset_setting_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  double dVar5;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24 [2];
  undefined4 local_1c;
  
  local_1c = 0;
  iVar1 = lv_observer_get_target();
  if (iVar1 == 0) {
    return;
  }
  iVar2 = *(int *)(iVar1 + 0x7c);
  if (iVar2 == 0) {
    return;
  }
  if (*(int *)(iVar2 + 0x5c) != 0) {
    iVar2 = getodin();
    if (*(char *)(iVar2 + 0x2bcd) == '\0') {
      iVar2 = getodin();
      local_1c = 0;
      if (DAT_005959a8 < *(double *)(iVar2 + 0x2340)) {
        dVar5 = DAT_005959a8;
        iVar3 = getodin();
        local_1c = 0;
        iVar2 = *(int *)(iVar1 + 0x7c);
        if (dVar5 < *(double *)(iVar3 + 0x2340)) {
          lv_imagebutton_set_state(*(undefined4 *)(iVar2 + 0x5c),0);
          lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x5c),0,0);
          uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x5c);
          lv_color_make(&local_28,0x2d,0x2e,0x31);
          lv_obj_set_style_image_recolor(uVar4,local_28,0);
          iVar2 = *(int *)(iVar1 + 0x7c);
        }
        goto LAB_004d1edc;
      }
    }
    lv_imagebutton_set_state(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x5c),2);
    lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x5c),0x4c,0);
    uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x5c);
    lv_color_make(local_24,0x22,0x23,0x25);
    lv_obj_set_style_image_recolor(uVar4,local_24[0],0);
    iVar2 = *(int *)(iVar1 + 0x7c);
  }
LAB_004d1edc:
  if (*(int *)(iVar2 + 0x60) == 0) {
    return;
  }
  iVar2 = getodin();
  if (*(char *)(iVar2 + 0x2bce) == '\0') {
    iVar2 = getodin();
    local_1c = 0;
    if (*(double *)(iVar2 + 0x2340) < DAT_005959a0) {
      dVar5 = DAT_005959a0;
      iVar2 = getodin();
      local_1c = 0;
      if (dVar5 <= *(double *)(iVar2 + 0x2340)) {
        return;
      }
      lv_imagebutton_set_state(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x60),0);
      lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x60),0,0);
      uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x60);
      lv_color_make(&local_30,0x2d,0x2e,0x31);
      local_2c = local_30;
      goto LAB_004d1fcc;
    }
  }
  lv_imagebutton_set_state(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x60),2);
  lv_obj_set_style_image_recolor_opa(*(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x60),0x4c,0);
  uVar4 = *(undefined4 *)(*(int *)(iVar1 + 0x7c) + 0x60);
  lv_color_make(&local_2c,0x22,0x23,0x25);
LAB_004d1fcc:
  local_1c = 0;
  lv_obj_set_style_image_recolor(uVar4,local_2c,0);
  return;
}



// === axis_e_status_update_observer_cb @ 004d20f8 ===

void axis_e_status_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = lv_observer_get_target();
  if (iVar1 == 0) {
    return;
  }
  iVar2 = pre_print_material_runout_verify();
  if (iVar2 == 0) {
    lv_obj_remove_flag();
    iVar2 = getodin();
    iVar2 = *(int *)(iVar2 + 0x2c10);
  }
  else {
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x68),1);
    iVar2 = getodin();
    iVar2 = *(int *)(iVar2 + 0x2c10);
  }
  if (iVar2 == 0) {
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x6c),1);
    uVar3 = *(undefined4 *)(iVar1 + 0x70);
  }
  else {
    iVar2 = getodin();
    if (*(int *)(iVar2 + 0x2c10) != 1) {
      lv_obj_add_flag();
      lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x70),1);
      return;
    }
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x6c),1);
    uVar3 = *(undefined4 *)(iVar1 + 0x70);
  }
  lv_obj_add_flag(uVar3,1);
  return;
}



// === speed_mode_update_observer_cb @ 004d21d8 ===

void speed_mode_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  char *__format;
  undefined4 uVar6;
  int iVar7;
  char acStack_60 [64];
  undefined4 local_20;
  
  local_20 = 0;
  iVar1 = lv_observer_get_target();
  if (iVar1 == 0) {
    return;
  }
  memset(acStack_60,0,0x40);
  iVar2 = getodin();
  if (*(int *)(iVar2 + 0xf6c) == 3) {
    uVar6 = lv_i18n_get_text("SlicentMode");
    __format = "%s";
  }
  else {
    iVar2 = getodin();
    if (*(int *)(iVar2 + 0xf6c) == 4) {
      iVar2 = getodin();
      local_20 = 0;
      snprintf(acStack_60,0x40,"%d%%",(int)(*(double *)(iVar2 + 0x2358) * DAT_00613d68 + 0.0));
      uVar6 = *(undefined4 *)(iVar1 + 0x30);
      goto LAB_004d2298;
    }
    iVar2 = getodin();
    uVar6 = (&speed_mode_list)[*(int *)(iVar2 + 0xf6c)];
    __format = "%d%%";
  }
  snprintf(acStack_60,0x40,__format,uVar6);
  uVar6 = *(undefined4 *)(iVar1 + 0x30);
LAB_004d2298:
  lv_label_set_text(uVar6,acStack_60);
  if (*(int *)(iVar1 + 0x78) != 0) {
    iVar2 = getodin();
    if (*(int *)(iVar2 + 0xf6c) == 4) {
      *(undefined4 *)(*(int *)(iVar1 + 0x78) + 0x2c) = 0xffffffff;
    }
    else {
      iVar2 = getodin();
      *(undefined4 *)(*(int *)(iVar1 + 0x78) + 0x2c) = *(undefined4 *)(iVar2 + 0xf6c);
    }
    uVar3 = lv_display_get_inactive_time(0);
    if (2000 < uVar3) {
      iVar2 = *(int *)(iVar1 + 0x78);
      iVar7 = 0;
      if (iVar2 != 0) {
        do {
          if (iVar2 == 0) {
            iVar7 = iVar7 + 1;
            iVar5 = iRam0000002c;
            if (iVar7 == 4) goto LAB_004d235c;
          }
          else if (*(int *)(iVar2 + 0x50) != 0) {
            piVar4 = (int *)(*(int *)(iVar2 + 0x50) + iVar7 * 0xc);
            iVar5 = *piVar4;
            if ((iVar5 != 0) && (piVar4[1] != 0)) {
              lv_obj_remove_state(iVar5,1);
              lv_obj_add_flag(*(undefined4 *)
                               (*(int *)(*(int *)(iVar1 + 0x78) + 0x50) + iVar7 * 0xc + 4),1);
              iVar2 = *(int *)(iVar1 + 0x78);
            }
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 != 4);
        iVar5 = *(int *)(iVar2 + 0x2c);
LAB_004d235c:
        if ((iVar5 != -1) && (*(int *)(iVar2 + 0x50) != 0)) {
          piVar4 = (int *)(iVar5 * 0xc + *(int *)(iVar2 + 0x50));
          iVar2 = *piVar4;
          if ((iVar2 != 0) && (piVar4[1] != 0)) {
            lv_obj_add_state(iVar2,1);
            lv_obj_remove_flag(*(undefined4 *)
                                (*(int *)(*(int *)(iVar1 + 0x78) + 0x2c) * 0xc +
                                 *(int *)(*(int *)(iVar1 + 0x78) + 0x50) + 4),1);
          }
        }
      }
    }
  }
  return;
}



// === zoffset_update_observer_cb @ 004d247c ===

void zoffset_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = lv_observer_get_target();
  if (iVar1 == 0) {
    return;
  }
  if ((*(int *)(iVar1 + 0x7c) != 0) && (iVar4 = *(int *)(*(int *)(iVar1 + 0x7c) + 0x4c), iVar4 != 0)
     ) {
    iVar2 = getodin();
    lv_label_set_text_fmt
              (iVar4,"%0.3lfmm",*(undefined4 *)(iVar2 + 0x2340),*(undefined4 *)(iVar2 + 0x2344));
  }
  uVar3 = *(undefined4 *)(iVar1 + 0x38);
  iVar1 = getodin();
  lv_label_set_text_fmt
            (uVar3,"%0.3lfmm",*(undefined4 *)(iVar1 + 0x2340),*(undefined4 *)(iVar1 + 0x2344));
  iVar1 = getodin();
  lv_subject_set_int(iVar1 + 0x2bd0,1);
  return;
}



// === page_tune_filament_update_btn_state @ 004d4e54 ===

void page_tune_filament_update_btn_state(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = page_obj_pop(5);
  iVar2 = lv_obj_has_state(*(undefined4 *)(iVar1 + 0x6c),0x80);
  iVar3 = lv_obj_has_state(*(undefined4 *)(iVar1 + 0x70),0x80);
  if (param_1 == 0) {
    if (iVar2 == 0) {
      lv_obj_add_state(*(undefined4 *)(iVar1 + 0x6c),0x80);
      if (iVar3 == 0) {
        uVar4 = *(undefined4 *)(iVar1 + 0x70);
        goto LAB_004d4ed4;
      }
    }
    else if (iVar3 == 0) {
      uVar4 = *(undefined4 *)(iVar1 + 0x70);
LAB_004d4ed4:
      lv_obj_add_state(uVar4,0x80);
      return;
    }
  }
  else {
    if (iVar2 != 0) {
      lv_obj_remove_state(*(undefined4 *)(iVar1 + 0x6c),0x80);
    }
    if (iVar3 != 0) {
      lv_obj_remove_state(*(undefined4 *)(iVar1 + 0x70),0x80);
      return;
    }
  }
  return;
}



// === page_tune_filament_update_cont_progress_state @ 004d503c ===

void page_tune_filament_update_cont_progress_state(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18 [2];
  
  iVar1 = page_obj_pop(5);
  iVar2 = lv_obj_has_flag(*(undefined4 *)(iVar1 + 0x34),1);
  if (param_1 == 0) {
    lv_color_white(local_18);
  }
  else {
    lv_color_make(local_18,0xfa,0x6d,0x31);
  }
  if (iVar2 == 0) {
    lv_obj_set_style_text_color(*(undefined4 *)(iVar1 + 0x50),local_18[0],0);
    lv_obj_set_style_text_color(*(undefined4 *)(iVar1 + 0x58),local_18[0],0);
    uVar3 = *(undefined4 *)(iVar1 + 0x5c);
  }
  else {
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x34),1);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x38),1);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x3c),1);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x40),1);
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x4c),1);
    uVar3 = *(undefined4 *)(iVar1 + 0x50);
    lv_color_make(&local_1c,0xfa,0x6d,0x31);
    lv_obj_set_style_text_color(uVar3,local_1c,0);
    uVar3 = *(undefined4 *)(iVar1 + 0x58);
    lv_color_make(&local_20,0xfa,0x6d,0x31);
    lv_obj_set_style_text_color(uVar3,local_20,0);
    uVar3 = *(undefined4 *)(iVar1 + 0x5c);
  }
  if (param_1 == 0) {
    lv_obj_add_flag();
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x60),1);
    return;
  }
  lv_obj_remove_flag(uVar3,1);
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x60),1);
  return;
}



// === page_tune_filament_update_timeline @ 004d51b4 ===

void page_tune_filament_update_timeline(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  float fVar9;
  float fVar10;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_38;
  
  local_38 = 0;
  iVar2 = page_obj_pop(5);
  iVar3 = *(int *)(iVar2 + 0x90);
  puVar7 = *(undefined4 **)(iVar2 + 0x80);
  if (iVar3 == 0) {
    iVar3 = lv_obj_has_flag(*(undefined4 *)(iVar2 + 0x78),1);
    iVar5 = lv_obj_has_flag(*(undefined4 *)(iVar2 + 0x7c),1);
    if (iVar5 == 0) {
      lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x7c),1);
    }
    if (iVar3 == 0) {
      iVar3 = *(int *)(iVar2 + 0x90);
    }
    else {
      lv_obj_remove_flag(*(undefined4 *)(iVar2 + 0x78),1);
      iVar3 = *(int *)(iVar2 + 0x90);
    }
  }
  if (iVar3 == 1) {
    iVar5 = lv_obj_has_flag(*(undefined4 *)(iVar2 + 0x78),1);
    iVar3 = lv_obj_has_flag(*(undefined4 *)(iVar2 + 0x7c),1);
    if (iVar5 == 0) {
      local_40 = iVar3;
      lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x78),1);
      iVar3 = local_40;
    }
    if (iVar3 == 0) {
      puVar7 = *(undefined4 **)(iVar2 + 0x84);
    }
    else {
      lv_obj_remove_flag(*(undefined4 *)(iVar2 + 0x7c),1);
      puVar7 = *(undefined4 **)(iVar2 + 0x84);
    }
    iVar2 = 3;
    iVar3 = 4;
  }
  else {
    iVar2 = 2;
    iVar3 = 3;
  }
  iVar5 = 0;
  bVar1 = param_1 < 0;
  puVar6 = puVar7;
  do {
    uVar8 = *puVar6;
    if (bVar1) {
      lv_color_make(&local_4c,0x83,0x86,0x8b);
      lv_obj_set_style_bg_color(uVar8,local_4c,0);
      uVar8 = lv_obj_get_parent(*puVar6);
      uVar4 = lv_obj_get_child(uVar8,0xffffffff);
      lv_color_make(&local_50,0x6a,0x70,0x7d);
      uVar8 = local_50;
    }
    else {
      lv_color_make(&local_44,0x17,0xcc,0x5f);
      lv_obj_set_style_bg_color(uVar8,local_44,0);
      uVar8 = lv_obj_get_parent(*puVar6);
      uVar4 = lv_obj_get_child(uVar8,0xffffffff);
      lv_color_white(&local_48);
      uVar8 = local_48;
    }
    iVar5 = iVar5 + 1;
    puVar6 = puVar6 + 1;
    lv_obj_set_style_text_color(uVar4,uVar8,0);
    bVar1 = param_1 < iVar5;
  } while (iVar3 != iVar5);
  uVar8 = lv_obj_get_parent(*puVar7);
  uVar8 = lv_obj_get_parent(uVar8);
  uVar8 = lv_obj_get_child(uVar8,0);
  local_38 = 0;
  fVar9 = (float)iVar2;
  fVar10 = DAT_0058a8d0;
  lv_obj_set_style_bg_main_stop(uVar8,(int)(((float)param_1 / fVar9) * DAT_0058a8d0),0);
  fVar9 = ((float)(param_1 + 1) / fVar9) * fVar10;
  iVar2 = 0xff;
  if (fVar9 <= fVar10) {
    iVar2 = (int)fVar9;
  }
  local_38 = 0;
  lv_obj_set_style_bg_grad_stop(uVar8,iVar2,0);
  return;
}



// === update_extruder_retract_tip @ 004d5784 ===

void update_extruder_retract_tip(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  char acStack_110 [260];
  
  memset(acStack_110,0,0x100);
  uVar1 = lv_i18n_get_text("TipsFilament");
  iVar2 = getodin();
  snprintf(acStack_110,0x100,"%s %d%s",uVar1,*(undefined4 *)(iVar2 + 0xe58),&DAT_00612f88);
  lv_label_set_text(*(undefined4 *)(param_1 + 0x4c),acStack_110);
  return;
}



// === fan_speed_update_observer_cb @ 004d6e78 ===

void fan_speed_update_observer_cb(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  iVar1 = lv_observer_get_target();
  uVar2 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x50),0xffffffff);
  iVar3 = getodin();
  dVar4 = DAT_00614dc0;
  dVar5 = DAT_00613d68;
  lv_label_set_text_fmt
            (uVar2,&DAT_00613bf0,(int)(*(double *)(iVar3 + 0x22a0) * DAT_00613d68 + DAT_00614dc0));
  uVar2 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x58),0xffffffff);
  iVar3 = getodin();
  lv_label_set_text_fmt(uVar2,&DAT_00613bf0,(int)(*(double *)(iVar3 + 0x22b0) * dVar5 + dVar4));
  uVar2 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x54),0xffffffff);
  iVar3 = getodin();
  lv_label_set_text_fmt(uVar2,&DAT_00613bf0,(int)(*(double *)(iVar3 + 0x22c0) * dVar5 + dVar4));
  iVar3 = getodin();
  if (*(char *)(iVar3 + 0x2786) == '\0') {
    lv_obj_add_flag();
    return;
  }
  lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x54),1);
  return;
}



// === widget_auth_wifi_destructor @ 004d8400 ===

void widget_auth_wifi_destructor(void)

{
  return;
}



// === icon_password_clear_event_handler @ 004d862c ===

void icon_password_clear_event_handler(void)

{
  int iVar1;
  char *__src;
  
  iVar1 = lv_event_get_user_data();
  lv_textarea_set_text(*(undefined4 *)(iVar1 + 0x3c),"");
  __src = (char *)lv_textarea_get_text(*(undefined4 *)(iVar1 + 0x3c));
  strcpy((char *)(iVar1 + 0x18d),__src);
  return;
}



// === widget_auth_wifi_constructor @ 004d86f0 ===

/* WARNING: Removing unreachable block (ram,0x004d8c14) */
/* WARNING: Removing unreachable block (ram,0x004d892c) */
/* WARNING: Removing unreachable block (ram,0x004d8be0) */
/* WARNING: Removing unreachable block (ram,0x004d8d48) */

void widget_auth_wifi_constructor(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  *(undefined1 *)(param_2 + 0x4c) = 0;
  *(undefined4 *)(param_2 + 0x38) = 0;
  *(undefined4 *)(param_2 + 0x34) = 0;
  *(undefined4 *)(param_2 + 0x48) = 0;
  lv_obj_set_size(param_2,0x20000064);
  uVar1 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_left(param_2,uVar1,0);
  lv_obj_set_style_pad_right(param_2,uVar1,0);
  lv_obj_set_style_pad_top(param_2,uVar1,0);
  lv_obj_set_style_pad_bottom(param_2,uVar1,0);
  lv_obj_set_style_radius(param_2,0,0);
  lv_obj_set_style_border_width(param_2,0,0);
  lv_color_make(&local_3c,0x23,0x24,0x26);
  lv_obj_set_style_bg_color(param_2,local_3c,0);
  lv_obj_set_style_bg_opa(param_2,0xff,0);
  lv_obj_set_flex_flow(param_2,1);
  lv_obj_set_flex_align(param_2,5,0,5);
  lv_obj_set_style_pad_row(param_2,10,0);
  uVar1 = lv_obj_create(param_2);
  lv_obj_remove_style_all(uVar1);
  lv_obj_set_size(uVar1,0x20000064,0x3fffffff);
  local_38 = &font_icons;
  uVar2 = create_button(uVar1,0,&DAT_00613430,DAT_0084d934);
  *(undefined4 *)(param_2 + 0x2c) = uVar2;
  lv_obj_remove_style_all(uVar2);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  iVar4 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_size(uVar2,iVar3 << 2,iVar4 * 3);
  uVar5 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_left(uVar2,uVar5,0);
  lv_obj_set_style_pad_right(uVar2,uVar5,0);
  lv_obj_set_style_pad_top(uVar2,uVar5,0);
  lv_obj_set_style_pad_bottom(uVar2,uVar5,0);
  lv_palette_main(&local_40,0x12);
  lv_obj_set_style_text_color(uVar2,local_40,0);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_align(uVar2,7,iVar3 / 2,0);
  lv_obj_add_event_cb(uVar2,btn_cancel_event_handler,10,param_2);
  uVar2 = lv_i18n_get_text("NetworkConnect");
  uVar5 = getcxfont(7);
  uVar1 = create_label(uVar1,uVar2,0,uVar5);
  *(undefined4 *)(param_2 + 0x48) = uVar1;
  lv_obj_set_size(uVar1,0x3fffffff);
  lv_obj_set_style_text_align(uVar1,2,0);
  lv_obj_center(uVar1);
  uVar1 = lv_obj_create(param_2);
  *(undefined4 *)(param_2 + 0x30) = uVar1;
  lv_obj_remove_style_all(uVar1);
  lv_obj_set_size(uVar1,0x20000064,0x3fffffff);
  uVar1 = lv_obj_create(param_2);
  lv_obj_remove_style_all(uVar1);
  lv_obj_set_size(uVar1,0x20000064,0x3fffffff);
  lv_color_make(&local_44,0x4c,0x50,0x57);
  lv_obj_set_style_bg_color(uVar1,local_44,0);
  lv_obj_set_style_bg_opa(uVar1,0xff,0);
  lv_obj_set_style_border_width(uVar1,1,0);
  lv_color_make(&local_48,0x88,0x89,0x89);
  lv_obj_set_style_border_color(uVar1,local_48,0);
  lv_obj_set_style_radius(uVar1,4,0);
  uVar2 = lv_textarea_create(uVar1);
  *(undefined4 *)(param_2 + 0x3c) = uVar2;
  lv_obj_set_size(uVar2,0x20000058,0x3fffffff);
  lv_obj_set_style_bg_opa(uVar2,0,0);
  lv_obj_set_style_border_width(uVar2,0,0);
  lv_obj_remove_flag(uVar2,0x10);
  uVar5 = getcxfont(7);
  lv_obj_set_style_text_font(uVar2,uVar5,0);
  lv_obj_set_style_radius(uVar2,0,0);
  lv_textarea_set_one_line(uVar2,1);
  lv_textarea_set_max_length(uVar2,0x40);
  lv_textarea_set_password_mode(uVar2,1);
  uVar5 = lv_i18n_get_text("PasswordPlaceholder");
  lv_textarea_set_placeholder_text(uVar2,uVar5);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_right(uVar2,iVar3 * 6,0);
  lv_obj_add_event_cb(uVar2,ta_event_handler,10,param_2);
  lv_obj_align(uVar2,7,0,0);
  lv_group_focus_obj(uVar2);
  uVar5 = create_label(uVar1,&DAT_00613428,0,local_38[9]);
  lv_color_make(&local_4c,0x6a,0x70,0x7d);
  lv_obj_set_style_text_color(uVar5,local_4c,0);
  lv_obj_set_size(uVar5,0x3fffffff);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_top(uVar5,iVar3 / 4,0);
  lv_obj_set_style_pad_bottom(uVar5,iVar3 / 4,0);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_left(uVar5,iVar3 / 2,0);
  lv_obj_set_style_pad_right(uVar5,iVar3 / 2,0);
  uVar6 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_left(uVar5,uVar6,0);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  local_2c = 0;
  lv_obj_align(uVar5,8,(int)((double)-iVar3 * DAT_00612550 + 0.0),0);
  lv_obj_set_style_text_align(uVar5,2,0);
  lv_obj_add_flag(uVar5,2);
  lv_obj_add_event_cb(uVar5,icon_password_clear_event_handler,10,param_2);
  uVar1 = create_label(uVar1,&DAT_00616098,0,local_38[9]);
  *(undefined4 *)(param_2 + 0x40) = uVar1;
  lv_color_make(&local_50,0x6a,0x70,0x7d);
  lv_obj_set_style_text_color(uVar1,local_50,0);
  lv_obj_add_flag(uVar1,2);
  lv_obj_set_ext_click_area(uVar1,0x10);
  iVar3 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_align(uVar1,8,-iVar3 / 2,0);
  lv_obj_add_event_cb(uVar1,eye_event_handler,10,param_2);
  uVar1 = lv_obj_create(param_2);
  lv_obj_remove_style_all(uVar1);
  lv_obj_set_flex_grow(uVar1,1);
  uVar1 = lv_obj_create(param_2);
  lv_obj_remove_style_all(uVar1);
  lv_obj_set_size(uVar1,0x20000064,0x20000045);
  lv_obj_add_flag(uVar1,0x40000);
  lv_obj_add_flag(uVar1,0x100000);
  lv_obj_align(uVar1,5,0,0);
  lv_obj_remove_flag(uVar1,2);
  iVar3 = create_keyboard(uVar1);
  *(int *)(param_2 + 0x44) = iVar3;
  widget_keyboard_set_textarea(iVar3,uVar2);
  lv_obj_add_event_cb(*(undefined4 *)(iVar3 + 0x2c),btnm_event_cb,1,param_2);
  return;
}



// === widget_auth_wifi_create @ 004d8e58 ===

undefined4 widget_auth_wifi_create(void)

{
  undefined4 uVar1;
  
  uVar1 = lv_screen_active();
  uVar1 = lv_obj_class_create_obj(widget_auth_wifi_class,uVar1);
  lv_obj_class_init_obj(uVar1);
  return uVar1;
}



// === widget_auth_wifi_set_title @ 004d8e94 ===

void widget_auth_wifi_set_title(int param_1)

{
  if (*(int *)(param_1 + 0x48) != 0) {
    lv_label_set_text();
    return;
  }
  return;
}



// === widget_auth_wifi_set_param @ 004d8eb0 ===

/* WARNING: Removing unreachable block (ram,0x004d8fb8) */

undefined4 widget_auth_wifi_set_param(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  
  uVar7 = *(undefined4 *)(param_1 + 0x30);
  if (param_2 == (undefined4 *)0x0) {
    uVar7 = lv_textarea_create(uVar7);
    *(undefined4 *)(param_1 + 0x34) = uVar7;
    lv_obj_set_size(uVar7,0x20000064,0x3fffffff);
    uVar3 = getcxfont(7);
    lv_obj_set_style_text_font(uVar7,uVar3,0);
    lv_obj_set_style_radius(uVar7,0,0);
    lv_textarea_set_one_line(uVar7,1);
    lv_textarea_set_max_length(uVar7,0x20);
    uVar3 = lv_i18n_get_text("SSIDPlaceholder");
    lv_textarea_set_placeholder_text(uVar7,uVar3);
    lv_obj_add_event_cb(uVar7,ta_event_handler,10,param_1);
    lv_group_focus_obj(uVar7);
    widget_keyboard_set_textarea(*(undefined4 *)(param_1 + 0x44),uVar7);
    return 0;
  }
  puVar1 = (undefined4 *)(param_1 + 0x4d);
  puVar6 = param_2 + 0x60;
  do {
    uVar5 = param_2[1];
    uVar3 = param_2[3];
    uVar4 = param_2[2];
    *puVar1 = *param_2;
    puVar1[1] = uVar5;
    puVar1[2] = uVar4;
    param_2 = param_2 + 4;
    puVar1[3] = uVar3;
    puVar1 = puVar1 + 4;
  } while (param_2 != puVar6);
  uVar3 = lv_i18n_get_text("SSIDPlaceholder");
  uVar4 = getcxfont(7);
  uVar7 = create_label(uVar7,uVar3,0,uVar4);
  *(undefined4 *)(param_1 + 0x38) = uVar7;
  lv_obj_align(uVar7,7,0,0);
  lv_label_set_text(*(undefined4 *)(param_1 + 0x38),param_1 + 0x8d);
  lv_obj_add_state(*(undefined4 *)(param_1 + 0x38),0x80);
  iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_size(uVar7,0x20000064,iVar2 * 3);
  iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
  lv_obj_set_style_pad_top(uVar7,iVar2 / 2,0);
  uVar3 = getcxfont(7);
  lv_obj_set_style_text_font(uVar7,uVar3,0);
  lv_obj_set_style_text_align(uVar7,1,0);
  return 0;
}



// === widget_keyboard_destructor @ 004da590 ===

void widget_keyboard_destructor(void)

{
  return;
}



// === widget_keyboard_constructor @ 004da900 ===

void widget_keyboard_constructor(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_18 [2];
  
  lv_obj_remove_flag(param_2,2);
  uVar1 = lv_keyboard_create(param_2);
  lv_obj_update_layout(param_2);
  lv_obj_add_flag(uVar1,0x100000);
  iVar2 = lv_obj_get_height(param_2);
  lv_obj_set_size(uVar1,0x20000064,iVar2 + -0x3c);
  lv_obj_align(uVar1,5,0,0);
  *(undefined4 *)(param_2 + 0x2c) = uVar1;
  lv_keyboard_set_map(uVar1,0,kb_map_lc,kb_ctrl_lcuc_map);
  lv_keyboard_set_map(uVar1,1,kb_map_uc,kb_ctrl_lcuc_map);
  lv_keyboard_set_map(uVar1,2,kb_map_num,kb_ctrl_num_map);
  lv_keyboard_set_mode(uVar1,0);
  lv_keyboard_set_popovers(uVar1,1);
  lv_obj_set_style_bg_opa(uVar1,0,0);
  lv_obj_set_style_pad_left(uVar1,0,0);
  lv_obj_set_style_pad_right(uVar1,0,0);
  lv_obj_set_style_pad_top(uVar1,0,0);
  lv_obj_set_style_pad_bottom(uVar1,0,0);
  lv_color_hex(local_18,0x4c5057);
  lv_obj_set_style_bg_color(uVar1,local_18[0],0x50000);
  lv_obj_set_style_radius(uVar1,4,0x50000);
  uVar3 = getcxfont(6);
  lv_obj_set_style_text_font(uVar1,uVar3,0x50000);
  lv_obj_add_flag(uVar1,0x80000);
  lv_obj_add_event_cb(uVar1,draw_event_cb,0x22,param_2);
  lv_obj_remove_event(uVar1,0);
  lv_obj_add_event_cb(uVar1,btnm_event_cb,0,param_2);
  return;
}



// === create_keyboard @ 004daad4 ===

undefined4 create_keyboard(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = lv_obj_class_create_obj(widget_keyboard_class,param_1);
  lv_obj_class_init_obj(uVar1);
  return uVar1;
}



// === widget_keyboard_set_textarea @ 004dab08 ===

void widget_keyboard_set_textarea(int param_1,undefined4 param_2)

{
  lv_keyboard_set_textarea(*(undefined4 *)(param_1 + 0x2c));
  lv_textarea_set_accepted_chars
            (param_2,
             "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM,./;\'[]\\`-=~!@#$%^&*()_+{}|:\"<>? "
            );
  return;
}



// === widget_update_range_tip @ 004db4b0 ===

void widget_update_range_tip(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 local_18 [2];
  
  lv_obj_clean(*(undefined4 *)(param_1 + 0x3c));
  uVar1 = lv_label_create(*(undefined4 *)(param_1 + 0x3c));
  lv_color_make(local_18,0x17,0xcc,0x5f);
  lv_obj_set_style_text_color(uVar1,local_18[0],0);
  uVar2 = getcxfont(6);
  lv_obj_set_style_text_font(uVar1,uVar2,0);
  lv_label_set_text_fmt
            (uVar1," %d~%d",*(undefined4 *)(param_1 + 0x48),*(undefined4 *)(param_1 + 0x4c));
  lv_obj_set_width(*(undefined4 *)(param_1 + 0x3c),0x3fffffff);
  lv_obj_update_layout(*(undefined4 *)(param_1 + 0x3c));
  uVar2 = lv_obj_get_width(*(undefined4 *)(param_1 + 0x3c));
  lv_obj_set_width(*(undefined4 *)(param_1 + 0x3c),0x20000064);
  lv_obj_align(uVar1,7,uVar2,0);
  lv_obj_remove_flag(*(undefined4 *)(param_1 + 0x38),1);
  lv_obj_add_flag(*(undefined4 *)(param_1 + 0x30),1);
  return;
}



// === radiogroup_display_update.part.0 @ 004db80c ===

void radiogroup_display_update_part_0(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = *(int *)(param_1 + 0x38);
  if (0 < iVar2) {
    iVar4 = 0;
    do {
      if (*(int *)(param_1 + 0x50) != 0) {
        piVar1 = (int *)(*(int *)(param_1 + 0x50) + iVar4 * 0xc);
        iVar3 = *piVar1;
        if ((iVar3 != 0) && (piVar1[1] != 0)) {
          lv_obj_remove_state(iVar3,1);
          lv_obj_add_flag(*(undefined4 *)(*(int *)(param_1 + 0x50) + iVar4 * 0xc + 4),1);
          iVar2 = *(int *)(param_1 + 0x38);
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar2);
  }
  if ((*(int *)(param_1 + 0x2c) != -1) && (*(int *)(param_1 + 0x50) != 0)) {
    piVar1 = (int *)(*(int *)(param_1 + 0x2c) * 0xc + *(int *)(param_1 + 0x50));
    iVar2 = *piVar1;
    if ((iVar2 != 0) && (piVar1[1] != 0)) {
      lv_obj_add_state(iVar2,1);
      lv_obj_remove_flag(*(undefined4 *)
                          (*(int *)(param_1 + 0x2c) * 0xc + *(int *)(param_1 + 0x50) + 4),1);
      return;
    }
  }
  return;
}



// === radiogroup_display_update @ 004db924 ===

void radiogroup_display_update(int param_1)

{
  if ((param_1 != 0) && (0 < *(int *)(param_1 + 0x38))) {
    radiogroup_display_update_part_0();
    return;
  }
  return;
}



// === api_fetch_oneshot_token @ 004dda8c ===

undefined4 api_fetch_oneshot_token(void)

{
  cgi_GetAccessOneShotToken();
  return 0;
}



// === dev_selftest_send_update_observer_cb @ 004df4c0 ===

void dev_selftest_send_update_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  char local_20 [20];
  
  iVar1 = lv_subject_get_int(param_2);
  if ((iVar1 != 0) && (iVar2 = lv_observer_get_target(param_1), *(char *)(iVar2 + 0x52) != '\0')) {
    if (iVar1 == 1) {
      if (*(int *)(iVar2 + 0x54) != 0) {
        lv_timer_delete();
      }
      *(undefined4 *)(iVar2 + 0x54) = 0;
      *(undefined1 *)(iVar2 + 0x52) = 0;
      iVar1 = strcmp(*(char **)(*(int *)(iVar2 + 0x40) * 0x54 + *(int *)(iVar2 + 0x44)),
                     "InputShaping");
      if (iVar1 == 0) {
        iVar1 = getodin();
        iVar6 = *(int *)(iVar2 + 0x40);
        iVar5 = *(int *)(iVar2 + 0x44);
        *(undefined4 *)(iVar1 + 0x1ee8) = 1;
        uVar4 = ws_run_cmd("cx_printer_gcode_script",0,"%s",iVar6 * 0x54 + iVar5 + 4);
        iVar1 = *(int *)(iVar2 + 0x40) * 0x54 + *(int *)(iVar2 + 0x44);
        ws_reqcb_cache_add(uVar4,*(undefined4 *)(iVar1 + 0x44),iVar1 + 0x4c,0x5dc);
      }
    }
    else if (iVar1 == 2) {
      if (*(int *)(iVar2 + 0x54) != 0) {
        lv_timer_delete();
      }
      *(undefined4 *)(iVar2 + 0x54) = 0;
      *(undefined1 *)(iVar2 + 0x52) = 0;
      local_20[0] = '\0';
      local_20[1] = '\0';
      local_20[2] = '\0';
      local_20[3] = '\0';
      local_20[4] = '\0';
      local_20[5] = '\0';
      local_20[6] = '\0';
      local_20[7] = '\0';
      local_20[8] = '\0';
      local_20[9] = '\0';
      strncpy(local_20,device_selftest_step_error + *(int *)(iVar2 + 0x40) * 10,9);
      sVar3 = strlen(local_20);
      service_gui_request(0xf,local_20,sVar3 + 1);
      iVar1 = *(int *)(iVar2 + 0x40) * 0x54 + *(int *)(iVar2 + 0x44);
      *(undefined1 *)(iVar1 + 0x52) = 0;
      *(undefined1 *)(iVar1 + 0x50) = 1;
      page_dev_selftest_draw_items(iVar2);
    }
  }
  return;
}



// === start_print_verify_stop_print_cb @ 004e0ff0 ===

void start_print_verify_stop_print_cb(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_event_get_user_data();
  iVar2 = *(int *)(iVar1 + 0x2c);
  widget_alert_close(iVar1);
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x288) = 0;
  }
  return;
}



// === start_print_verify_continue_print_cb @ 004e123c ===

void start_print_verify_continue_print_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = lv_event_get_user_data();
  if (*(int *)(iVar1 + 0x2c) != 0) {
    *(undefined4 *)(*(int *)(iVar1 + 0x2c) + 0x288) = 0;
    iVar2 = getodin();
    uVar3 = *(undefined4 *)(iVar1 + 0x2c);
    *(undefined1 *)(iVar2 + 0x2760) = 1;
    info_start_print_handler(uVar3);
    return;
  }
  return;
}



// === update_history_file_info @ 004e1f40 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x004e207c) */
/* WARNING: Removing unreachable block (ram,0x004e20a0) */

void update_history_file_info(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  double dVar7;
  undefined8 uVar8;
  
  iVar1 = page_obj_pop(0xd);
  iVar2 = getodin();
  uVar5 = *(undefined4 *)(param_1 + 0x180);
  uVar4 = *(undefined4 *)(param_1 + 0x184);
  uVar8 = *(undefined8 *)(param_1 + 0x148);
  uVar6 = *(undefined8 *)(param_1 + 0x118);
  uVar3 = *(undefined4 *)(iVar1 + 0x260);
  *(undefined1 *)(iVar2 + 0x2bc9) = 0;
  *(int *)(iVar1 + 0x30) = param_1 + 9;
  *(int *)(iVar1 + 0x234) = param_1 + 0x150;
  *(undefined4 *)(iVar1 + 0x248) = uVar5;
  *(undefined4 *)(iVar1 + 0x24c) = uVar4;
  *(undefined8 *)(iVar1 + 0x238) = uVar8;
  *(undefined8 *)(iVar1 + 0x240) = uVar6;
  lv_label_set_text(uVar3,param_1 + 9);
  lv_label_set_text(*(undefined4 *)(iVar1 + 0x264),*(undefined4 *)(iVar1 + 0x234));
  if (**(char **)(iVar1 + 0x234) == '\0') {
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x264),1);
    uVar3 = *(undefined4 *)(iVar1 + 0x248);
  }
  else {
    uVar3 = *(undefined4 *)(iVar1 + 0x248);
  }
  lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x274),&DAT_00613450,uVar3);
  if (*(int *)(param_1 + 0x180) == 0) {
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x270),1);
    uVar3 = *(undefined4 *)(iVar1 + 0x24c);
  }
  else {
    uVar3 = *(undefined4 *)(iVar1 + 0x24c);
  }
  lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x26c),&DAT_00613450,uVar3);
  if (*(int *)(param_1 + 0x184) == 0) {
    lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x268),1);
  }
  dVar7 = *(double *)(iVar1 + 0x240);
  if (DAT_00696650 < dVar7 / DAT_00696650) {
    lv_label_set_text_fmt
              (*(undefined4 *)(iVar1 + 0x27c),"%dh%dmin",
               (int)((double)CONCAT44((int)dVar7,SUB84(dVar7,0)) / DAT_00696658),
               ((int)dVar7 % 0xe10) / 0x3c);
  }
  else {
    lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x27c),"%dmin",(int)(dVar7 / DAT_00696650));
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === update_print_again_file_info @ 004e2200 ===

/* WARNING: Control flow encountered bad instruction data */

void update_print_again_file_info(void)

{
  int iVar1;
  int iVar2;
  
  page_obj_pop(0xd);
  iVar1 = getodin();
  *(undefined1 *)(iVar1 + 0x2bc9) = 1;
  iVar1 = page_obj_pop(9);
  iVar2 = page_obj_pop(0xb);
  lv_obj_add_flag(*(undefined4 *)(iVar1 + 0x30),1);
  lv_obj_add_flag(*(undefined4 *)(iVar2 + 0x30),1);
  if (*(int *)(iVar2 + 0x34) != 0) {
    lv_obj_add_flag(*(int *)(iVar2 + 0x34),1);
  }
  iVar1 = lv_obj_get_child(iVar1,0);
  iVar2 = lv_obj_get_child(iVar2,0);
  if (*(int *)(iVar1 + 0xc0) != 0) {
    lv_obj_delete();
  }
  if (*(int *)(iVar2 + 0xc0) != 0) {
    lv_obj_delete();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === udisk_list_update_observer_cb @ 004e33dc ===

void udisk_list_update_observer_cb(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = lv_observer_get_target();
  iVar2 = getodin();
  pthread_mutex_lock((pthread_mutex_t *)(iVar2 + 0x36f4));
  page_files_pendrive_dropdown_create(uVar1);
  iVar2 = getodin();
  pthread_mutex_unlock((pthread_mutex_t *)(iVar2 + 0x36f4));
  return;
}



// === create_update_udisk_list @ 004e47e8 ===

/* WARNING: Removing unreachable block (ram,0x004e4a58) */

void create_update_udisk_list(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  double dVar7;
  undefined1 auStack_a0 [64];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  int local_48;
  char *local_44;
  int local_40;
  char *local_3c;
  undefined4 local_34;
  
  local_34 = 0;
  iVar1 = page_obj_pop(0x21);
  iVar2 = getodin();
  if (*(int *)(iVar2 + 0x2c98) < 5) {
    lv_obj_remove_flag(*(undefined4 *)(iVar1 + 0x38),0x10);
    lv_obj_set_flex_align(*(undefined4 *)(iVar1 + 0x38),2,2,5);
  }
  else {
    lv_obj_add_flag();
    lv_obj_set_flex_align(*(undefined4 *)(iVar1 + 0x38),0,2,5);
  }
  iVar3 = lv_obj_get_child_count(*(undefined4 *)(iVar1 + 0x38));
  iVar2 = iVar3 + -1;
  if (0 < iVar3) {
    do {
      while (iVar3 = lv_obj_get_child(*(undefined4 *)(iVar1 + 0x38),iVar2), iVar3 == 0) {
        iVar3 = iVar2 + -1;
        printf("Failed to get child at index %d\n",iVar2);
        iVar2 = iVar3;
        if (iVar3 == -1) goto LAB_004e48e0;
      }
      iVar2 = iVar2 + -1;
      lv_obj_delete(iVar3);
    } while (iVar2 != -1);
  }
LAB_004e48e0:
  local_34 = 0;
  local_48 = 0x4e0000;
  local_44 = "oot and retry.";
  local_3c = "videoinfo_export Udisk path=%s";
  dVar7 = DAT_00612550;
  iVar2 = getodin();
  uVar6 = 0;
  if (*(int *)(iVar2 + 0x2c98) != 0) {
    do {
      uVar4 = lv_obj_create(param_1);
      lv_obj_set_size(uVar4,0x62,0x3fffffff);
      lv_obj_remove_flag(uVar4,0x10);
      lv_color_make(&local_4c,0x60,0x62,0x66);
      lv_obj_set_style_bg_color(uVar4,local_4c,0);
      lv_obj_set_style_bg_opa(uVar4,0xcc,0);
      lv_obj_set_style_border_width(uVar4,1,0);
      lv_color_make(&local_50,0x60,0x62,0x66);
      lv_obj_set_style_border_color(uVar4,local_50,0);
      lv_obj_add_event_cb(uVar4,local_48 + 0x4d44,10,param_1);
      uVar5 = create_label(uVar4,local_44 + 0x33b8,0,DAT_0084d948);
      lv_color_make(&local_54,0xff,0xff,0xff);
      lv_obj_set_style_text_color(uVar5,local_54,0);
      lv_color_make(&local_58,0x74,0x74,0x74);
      lv_obj_set_style_bg_color(uVar5,local_58,0);
      iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
      lv_obj_align(uVar5,2,0,-iVar2 / 2);
      iVar2 = getodin();
      lv_snprintf(auStack_a0,0x40,"%s",*(int *)(iVar2 + 0x2c9c) + uVar6 * 0x100);
      uVar5 = getcxfont(4);
      uVar5 = create_label(uVar4,auStack_a0,0,uVar5);
      lv_obj_set_style_text_align(uVar5,1,0);
      iVar2 = lv_font_get_line_height(lv_font_montserrat_14);
      local_34 = 0;
      lv_obj_align_to(uVar5,uVar4,2,0,(int)((double)iVar2 * dVar7 + 0.0));
      if (uVar6 == 0) {
        iVar2 = getodin();
        snprintf((char *)(iVar1 + 0x144),0x100,"%s",*(undefined4 *)(iVar2 + 0x2c9c));
        local_40 = getodin();
        iVar2 = getodin();
        snprintf((char *)(iVar1 + 0x44),0x100,"%s/%s",local_40 + 0x2c34,
                 *(undefined4 *)(iVar2 + 0x2c9c));
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_settings_camera_videoinfo.c"
                   ,0x15e,"create_update_udisk_list",local_3c,(char *)(iVar1 + 0x44));
        lv_color_make(&local_5c,0x17,0xcc,0x5f);
        lv_obj_set_style_bg_color(uVar4,local_5c,0);
        lv_obj_set_style_bg_opa(uVar4,0x4c,0);
        lv_color_make(&local_60,0x17,0xcc,0x5f);
        lv_obj_set_style_border_color(uVar4,local_60,0);
      }
      uVar6 = uVar6 + 1;
      iVar2 = getodin();
    } while (uVar6 < *(uint *)(iVar2 + 0x2c98));
  }
  return;
}



// === udisk_list_update_observer_cb @ 004e4c84 ===

void udisk_list_update_observer_cb(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = lv_observer_get_target();
  iVar2 = lv_subject_get_int(param_2);
  if ((*(int *)(iVar1 + 0x38) != 0) && (iVar2 != 0)) {
    create_update_udisk_list();
    return;
  }
  return;
}



// === local_network_update_observer_cb @ 004e5cac ===

void local_network_update_observer_cb(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char acStack_50 [64];
  
  iVar1 = lv_observer_get_target();
  iVar2 = getodin();
  iVar2 = lv_subject_get_int(iVar2 + 0x3778);
  if (iVar2 != 0) {
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/pages/page_settings_local_network.c"
               ,0xd2,"local_network_update_observer_cb","===refresh local network data===\n");
    memset(acStack_50,0,0x40);
    uVar3 = lv_i18n_get_text("IpAddress");
    iVar2 = getodin();
    snprintf(acStack_50,0x40,"%s: %s",uVar3,iVar2 + 0x3714);
    lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x30),acStack_50);
    uVar3 = lv_i18n_get_text("Gateway");
    iVar2 = getodin();
    snprintf(acStack_50,0x40,"%s: %s",uVar3,iVar2 + 0x3734);
    lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x34),acStack_50);
    uVar3 = lv_i18n_get_text("SubnetMask");
    iVar2 = getodin();
    snprintf(acStack_50,0x40,"%s: %s",uVar3,iVar2 + 0x3724);
    lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x38),acStack_50);
    uVar3 = lv_i18n_get_text("DnsServer");
    iVar2 = getodin();
    snprintf(acStack_50,0x40,"%s: %s",uVar3,iVar2 + 0x3744);
    lv_label_set_text_fmt(*(undefined4 *)(iVar1 + 0x3c),acStack_50);
  }
  return;
}



// === get_total_time @ 004e6770 ===

/* WARNING: Removing unreachable block (ram,0x004e6794) */

int get_total_time(void)

{
  timespec local_10;
  
  clock_gettime(1,&local_10);
  return local_10.tv_sec * 1000 + local_10.tv_nsec / 1000000;
}



// === extcom_out_ota_cmd @ 004e8164 ===

undefined4 extcom_out_ota_cmd(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  
  puVar1 = *(undefined4 **)(param_1 + 4);
  msg_ipc = 1;
  DAT_0084da50 = 8;
  puVar3 = &DAT_0084da58;
  puVar8 = puVar1 + 0x40;
  do {
    uVar7 = *puVar1;
    uVar6 = puVar1[1];
    uVar5 = puVar1[2];
    uVar4 = puVar1[3];
    puVar1 = puVar1 + 4;
    *puVar3 = uVar7;
    puVar3[1] = uVar6;
    puVar3[2] = uVar5;
    puVar3[3] = uVar4;
    iVar2 = ipc_out_msgid;
    puVar3 = puVar3 + 4;
  } while (puVar1 != puVar8);
  *puVar3 = *puVar1;
  DAT_0084da54 = 0x104;
  iVar2 = msgsnd(iVar2,&msg_ipc,0x80c,0);
  if (iVar2 == -1) {
    perror("msgsnd failed\n");
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



// === extcom_in_ota_cmd @ 004e857c ===

undefined4 extcom_in_ota_cmd(int param_1)

{
  int iVar1;
  int iVar2;
  char local_18 [12];
  
  iVar2 = *(int *)(param_1 + 4);
  local_18[0] = '\x01';
  iVar1 = get_log_level("extcom",local_18);
  if (iVar1 != 0) {
    lv_log_add((int)local_18[0],0,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/extcom/extcom.c"
               ,0x1f1,"extcom_in_ota_cmd","[extcom] Received ota state\n");
  }
  local_18[0] = '\x01';
  iVar1 = get_log_level("extcom",local_18);
  if (iVar1 != 0) {
    lv_log_add((int)local_18[0],0,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/extcom/extcom.c"
               ,0x1f2,"extcom_in_ota_cmd","[extcom] status: %d\n",*(undefined4 *)(iVar2 + 0x100));
  }
  iVar1 = getodin();
  *(undefined4 *)(iVar1 + 0x1ff0) = *(undefined4 *)(iVar2 + 0x100);
  iVar1 = getodin();
  service_gui_request(0x1a,iVar1 + 0x1ff0,0x104);
  return 0;
}



// === update_errcode_to_slicer @ 004e8bcc ===

void update_errcode_to_slicer(char *param_1)

{
  int iVar1;
  ushort **ppuVar2;
  ushort *puVar3;
  uint uVar4;
  char local_18 [12];
  
  if (param_1 == (char *)0x0) {
    DAT_0084c8b4 = 0;
    DAT_0084c8b8 = 0;
    DAT_0084c8bc = 0;
    return;
  }
  iVar1 = find_fault_entry();
  if (iVar1 == 0) {
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/extcom/extcom.c"
               ,0x136,"update_errcode_to_slicer","error code not found =%s",param_1);
  }
  else {
    uVar4 = (uint)*param_1;
    local_18[0] = '\0';
    local_18[1] = '\0';
    local_18[2] = '\0';
    local_18[3] = '\0';
    local_18[4] = '\0';
    local_18[5] = '\0';
    local_18[6] = '\0';
    local_18[7] = '\0';
    if (uVar4 == 0) {
LAB_004e8c64:
      DAT_0084c8b8 = 0;
    }
    else {
      ppuVar2 = __ctype_b_loc();
      puVar3 = *ppuVar2;
      iVar1 = 0;
      do {
        param_1 = param_1 + 1;
        if ((puVar3[uVar4 & 0xff] & 0x800) != 0) {
          local_18[iVar1] = (char)uVar4;
          iVar1 = iVar1 + 1;
        }
        uVar4 = (uint)*param_1;
        if (uVar4 == 0) {
          if (iVar1 == 0) goto LAB_004e8c64;
          break;
        }
      } while (iVar1 != 7);
      DAT_0084c8b8 = strtol(local_18,(char **)0x0,10);
    }
    DAT_0084c8b4 = 200;
    DAT_0084c8bc = DAT_0084c8b8;
  }
  return;
}



// === extcom_cmd_timer_callback @ 004e9020 ===

void extcom_cmd_timer_callback(undefined4 param_1)

{
  screen_lightup(1);
  lv_timer_delete(param_1);
  return;
}



// === httpchunk_download_ota_image @ 004e9940 ===

undefined4 httpchunk_download_ota_image(int param_1)

{
  char *pcVar1;
  int iVar2;
  char *__s;
  undefined1 auStack_528 [520];
  undefined4 local_320;
  char local_318 [260];
  char acStack_214 [256];
  char acStack_114 [260];
  
  memset(auStack_528,0,0x210);
  __s = *(char **)(param_1 + 4);
  DAT_0084c8d0 = 1;
  service_mqtt_request(7,0,0);
  pcVar1 = rindex(__s,0x2f);
  if (pcVar1 == (char *)0x0) {
    pcVar1 = "ota.img";
  }
  else {
    pcVar1 = pcVar1 + 1;
  }
  memset(acStack_114,0,0x100);
  pcVar1 = (char *)pack_userdata_full_path(pcVar1,0);
  strncpy(acStack_114,pcVar1,0xff);
  local_320 = *(undefined4 *)(__s + 0x100);
  iVar2 = httpchunkdownload(__s,acStack_114,auStack_528,1,ota_progress_cb);
  if (iVar2 != 0) {
    DAT_0084c8d0 = 3;
    local_318[0] = '\0';
    local_318[1] = '\0';
    local_318[2] = '\0';
    local_318[3] = '\0';
    service_gui_request(0x11,local_318,4);
    service_gui_request(0x20,0,0);
    return 0;
  }
  DAT_0084c8d0 = 2;
  service_mqtt_request(7,0,0);
  memset(local_318,0,0x104);
  pcVar1 = (char *)pack_userdata_full_path(auStack_528,0);
  strncpy(local_318,pcVar1,0x100);
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/httpchunk/httpchunk.c"
             ,0x1f1,"httpchunk_download_ota_image","save the ota image file: %s\n",local_318);
  memset(acStack_214,0,0x100);
  snprintf(acStack_214,0x100,"%s/%s",path_userdata,auStack_528);
  rename(acStack_114,acStack_214);
  service_extcom_request(8,local_318,0x104);
  return 0;
}



// === ota_progress_cb @ 004e9e44 ===

undefined4
ota_progress_cb(int param_1,undefined4 param_2,int param_3,int param_4,uint param_5,int param_6)

{
  int iVar1;
  
  if (param_3 != 0 || param_4 != 0) {
    DAT_0084c8d0 = 1;
    iVar1 = __divdi3((int)((ulonglong)param_5 * 100),
                     param_6 * 100 + (int)((ulonglong)param_5 * 100 >> 0x20));
    if (iVar1 != DAT_0084c8cc) {
      DAT_0084c8cc = iVar1;
      if (*(int *)(param_1 + 0x208) == 1) {
        service_gui_request(0x11,&DAT_0084c8cc,4);
      }
      else if (*(int *)(param_1 + 0x208) == 2) {
        service_mqtt_request(7,0,0);
      }
    }
  }
  return 0;
}



// === update_mounted_dirs @ 004ebcd0 ===

int update_mounted_dirs(char *param_1,char *param_2)

{
  FILE *__stream;
  byte *pbVar1;
  char *pcVar2;
  int iVar3;
  FILE *pFVar4;
  size_t sVar5;
  undefined4 *puVar6;
  undefined ***pppuVar7;
  byte bVar8;
  undefined4 uVar9;
  undefined **ppuVar10;
  byte *pbVar11;
  undefined4 uVar12;
  undefined **ppuVar13;
  undefined4 uVar14;
  undefined **ppuVar15;
  int iVar16;
  byte local_ac0 [4];
  undefined4 local_abc [255];
  byte abStack_6c0 [512];
  char acStack_4c0 [512];
  char acStack_2c0 [512];
  undefined **local_c0 [7];
  undefined1 local_a1 [97];
  undefined **local_40;
  byte *local_3c;
  char *local_38;
  undefined **local_34;
  FILE *local_30;
  
  memset(acStack_2c0,0,0x200);
  __stream = popen("cat /proc/mounts |grep /media/creality","r");
  if (__stream != (FILE *)0x0) {
    local_40 = &PTR__handleLinearX1Attr_006a0000;
    iVar16 = 0;
    local_34 = DAT_006985d4;
    local_38 = "\n";
    while (pcVar2 = fgets(acStack_2c0,0x200,__stream), pcVar2 != (char *)0x0) {
      pbVar1 = (byte *)strstr(acStack_2c0,"/media/creality");
      if (pbVar1 != (byte *)0x0) {
        if (iVar16 == 4) {
          puts("Warning: too much udisk is mounted ");
          pclose(__stream);
          iVar3 = getodin();
          *(undefined4 *)(iVar3 + 0x3208) = 4;
          goto LAB_004ebf24;
        }
        bVar8 = *pbVar1;
        if ((bVar8 & 0xdf) == 0) {
          local_3c = local_ac0;
          iVar3 = 0;
        }
        else {
          local_3c = local_ac0;
          pbVar11 = local_3c + iVar16 * 0x100;
          iVar3 = 0;
          do {
            pbVar1 = pbVar1 + 1;
            *pbVar11 = bVar8;
            bVar8 = *pbVar1;
            iVar3 = iVar3 + 1;
            pbVar11 = pbVar11 + 1;
            if ((bVar8 & 0xdf) == 0) break;
          } while (iVar3 != 0x100);
        }
        pbVar1 = local_3c + iVar16 * 0x100;
        pbVar1[iVar3] = 0;
        snprintf(acStack_4c0,0x200,(char *)(local_40 + -0x1ea5),pbVar1);
        pFVar4 = popen(acStack_4c0,"r");
        pppuVar7 = local_c0 + iVar16 * 8;
        if (pFVar4 == (FILE *)0x0) {
          *pppuVar7 = local_34;
        }
        else {
          local_30 = pFVar4;
          pcVar2 = fgets((char *)abStack_6c0,0x200,pFVar4);
          pFVar4 = local_30;
          if (pcVar2 == (char *)0x0) {
            *pppuVar7 = DAT_006985d4;
          }
          else {
            sVar5 = strcspn((char *)abStack_6c0,local_38);
            local_3c[sVar5 + 0x400] = 0;
            strncpy((char *)pppuVar7,(char *)abStack_6c0,0x1f);
            pFVar4 = local_30;
            local_a1[iVar16 * 0x20] = 0;
          }
          pclose(pFVar4);
        }
        pcVar2 = strstr(acStack_2c0,param_1);
        if (pcVar2 != (char *)0x0) {
          strcpy(param_2,(char *)pbVar1);
        }
        printf("find no.%d udisk %s, size: %s\n",iVar16,pbVar1,pppuVar7);
        iVar16 = iVar16 + 1;
      }
    }
    pclose(__stream);
    iVar3 = getodin();
    *(int *)(iVar3 + 0x3208) = iVar16;
    if (iVar16 != 0) {
LAB_004ebf24:
      iVar3 = getodin();
      puVar6 = (undefined4 *)(iVar3 + 0x328c);
      pbVar1 = local_ac0;
      do {
        uVar14 = *(undefined4 *)(pbVar1 + 4);
        uVar12 = *(undefined4 *)(pbVar1 + 8);
        uVar9 = *(undefined4 *)(pbVar1 + 0xc);
        *puVar6 = *(undefined4 *)pbVar1;
        puVar6[1] = uVar14;
        puVar6[2] = uVar12;
        pbVar1 = pbVar1 + 0x10;
        puVar6[3] = uVar9;
        puVar6 = puVar6 + 4;
      } while (pbVar1 != abStack_6c0);
      iVar3 = getodin();
      puVar6 = (undefined4 *)(iVar3 + 0x320c);
      pppuVar7 = local_c0;
      do {
        ppuVar15 = pppuVar7[1];
        ppuVar13 = pppuVar7[2];
        ppuVar10 = pppuVar7[3];
        *puVar6 = *pppuVar7;
        puVar6[1] = ppuVar15;
        puVar6[2] = ppuVar13;
        pppuVar7 = pppuVar7 + 4;
        puVar6[3] = ppuVar10;
        puVar6 = puVar6 + 4;
      } while (pppuVar7 != &local_40);
      iVar3 = getodin();
      strcpy((char *)&DAT_0084cc28,(char *)(iVar3 + iVar16 * 0x100 + 0x318c));
      printf("udisk dir: [%s] total %d usb disk\n",&DAT_0084cc28,iVar16);
      iVar3 = getodin();
      lv_ll_clear(iVar3 + 0x4a0);
      iVar3 = getodin();
      pcVar2 = (char *)lv_ll_ins_head(iVar3 + 0x4a0);
      strcpy(pcVar2,(char *)&DAT_0084cc28);
      return iVar16;
    }
  }
  return 0;
}



// === get_tbsignstring @ 004f0140 ===

void get_tbsignstring(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4)

{
  byte bVar1;
  size_t n;
  byte *pbVar2;
  uchar auStack_138 [256];
  byte local_38 [36];
  
  local_38[0] = 0;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  local_38[4] = 0;
  local_38[5] = 0;
  local_38[6] = 0;
  local_38[7] = 0;
  local_38[8] = 0;
  local_38[9] = 0;
  local_38[10] = 0;
  local_38[0xb] = 0;
  local_38[0xc] = 0;
  local_38[0xd] = 0;
  local_38[0xe] = 0;
  local_38[0xf] = 0;
  local_38[0x10] = 0;
  local_38[0x11] = 0;
  local_38[0x12] = 0;
  local_38[0x13] = 0;
  local_38[0x14] = 0;
  local_38[0x15] = 0;
  local_38[0x16] = 0;
  local_38[0x17] = 0;
  local_38[0x18] = 0;
  local_38[0x19] = 0;
  local_38[0x1a] = 0;
  local_38[0x1b] = 0;
  local_38[0x1c] = 0;
  local_38[0x1d] = 0;
  local_38[0x1e] = 0;
  local_38[0x1f] = 0;
  memset(auStack_138,0,0x100);
  snprintf((char *)auStack_138,0x100,"%s%s%s",param_1,param_2,param_3);
  n = strlen((char *)auStack_138);
  pbVar2 = local_38;
  SHA256(auStack_138,n,local_38);
  do {
    bVar1 = *pbVar2;
    pbVar2 = pbVar2 + 1;
    sprintf(param_4,"%02x",(uint)bVar1);
    param_4 = param_4 + 2;
  } while (pbVar2 != local_38 + 0x20);
  return;
}



// === fetch_mqtt_token @ 004f0e6c ===

undefined4 fetch_mqtt_token(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char acStack_208 [256];
  undefined1 auStack_108 [68];
  undefined1 auStack_c4 [52];
  int local_90 [2];
  char *local_88;
  undefined4 local_84;
  int local_80;
  undefined4 local_7c;
  char *local_78;
  undefined4 local_74;
  int local_70;
  undefined4 local_6c;
  undefined *local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  int local_34;
  undefined4 local_2c;
  
  local_2c = 0;
  memset(acStack_208,0,0x100);
  iVar1 = getodin();
  iVar2 = getodin();
  local_60 = DAT_00699954;
  local_5c = DAT_00699958;
  local_58 = DAT_0069995c;
  local_54 = DAT_00699960;
  local_50 = DAT_00699964;
  local_4c = DAT_00699968;
  local_44 = DAT_00699970;
  local_48 = DAT_0069996c;
  iVar3 = getodin();
  local_40 = 0;
  local_3c = 0;
  local_40 = lv_malloc(1);
  local_3c = 0;
  uVar4 = get_cx_host();
  snprintf(acStack_208,0x100,"%s%s",uVar4,"/api/cxy/v2/device/registerDevice");
  get_randstring_constprop_1(auStack_c4);
  memset(auStack_108,0,0x41);
  get_tbsignstring(iVar1 + 0x14ec,auStack_c4,&local_60,auStack_108);
  uVar4 = cJSON_CreateObject();
  cJSON_AddNumberToObject(uVar4,"iotType",DAT_00699f70,DAT_00699f74);
  cJSON_AddStringToObject(uVar4,&PTR_DAT_00699914,iVar1 + 0x14ec);
  cJSON_AddStringToObject(uVar4,&DAT_00699918,auStack_108);
  cJSON_AddNumberToObject(uVar4,"type",(undefined4)DAT_00699f78,DAT_00699f78._4_4_);
  cJSON_AddStringToObject(uVar4,"printerName",iVar2 + 0x14a0);
  cJSON_AddStringToObject(uVar4,"factorySN",iVar3 + 0x15d8);
  uVar5 = cJSON_PrintUnformatted(uVar4);
  printf("postdata: %s\n",uVar5);
  cJSON_Delete(uVar4);
  uVar4 = init_public_hearder(0,auStack_c4);
  uVar4 = curl_slist_append(uVar4,"Content-Type: application/json; charset=UTF-8");
  iVar1 = httpPostRequest(acStack_208,uVar5,&local_40,uVar4);
  if (iVar1 != 0) {
    uVar4 = 0xffffffff;
    goto LAB_004f10c4;
  }
  uVar4 = 0xffffffff;
  if (local_3c == 0) goto LAB_004f10c4;
  uVar6 = cJSON_Parse(local_40);
  iVar1 = cJSON_GetObjectItem(uVar6,"code");
  uVar4 = 0xffffffff;
  if (iVar1 != 0) {
    if ((*(int *)(iVar1 + 0x14) == 0) && (iVar1 = cJSON_GetObjectItem(uVar6,"result"), iVar1 != 0))
    {
      local_38 = cJSON_GetObjectItem(iVar1,"tbToken");
      local_34 = cJSON_GetObjectItem(iVar1,"deviceName");
      iVar2 = cJSON_GetObjectItem(iVar1,&DAT_0069994c);
      if ((local_38 != 0) && ((local_34 != 0 && (iVar2 != 0)))) {
        local_70 = getodin();
        local_90[0] = local_70 + 6000;
        local_80 = local_70 + 0x17b1;
        local_70 = local_70 + 0x17f2;
        local_90[1] = 0x10;
        local_7c = 0x10;
        local_6c = 0x10;
        local_64 = 0x100;
        local_88 = "tbToken";
        local_84 = 0x41;
        local_78 = "deviceName";
        local_74 = 0x41;
        local_68 = &DAT_0069994c;
        extract_from_json(iVar1,local_90,3,0);
        dump_extracted_from_json(iVar1,local_90,3);
        iVar1 = getodin();
        save_iot_tb_info(iVar1 + 6000);
        uVar4 = 0;
        goto LAB_004f10bc;
      }
    }
    uVar4 = 0xffffffff;
  }
LAB_004f10bc:
  cJSON_Delete(uVar6);
LAB_004f10c4:
  lv_free(uVar5);
  lv_free(local_40);
  return uVar4;
}



// === update_work_state_to_gui @ 004f5048 ===

void update_work_state_to_gui(void)

{
  undefined4 local_10 [3];
  
  local_10[0] = 4;
  service_gui_request(0xd,local_10,4);
  return;
}



// === update_remote_model_str @ 004f5224 ===

void update_remote_model_str(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  uint uVar3;
  uint *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char cVar7;
  char cVar8;
  int iVar9;
  undefined4 *puVar10;
  uint uVar11;
  
  iVar9 = getodin();
  iVar9 = strcasecmp((char *)(iVar9 + 0x147c),"K1C");
  if (iVar9 == 0) {
LAB_004f52cc:
    iVar9 = getodin();
    *(undefined4 *)(iVar9 + 0x14a0) = DAT_00614250;
  }
  else {
    iVar9 = getodin();
    iVar9 = strcasecmp((char *)(iVar9 + 0x147c),"K1SE");
    if (iVar9 == 0) {
      iVar9 = getodin();
      puVar10 = &DAT_0061420c;
      uVar11 = DAT_0061420c;
    }
    else {
      iVar9 = getodin();
      iVar9 = strcasecmp((char *)(iVar9 + 0x147c),"K1");
      if (iVar9 != 0) {
        iVar9 = getodin();
        iVar9 = strcasecmp((char *)(iVar9 + 0x147c),"K1Max");
        if (iVar9 == 0) {
          iVar9 = getodin();
          uVar6 = s_CR_K1_Max_00698110._4_4_;
          uVar5 = s_CR_K1_Max_00698110._0_4_;
          uVar11 = iVar9 + 0x14a3U & 3;
          puVar4 = (uint *)((iVar9 + 0x14a3U) - uVar11);
          *puVar4 = *puVar4 & -1 << (uVar11 + 1) * 8 |
                    (uint)s_CR_K1_Max_00698110._0_4_ >> (3 - uVar11) * 8;
          cVar8 = s_CR_K1_Max_00698110[9];
          cVar7 = s_CR_K1_Max_00698110[8];
          uVar11 = iVar9 + 0x14a0U & 3;
          puVar4 = (uint *)((iVar9 + 0x14a0U) - uVar11);
          *puVar4 = *puVar4 & 0xffffffffU >> (4 - uVar11) * 8 | uVar5 << uVar11 * 8;
          *(undefined4 *)(iVar9 + 0x14a4) = uVar6;
          *(char *)(iVar9 + 0x14a8) = cVar7;
          *(char *)(iVar9 + 0x14a9) = cVar8;
          goto LAB_004f52e0;
        }
        iVar9 = getodin();
        iVar9 = strcasecmp((char *)(iVar9 + 0x147c),"ENDER3V3Plus");
        if (iVar9 == 0) {
          iVar9 = getodin();
          uVar1 = DAT_0069a518;
          uVar3 = DAT_0069a514;
          uVar11 = iVar9 + 0x14a3U & 3;
          puVar4 = (uint *)((iVar9 + 0x14a3U) - uVar11);
          *puVar4 = *puVar4 & -1 << (uVar11 + 1) * 8 | DAT_0069a514 >> (3 - uVar11) * 8;
          uVar11 = iVar9 + 0x14a0U & 3;
          puVar4 = (uint *)((iVar9 + 0x14a0U) - uVar11);
          *puVar4 = *puVar4 & 0xffffffffU >> (4 - uVar11) * 8 | uVar3 << uVar11 * 8;
          *(undefined1 *)(iVar9 + 0x14a4) = uVar1;
          goto LAB_004f52e0;
        }
        goto LAB_004f52cc;
      }
      iVar9 = getodin();
      puVar10 = &DAT_0069a50c;
      uVar11 = DAT_0069a50c;
    }
    uVar1 = *(undefined1 *)(puVar10 + 1);
    uVar2 = *(undefined1 *)((int)puVar10 + 5);
    uVar3 = iVar9 + 0x14a3U & 3;
    puVar4 = (uint *)((iVar9 + 0x14a3U) - uVar3);
    *puVar4 = *puVar4 & -1 << (uVar3 + 1) * 8 | uVar11 >> (3 - uVar3) * 8;
    uVar3 = iVar9 + 0x14a0U & 3;
    puVar4 = (uint *)((iVar9 + 0x14a0U) - uVar3);
    *puVar4 = *puVar4 & 0xffffffffU >> (4 - uVar3) * 8 | uVar11 << uVar3 * 8;
    *(undefined1 *)(iVar9 + 0x14a4) = uVar1;
    *(undefined1 *)(iVar9 + 0x14a5) = uVar2;
  }
LAB_004f52e0:
  iVar9 = getodin();
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remoteproc.c"
             ,0x2e7,"update_remote_model_str","remote_model_str = %s\n",iVar9 + 0x14a0);
  return;
}



// === upgrade_thread_func @ 004f53f0 ===

undefined4 upgrade_thread_func(void)

{
  return 0;
}



// === service_upgrade_request @ 004f5478 ===

undefined4 service_upgrade_request(undefined4 param_1,void *param_2,size_t param_3)

{
  undefined4 local_20;
  void *local_1c;
  size_t local_18;
  void *local_10;
  
  local_1c = (void *)0x0;
  local_18 = 0;
  local_20 = param_1;
  if ((param_2 != (void *)0x0) && (param_3 != 0)) {
    local_10 = param_2;
    local_1c = (void *)lv_malloc(param_3);
    local_18 = param_3;
    memcpy(local_1c,local_10,param_3);
  }
  llqueue_push(queue_service_upgrade,&local_20,0xc);
  return 0;
}



// === service_upgrade_launch @ 004f54f0 ===

bool service_upgrade_launch(void)

{
  int iVar1;
  
  llqueue_init(queue_service_upgrade,0xc);
  iVar1 = pthread_create(&upgrade_thread,(pthread_attr_t *)0x0,upgrade_thread_func,
                         queue_service_upgrade);
  if (iVar1 != 0) {
    puts("Error creating upgrade thread");
  }
  return iVar1 != 0;
}



// === service_upgrade_join @ 004f5550 ===

undefined4 service_upgrade_join(void)

{
  pthread_join(upgrade_thread,(void **)0x0);
  return 0;
}



// === compare_upgrade_file_name @ 004f5640 ===

undefined4 compare_upgrade_file_name(char *param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  char *pcVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  char *local_78 [4];
  char acStack_68 [8];
  char acStack_60 [4];
  char acStack_5c [28];
  char acStack_40 [32];
  
  pcVar3 = hw_ver_filter;
  if ((param_1 == (char *)0x0) || (param_2 == (char *)0x0)) {
    local_78[1] = "Parameters are not available\n";
    local_78[0] = "compare_upgrade_file_name";
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/upgrade/upgrade.c"
               ,0x131);
    uVar6 = 0xffffffff;
  }
  else {
    sVar2 = strlen(hw_ver_filter);
    iVar1 = -(sVar2 + 0xb & 0xfffffff8);
    *(undefined **)((int)local_78 + iVar1) = &DAT_0069a674;
    snprintf(acStack_68 + iVar1,sVar2 + 6,"%s%s",pcVar3);
    pcVar3 = strstr(param_2,"_V");
    if (pcVar3 == (char *)0x0) {
      snprintf(acStack_40,0x20,"%s",param_2);
    }
    else {
      memcpy(acStack_40,param_2,(int)pcVar3 - (int)param_2);
      *(char **)((int)local_78 + iVar1 + 4) = "Extract model name=======%s\n";
      *(char **)((int)local_78 + iVar1 + 8) = acStack_40;
      *(char **)((int)local_78 + iVar1) = "compare_upgrade_file_name";
      acStack_40[(int)pcVar3 - (int)param_2] = '\0';
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/upgrade/upgrade.c"
                 ,0x141);
    }
    iVar4 = strncmp(param_1,acStack_68 + iVar1,sVar2 + 4);
    if (iVar4 != 0) {
      return 0;
    }
    pcVar3 = strstr(param_1,"ota_");
    if ((pcVar3 == (char *)0x0) && (pcVar3 = strstr(param_1,"ota-"), pcVar3 == (char *)0x0)) {
      return 0;
    }
    pcVar5 = strrchr(pcVar3,0x5f);
    strncpy(acStack_60,pcVar3,(int)pcVar5 - (int)pcVar3);
    *(char **)((int)local_78 + iVar1 + 4) = "======ota_name==%s====full_version_name===%s\n";
    *(char **)((int)local_78 + iVar1 + 0xc) = acStack_40;
    *(char **)((int)local_78 + iVar1 + 8) = acStack_5c;
    *(char **)((int)local_78 + iVar1) = "compare_upgrade_file_name";
    acStack_60[(int)pcVar5 - (int)pcVar3] = '\0';
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/upgrade/upgrade.c"
               ,0x153);
    pcVar3 = strstr(acStack_5c,acStack_40);
    if ((pcVar3 != (char *)0x0) ||
       (pcVar3 = strstr(acStack_40,acStack_5c), uVar6 = 0, pcVar3 != (char *)0x0)) {
      *(char **)((int)local_78 + iVar1 + 4) = "The upgrade package matches\n";
      *(char **)((int)local_78 + iVar1) = "compare_upgrade_file_name";
      uVar6 = 1;
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/upgrade/upgrade.c"
                 ,0x156);
    }
  }
  return uVar6;
}



// === extract_udisk_upgrade_version @ 004f5a50 ===

undefined4 extract_udisk_upgrade_version(char *param_1,char *param_2,uint param_3)

{
  char *pcVar1;
  int iVar2;
  char *__src;
  int iVar3;
  uint __n;
  
  if ((param_1 == (char *)0x0) || (param_2 == (char *)0x0)) {
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/upgrade/upgrade.c"
               ,0x198,"extract_udisk_upgrade_version","Parameters are not available\n");
  }
  else {
    pcVar1 = strrchr(param_1,0x5f);
    __src = pcVar1 + 2;
    if (pcVar1 != (char *)0x0) {
      iVar2 = (int)pcVar1[2];
      iVar3 = 0;
      pcVar1 = __src;
      if (iVar2 != 0) {
        do {
          if ((iVar2 != 0x2e) && (9 < (iVar2 - 0x30U & 0xff))) break;
          pcVar1 = pcVar1 + 1;
          iVar2 = (int)*pcVar1;
        } while (iVar2 != 0);
        iVar3 = (int)pcVar1 - (int)__src;
      }
      iVar2 = strcmp(pcVar1,"S.img");
      __n = iVar3 + (uint)(iVar2 == 0);
      if (__n < param_3) {
        strncpy(param_2,__src,__n);
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/upgrade/upgrade.c"
                   ,0x1b5,"extract_udisk_upgrade_version",
                   "===Extract OTA version information===%s\n",param_2);
        if (param_2[__n - 1] == '.') {
          param_2[__n - 1] = '\0';
          return 0;
        }
        param_2[__n] = '\0';
        return 0;
      }
    }
  }
  return 0xffffffff;
}



// === compare_ota_version @ 004f5fac ===

int compare_ota_version(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 auStack_28 [32];
  
  iVar1 = extract_version(param_1,auStack_28,0x20);
  if (iVar1 != 0) {
    puts("Failed to extract version from file name.");
    return 0;
  }
  printf("compare version: new vs current: %s - %s\n",auStack_28,param_2);
  iVar1 = compare_versions(auStack_28,param_2);
  if (iVar1 < 1) {
    if (iVar1 == 0) {
      puts("Versions are equal.");
      return 0;
    }
    puts("new version is lower.");
    return iVar1;
  }
  puts("new version is higher.");
  return iVar1;
}



// === wifi_setup_cmd_timer_callback @ 004f60fc ===

void wifi_setup_cmd_timer_callback(undefined4 param_1)

{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  local_20 = CONCAT31(local_20._1_3_,1);
  iVar1 = get_log_level(&DAT_00613050,&local_20);
  if (iVar1 != 0) {
    lv_log_add((int)(char)local_20,0,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/wifi/wifi_client.c"
               ,0xde,"wifi_setup_cmd_timer_callback","[wifi] wifi_setup_cmd\n");
  }
  local_1c = 0;
  local_18 = 0;
  local_20 = 0;
  llqueue_push(queue_service_wifi,&local_20,0xc);
  local_20 = 7;
  local_1c = 0;
  local_18 = 0;
  llqueue_push(queue_service_wifi,&local_20,0xc);
  local_20 = 6;
  local_1c = 0;
  local_18 = 0;
  llqueue_push(queue_service_wifi,&local_20,0xc);
  lv_timer_delete(param_1);
  local_20 = CONCAT31(local_20._1_3_,1);
  iVar1 = get_log_level(&DAT_00613050,&local_20);
  if (iVar1 != 0) {
    lv_log_add((int)(char)local_20,0,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/wifi/wifi_client.c"
               ,0xe8,"wifi_setup_cmd_timer_callback","[wifi] wifi_setup_cmd done\n");
  }
  return;
}



// === compare_signal_strength @ 004f773c ===

int compare_signal_strength(int param_1,int param_2)

{
  return *(int *)(param_1 + 0x44) - *(int *)(param_2 + 0x44);
}



// === service_wsslicer_request @ 004fa210 ===

undefined4 service_wsslicer_request(undefined4 param_1,void *param_2,size_t param_3)

{
  undefined4 local_20;
  void *local_1c;
  size_t local_18;
  void *local_10;
  
  local_1c = (void *)0x0;
  local_18 = 0;
  local_20 = param_1;
  if ((param_2 != (void *)0x0) && (param_3 != 0)) {
    local_10 = param_2;
    local_1c = (void *)lv_malloc(param_3);
    local_18 = param_3;
    memcpy(local_1c,local_10,param_3);
  }
  llqueue_push(queue_service_wsslicer,&local_20,0xc);
  return 0;
}



// === service_wsslicer_launch @ 004fa76c ===

undefined4 service_wsslicer_launch(void)

{
  int iVar1;
  undefined4 uVar2;
  
  ws_init_cmd_cache(ll_slicer_history);
  ws_init_resp(resp_wsslicer);
  task_queue_init(wsslicer_task_queue);
  iVar1 = pthread_create(&wsslicer_thread,(pthread_attr_t *)0x0,websocket_slicer_thread,
                         queue_service_wsslicer);
  if (iVar1 == 0) {
    llqueue_init(queue_service_wsslicer,0xc);
    iVar1 = pthread_create(&wsslicer_thread,(pthread_attr_t *)0x0,tasks_slicer_thread,
                           queue_service_wsslicer);
    uVar2 = 0;
    if (iVar1 != 0) {
      perror("Failed to create tasks_slicer_thread thread");
      uVar2 = 0xffffffff;
    }
  }
  else {
    perror("Failed to create wsslicer websocket thread");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// === service_wsslicer_join @ 004fa82c ===

undefined4 service_wsslicer_join(void)

{
  pthread_join(wsslicer_thread,(void **)0x0);
  return 0;
}



// === elapseUploadEnable_proc @ 004fd500 ===

undefined4 elapseUploadEnable_proc(void)

{
  puts("elapseUploadEnable_proc");
  return 1;
}



// === enableAITest_proc @ 004fe82c ===

undefined4 enableAITest_proc(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  puts("enableAITest_proc");
  uVar1 = 0xffffffff;
  if (param_1 != 0) {
    iVar2 = getodin();
    if ((*(int *)(iVar2 + 0x1630) != 0) && (param_3 == 1)) {
      service_gui_request(0x1e,0,0);
    }
    iVar3 = *(int *)(param_1 + 0x14);
    iVar2 = getodin();
    *(bool *)(iVar2 + 0x1768) = iVar3 != 0;
    DAT_0084cd50 = iVar3;
    iVar2 = getodin();
    save_systemconfig(iVar2 + 0x12b8);
    iVar2 = getodin();
    service_extcom_request(3,iVar2 + 0x1768,7);
    service_gui_request(0x22,0,0);
    uVar1 = 1;
  }
  return uVar1;
}



// === enableFaultStop_proc @ 004fe8ec ===

undefined4 enableFaultStop_proc(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  puts("enableFaultStop_proc");
  uVar1 = 0xffffffff;
  if (param_1 != 0) {
    iVar2 = getodin();
    if ((*(int *)(iVar2 + 0x1630) != 0) && (param_3 == 1)) {
      service_gui_request(0x1e,0,0);
    }
    iVar3 = *(int *)(param_1 + 0x14);
    iVar2 = getodin();
    *(bool *)(iVar2 + 0x176b) = iVar3 != 0;
    DAT_0084cd54 = iVar3;
    iVar2 = getodin();
    service_extcom_request(3,iVar2 + 0x1768,7);
    uVar1 = 1;
  }
  return uVar1;
}



// === enableSelfTest_proc @ 004fe9f0 ===

undefined4 enableSelfTest_proc(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  puts("enableSelfTest_proc");
  uVar1 = 0xffffffff;
  if (param_1 != 0) {
    iVar2 = getodin();
    if ((*(int *)(iVar2 + 0x1630) != 0) && (param_3 == 1)) {
      service_gui_request(0x1e,0,0);
    }
    pthread_mutex_lock((pthread_mutex_t *)printStateMutex);
    DAT_0084cda8 = *(undefined4 *)(param_1 + 0x14);
    pthread_mutex_unlock((pthread_mutex_t *)printStateMutex);
    uVar1 = 1;
  }
  return uVar1;
}



// === gcodeCmd_proc @ 004fef2c ===

undefined4 gcodeCmd_proc(int param_1,undefined4 param_2,int param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 local_60 [17];
  
  if (param_1 == 0) {
    return 0xffffffff;
  }
  pcVar5 = *(char **)(param_1 + 0x10);
  if (pcVar5 == (char *)0x0) {
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
               ,0x238,"gcodeCmd_proc","cmd valuestring is NULL\n");
    return 1;
  }
  iVar3 = getodin();
  if (*(int *)(iVar3 + 0x1630) == 0) {
    if (param_3 == 1) {
LAB_004ff038:
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
                 ,0x243,"gcodeCmd_proc","gcodeCmd_proc: %s\n",pcVar5);
      iVar3 = strncmp(pcVar5,"G28",3);
      if ((iVar3 == 0) || (iVar3 = strncmp(pcVar5,"G90",3), iVar3 == 0)) {
        iVar3 = getodin();
        uVar1 = *(undefined1 *)(iVar3 + 10000);
        iVar3 = getodin();
        uVar2 = *(undefined1 *)(iVar3 + 0x2711);
        iVar3 = getodin();
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
                   ,0x245,"gcodeCmd_proc","homed.x=%d, homed.y=%d, homed.z=%d\n",uVar1,uVar2,
                   *(undefined1 *)(iVar3 + 0x2712));
      }
      iVar3 = getodin();
      if ((*(int *)(iVar3 + 0x2714) == 2) &&
         ((iVar3 = strncmp(pcVar5,"G28",3), iVar3 == 0 ||
          (iVar3 = strncmp(pcVar5,"G90",3), iVar3 == 0)))) {
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
                   ,0x249,"gcodeCmd_proc","ACCESS_STATE_HOMEING\n");
        return 1;
      }
      iVar3 = strncmp(pcVar5,"G28 X Y Z",9);
      if (iVar3 == 0) {
        iVar3 = getodin();
        *(undefined4 *)(iVar3 + 0x2714) = 2;
        local_60[0] = ws_run_cmd("cx_home_all",1,"");
        ws_reqcb_cache_add(local_60[0],axis_homed_cb,local_60,300);
        pcVar5 = "ws_run_cmd: cx_home_all\n";
        uVar4 = 0x252;
      }
      else {
        iVar3 = strncmp(pcVar5,"G28 X Y",7);
        if (iVar3 == 0) {
          iVar3 = getodin();
          *(undefined4 *)(iVar3 + 0x2714) = 2;
          local_60[0] = ws_run_cmd("cx_home_xy",1,"");
          ws_reqcb_cache_add(local_60[0],axis_homed_cb,local_60,300);
          pcVar5 = "ws_run_cmd: cx_home_xy\n";
          uVar4 = 0x25b;
        }
        else {
          iVar3 = strncmp(pcVar5,"G28 Z",5);
          if ((iVar3 == 0) &&
             ((iVar3 = getodin(), *(char *)(iVar3 + 10000) == '\0' ||
              (iVar3 = getodin(), *(char *)(iVar3 + 0x2711) == '\0')))) {
            iVar3 = getodin();
            *(undefined4 *)(iVar3 + 0x2714) = 2;
            local_60[0] = ws_run_cmd("cx_home_all",1,"");
            ws_reqcb_cache_add(local_60[0],axis_homed_cb,local_60,300);
            pcVar5 = "ws_run_cmd: cx_home_all\n";
            uVar4 = 0x264;
          }
          else {
            iVar3 = strncmp(pcVar5,"G28 Z",6);
            if (iVar3 != 0) {
              ws_run_cmd("cx_printer_gcode_script",1,"%s",pcVar5);
              return 1;
            }
            iVar3 = getodin();
            *(undefined4 *)(iVar3 + 0x2714) = 2;
            local_60[0] = ws_run_cmd("cx_home_z",1,"");
            ws_reqcb_cache_add(local_60[0],axis_homed_cb,local_60,300);
            pcVar5 = "ws_run_cmd: cx_home_z\n";
            uVar4 = 0x26d;
          }
        }
      }
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
                 ,uVar4,"gcodeCmd_proc",pcVar5);
      return 1;
    }
  }
  else if (param_3 == 1) {
    service_gui_request(0x1e,0,0);
    goto LAB_004ff038;
  }
  memset(local_60,0,0x40);
  iVar3 = strncmp(pcVar5,"M106 P1",7);
  if (iVar3 == 0) {
    snprintf((char *)local_60,0x40,"%s%s","M106 P3",pcVar5 + 7);
    pcVar5 = (char *)local_60;
  }
  ws_run_cmd("cx_printer_gcode_script",1,"%s",pcVar5);
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
             ,0x27e,"gcodeCmd_proc","gcodeCmd_proc: %s\n",pcVar5);
  return 1;
}



// === upgrade_proc @ 004ffcec ===

undefined4 upgrade_proc(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  char *__src;
  char acStack_118 [256];
  undefined4 local_18;
  
  puts("upgrade_proc");
  uVar1 = 0xffffffff;
  if (param_1 != 0) {
    iVar2 = getodin();
    if ((*(int *)(iVar2 + 0x1630) == 0) || (param_3 != 1)) {
      __src = *(char **)(param_1 + 0x10);
    }
    else {
      service_gui_request(0x1e,0,0);
      __src = *(char **)(param_1 + 0x10);
    }
    strncpy(acStack_118,__src,0x100);
    local_18 = 2;
    printf("upgrade_url: %s\n",acStack_118);
    service_httpchunk_request(1,acStack_118,0x104);
    uVar1 = 1;
  }
  return uVar1;
}



// === jwtToken_proc @ 00500690 ===

undefined4 jwtToken_proc(int param_1)

{
  int iVar1;
  char *__src;
  
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
             ,0x886,"jwtToken_proc","jwtToken_proc start\n");
  __src = *(char **)(param_1 + 0x10);
  iVar1 = getodin();
  strncpy((char *)(iVar1 + 0x18f2),__src,0x100);
  iVar1 = getodin();
  if (*(char *)(iVar1 + 0x1a41) == '\0') {
    iVar1 = getodin();
    request_user_onwerInfo(iVar1 + 0x18f2);
  }
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/services/remoteproc/remote_set_handler.c"
             ,0x896,"jwtToken_proc","jwtToken_proc end\n");
  return 1;
}



// === token_proc @ 00500e20 ===

undefined4 token_proc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  puts("token_proc");
  iVar1 = cJSON_GetObjectItem(param_1,"print");
  iVar2 = cJSON_GetObjectItem(param_1,"opGcodeFile");
  iVar3 = cJSON_GetObjectItem(param_1,"exportLog");
  iVar4 = cJSON_GetObjectItem(param_1,"livestream");
  if (iVar1 != 0) {
    uVar5 = print_proc(param_1,param_2,param_3);
    return uVar5;
  }
  if (iVar2 != 0) {
    uVar5 = opGcodeFile_proc(param_1,param_2,param_3);
    return uVar5;
  }
  if (iVar3 != 0) {
    uVar5 = exportLog_proc(param_1,param_2,param_3);
    return uVar5;
  }
  if (iVar4 != 0) {
    uVar5 = livestream_proc(param_1,param_2,param_3);
    return uVar5;
  }
  return 1;
}



// === wifi_cmd_scan_results @ 005023a4 ===

void wifi_cmd_scan_results(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = wpa_ctrl_command(param_1,param_2,5000000,&DAT_0069cf14);
  if (-1 < iVar1) {
    sleep(2);
    wpa_ctrl_command(param_1,param_2,5000000,"SCAN_RESULTS");
    return;
  }
  return;
}



// === _M_assign @ 00507258 ===

/* std::__cxx11::string::_M_assign(std::__cxx11::string const&) */

void __thiscall std::__cxx11::string::_M_assign(string *this,string *param_1)

{
  uint uVar1;
  string *__dest;
  uint __n;
  uint local_20 [2];
  
  if (this == param_1) {
    return;
  }
  __dest = *(string **)this;
  __n = *(uint *)(param_1 + 4);
  if (this + 8 == __dest) {
    uVar1 = 0xf;
  }
  else {
    uVar1 = *(uint *)(this + 8);
  }
  if (uVar1 < __n) {
    local_20[0] = __n;
    __dest = (string *)_M_create(local_20,uVar1);
    if (this + 8 != *(string **)this) {
      operator_delete(*(string **)this);
    }
    *(string **)this = __dest;
    *(uint *)(this + 8) = local_20[0];
  }
  if (__n != 0) {
    if (__n != 1) {
      memcpy(__dest,*(string **)param_1,__n);
      *(uint *)(this + 4) = __n;
      *(undefined1 *)(*(int *)this + __n) = 0;
      return;
    }
    *__dest = **(string **)param_1;
    __dest = *(string **)this;
  }
  *(uint *)(this + 4) = __n;
  __dest[__n] = (string)0x0;
  return;
}



// === tvg_canvas_update @ 005079b4 ===

undefined4 tvg_canvas_update(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1 != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x005079c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*param_1 + 0x10))(param_1,0);
    return uVar1;
  }
  return 1;
}



// === tvg_canvas_update_paint @ 005079d4 ===

undefined4 tvg_canvas_update_paint(int *param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((param_1 != (int *)0x0) && (param_2 != 0)) {
                    /* WARNING: Could not recover jumptable at 0x005079ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*param_1 + 0x10))();
    return uVar1;
  }
  return 1;
}



// === tvg_paint_rotate @ 00507ab4 ===

undefined4 tvg_paint_rotate(Paint *param_1,float param_2)

{
  undefined4 uVar1;
  
  if (param_1 != (Paint *)0x0) {
    uVar1 = tvg::Paint::rotate(param_1,param_2);
    return uVar1;
  }
  return 1;
}



// === tvg_animation_get_total_frame @ 00508c0c ===

undefined4 tvg_animation_get_total_frame(Animation *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((param_1 != (Animation *)0x0) && (param_2 != (undefined4 *)0x0)) {
    uVar1 = tvg::Animation::totalFrame(param_1);
    *param_2 = uVar1;
    uVar1 = 0;
  }
  return uVar1;
}



// === HASH_KEY @ 00509e1c ===

/* HASH_KEY(char const*) */

char * HASH_KEY(char *param_1)

{
  return param_1;
}



// === totalFrame @ 0050adc4 ===

/* LottieLoader::totalFrame() */

float __thiscall LottieLoader::totalFrame(LottieLoader *this)

{
  return (*(float *)(this + 0x40) - *(float *)(this + 0x3c)) * *(float *)(this + 0x5c);
}



// === assign @ 0050ca7c ===

/* LottieSlot::assign(LottieObject*) */

void __thiscall LottieSlot::assign(LottieSlot *this,LottieObject *param_1)

{
  LottieSlot LVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  LottieObject *pLVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  
  iVar7 = *(int *)(this + 8);
  puVar4 = *(undefined4 **)(this + 4);
  puVar14 = puVar4;
  if (puVar4 < puVar4 + iVar7 * 2) {
    do {
      while (LVar1 = this[0x10], LVar1 != (LottieSlot)0x5) {
        if (LVar1 == (LottieSlot)0x7) {
          if (this[0x11] == (LottieSlot)0x0) {
            puVar4 = operator_new(0x58);
            piVar8 = (int *)*puVar14;
            puVar4[2] = 0;
            iVar7 = piVar8[5];
            puVar4[1] = 0;
            *puVar4 = &PTR__LottieTextDoc_0069e0d8;
            puVar4[3] = 0;
            *(undefined1 *)(puVar4 + 0x11) = 0;
            puVar4[0x12] = 0;
            puVar4[0x14] = 0;
            puVar14[1] = puVar4;
            if (iVar7 == 0) {
              piVar2 = puVar4 + 3;
              piVar6 = piVar8 + 6;
              do {
                piVar5 = piVar6;
                piVar3 = piVar2;
                iVar11 = piVar5[1];
                iVar10 = piVar5[2];
                iVar7 = piVar5[3];
                piVar6 = piVar5 + 4;
                *piVar3 = *piVar5;
                piVar3[1] = iVar11;
                piVar3[2] = iVar10;
                piVar3[3] = iVar7;
                piVar2 = piVar3 + 4;
              } while (piVar6 != piVar8 + 0x16);
              iVar10 = piVar5[5];
              iVar7 = piVar5[6];
              piVar3[4] = *piVar6;
              piVar3[5] = iVar10;
              piVar3[6] = iVar7;
              piVar8[6] = 0;
              piVar8[0x15] = 0;
            }
            else {
              puVar4[2] = iVar7;
              piVar8[5] = 0;
            }
          }
          else {
            piVar8 = (int *)*puVar14;
          }
          (**(code **)(*piVar8 + 8))(piVar8,param_1 + 0xc);
          puVar4 = *(undefined4 **)(this + 4);
          iVar7 = *(int *)(this + 8);
        }
        else if (LVar1 == (LottieSlot)0x3) {
          if (this[0x11] == (LottieSlot)0x0) {
            puVar4 = operator_new(0x18);
            piVar8 = (int *)*puVar14;
            puVar4[1] = 0;
            puVar4[2] = 0;
            iVar10 = piVar8[7];
            iVar13 = piVar8[4];
            iVar12 = piVar8[5];
            iVar11 = piVar8[6];
            iVar7 = piVar8[8];
            *puVar4 = &PTR__LottieGenericProperty_0069e160;
            puVar14[1] = puVar4;
            puVar4[4] = iVar10;
            puVar4[1] = iVar13;
            puVar4[2] = iVar12;
            puVar4[3] = iVar11;
            puVar4[5] = iVar7;
            pLVar9 = param_1 + 0xc;
            iVar7 = *piVar8;
          }
          else {
            piVar8 = (int *)*puVar14;
            pLVar9 = param_1 + 0xc;
            iVar7 = *piVar8;
          }
          goto LAB_0050cb44;
        }
        puVar14 = puVar14 + 2;
        if (puVar4 + iVar7 * 2 <= puVar14) goto LAB_0050cb70;
      }
      if (this[0x11] == (LottieSlot)0x0) {
        puVar4 = operator_new(0x18);
        piVar8 = (int *)*puVar14;
        puVar4[2] = 0;
        iVar7 = piVar8[0x1b];
        puVar4[1] = 0;
        *puVar4 = &PTR__LottieColorStop_0069e0a0;
        puVar4[3] = 0;
        puVar4[4] = 0;
        *(undefined2 *)(puVar4 + 5) = 0;
        *(undefined1 *)((int)puVar4 + 0x16) = 0;
        puVar14[1] = puVar4;
        if (iVar7 == 0) {
          iVar7 = piVar8[0x1d];
          puVar4[3] = piVar8[0x1c];
          puVar4[4] = iVar7;
          piVar8[0x1c] = 0;
          piVar8[0x1d] = 0;
        }
        else {
          puVar4[2] = iVar7;
          piVar8[0x1b] = 0;
        }
        iVar7 = piVar8[0x1e];
        *(undefined1 *)((int)puVar4 + 0x16) = *(undefined1 *)((int)piVar8 + 0x7a);
        *(short *)(puVar4 + 5) = (short)iVar7;
      }
      else {
        piVar8 = (int *)*puVar14;
      }
      iVar7 = *piVar8;
      pLVar9 = param_1 + 100;
LAB_0050cb44:
      puVar14 = puVar14 + 2;
      (**(code **)(iVar7 + 8))(piVar8,pLVar9);
      iVar7 = *(int *)(this + 8);
      puVar4 = *(undefined4 **)(this + 4);
    } while (puVar14 < puVar4 + iVar7 * 2);
  }
LAB_0050cb70:
  this[0x11] = (LottieSlot)0x1;
  return;
}



// === parseKeyFrame<LottiePathSet> @ 0051d1e4 ===

/* void LottieParser::parseKeyFrame<LottiePathSet>(LottiePathSet&) */

void __thiscall
LottieParser::parseKeyFrame<LottiePathSet>(LottieParser *this,LottiePathSet *param_1)

{
  bool bVar1;
  uint uVar2;
  char *__s1;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  void *pvVar6;
  size_t __n;
  undefined4 *puVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  PathSet *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  puVar7 = *(undefined4 **)(param_1 + 8);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = calloc(1,0xc);
    *(undefined4 **)(param_1 + 8) = puVar7;
  }
  uVar8 = puVar7[2];
  uVar2 = puVar7[1] + 1;
  pvVar6 = (void *)*puVar7;
  if (uVar8 <= uVar2) {
    uVar2 = puVar7[1] * 2 + 2;
    __n = 0;
    if (uVar8 < uVar2) {
      puVar7[2] = uVar2;
      pvVar6 = realloc(pvVar6,uVar2 * 0x18);
      puVar5 = *(undefined4 **)(param_1 + 8);
      *puVar7 = pvVar6;
      pvVar6 = (void *)*puVar5;
      __n = (puVar5[2] - uVar8) * 0x18;
    }
    memset((void *)(uVar8 * 0x18 + (int)pvVar6),0,__n);
    puVar7 = *(undefined4 **)(param_1 + 8);
    pvVar6 = (void *)*puVar7;
    uVar2 = puVar7[1] + 1;
  }
  puVar7[1] = uVar2;
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_3c = (PathSet *)((int)pvVar6 + uVar2 * 0x18 + -0x18);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051d2a0:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar4 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 0x10) = uVar4;
        }
        return;
      }
      iVar3 = strcmp(__s1,"i");
      if (iVar3 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051d2a0;
      }
      iVar3 = strcmp(__s1,"o");
      if (iVar3 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051d2a0;
      }
      iVar3 = strcmp(__s1,"n");
      if (iVar3 == 0) {
        iVar3 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar3 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar3 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar3 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar3 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar3 == 0) goto LAB_0051d2a0;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051d2a0;
      }
      iVar3 = strcmp(__s1,local_40);
      if (iVar3 == 0) {
        local_2c = 0;
        uVar4 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 0xc) = uVar4;
        goto LAB_0051d2a0;
      }
      iVar3 = strcmp(__s1,local_38 + -0x31c);
      if (iVar3 == 0) {
        getValue(this,local_3c);
        goto LAB_0051d2a0;
      }
      iVar3 = strcmp(__s1,"e");
      if (iVar3 == 0) {
        getValue(this,(PathSet *)((*(int **)(param_1 + 8))[1] * 0x18 + **(int **)(param_1 + 8)));
        goto LAB_0051d2a0;
      }
      iVar3 = strcmp(__s1,"h");
      if (iVar3 != 0) break;
      iVar3 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0x14] = (PathSet)(iVar3 != 0);
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseKeyFrame<LottiePosition> @ 0051d548 ===

/* void LottieParser::parseKeyFrame<LottiePosition>(LottiePosition&) */

void __thiscall
LottieParser::parseKeyFrame<LottiePosition>(LottieParser *this,LottiePosition *param_1)

{
  bool bVar1;
  char *__s1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  Point *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  piVar7 = *(int **)(param_1 + 8);
  if (piVar7 == (int *)0x0) {
    piVar4 = operator_new(0xc);
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    *(int **)(param_1 + 8) = piVar4;
    iVar2 = 0;
    uVar6 = 2;
    uVar8 = 0;
LAB_0051d8ec:
    piVar4[2] = uVar6;
    pvVar5 = realloc((void *)*piVar4,uVar6 * 0x28);
    piVar7 = *(int **)(param_1 + 8);
    *piVar4 = (int)pvVar5;
  }
  else {
    uVar8 = piVar7[2];
    uVar6 = piVar7[1] + 1;
    if (uVar6 < uVar8) goto LAB_0051d5b4;
    uVar6 = piVar7[1] * 2 + 2;
    iVar2 = uVar8 * 0x28;
    piVar4 = piVar7;
    if (uVar8 < uVar6) goto LAB_0051d8ec;
  }
  memset((void *)(*piVar7 + iVar2),0,(piVar7[2] - uVar8) * 0x28);
  piVar7 = *(int **)(param_1 + 8);
  uVar6 = piVar7[1] + 1;
LAB_0051d5b4:
  piVar7[1] = uVar6;
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_3c = (Point *)(*piVar7 + uVar6 * 0x28 + -0x28);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051d608:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar3 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 0xc) = uVar3;
        }
        return;
      }
      iVar2 = strcmp(__s1,"i");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,"o");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,"n");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar2 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar2 == 0) goto LAB_0051d608;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,local_40);
      if (iVar2 == 0) {
        local_2c = 0;
        uVar3 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 8) = uVar3;
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,local_38 + -0x31c);
      if (iVar2 == 0) {
        getValue(this,local_3c);
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,"e");
      if (iVar2 == 0) {
        getValue(this,(Point *)((*(int **)(param_1 + 8))[1] * 0x28 + **(int **)(param_1 + 8)));
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,"ti");
      if (iVar2 == 0) {
        local_3c[0x24] = (Point)0x1;
        getValue(this,local_3c + 0x18);
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,"to");
      if (iVar2 == 0) {
        local_3c[0x24] = (Point)0x1;
        getValue(this,local_3c + 0x10);
        goto LAB_0051d608;
      }
      iVar2 = strcmp(__s1,"h");
      if (iVar2 != 0) break;
      iVar2 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0x25] = (Point)(iVar2 != 0);
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseKeyFrame<LottieGenericProperty<tvg::Point>> @ 0051dd9c ===

/* void LottieParser::parseKeyFrame<LottieGenericProperty<tvg::Point>
   >(LottieGenericProperty<tvg::Point>&) */

void __thiscall
LottieParser::parseKeyFrame<LottieGenericProperty<tvg::Point>>
          (LottieParser *this,LottieGenericProperty *param_1)

{
  bool bVar1;
  char *__s1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  Point *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  piVar7 = *(int **)(param_1 + 8);
  if (piVar7 == (int *)0x0) {
    piVar4 = operator_new(0xc);
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    *(int **)(param_1 + 8) = piVar4;
    iVar2 = 0;
    uVar6 = 2;
    uVar8 = 0;
LAB_0051e0f8:
    piVar4[2] = uVar6;
    pvVar5 = realloc((void *)*piVar4,uVar6 * 0x14);
    piVar7 = *(int **)(param_1 + 8);
    *piVar4 = (int)pvVar5;
  }
  else {
    uVar8 = piVar7[2];
    uVar6 = piVar7[1] + 1;
    if (uVar6 < uVar8) goto LAB_0051de08;
    uVar6 = piVar7[1] * 2 + 2;
    iVar2 = uVar8 * 0x14;
    piVar4 = piVar7;
    if (uVar8 < uVar6) goto LAB_0051e0f8;
  }
  memset((void *)(*piVar7 + iVar2),0,(piVar7[2] - uVar8) * 0x14);
  piVar7 = *(int **)(param_1 + 8);
  uVar6 = piVar7[1] + 1;
LAB_0051de08:
  piVar7[1] = uVar6;
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_3c = (Point *)(*piVar7 + uVar6 * 0x14 + -0x14);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051de5c:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar3 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 0xc) = uVar3;
        }
        return;
      }
      iVar2 = strcmp(__s1,"i");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051de5c;
      }
      iVar2 = strcmp(__s1,"o");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051de5c;
      }
      iVar2 = strcmp(__s1,"n");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar2 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar2 == 0) goto LAB_0051de5c;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051de5c;
      }
      iVar2 = strcmp(__s1,local_40);
      if (iVar2 == 0) {
        local_2c = 0;
        uVar3 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 8) = uVar3;
        goto LAB_0051de5c;
      }
      iVar2 = strcmp(__s1,local_38 + -0x31c);
      if (iVar2 == 0) {
        getValue(this,local_3c);
        goto LAB_0051de5c;
      }
      iVar2 = strcmp(__s1,"e");
      if (iVar2 == 0) {
        getValue(this,(Point *)((*(int **)(param_1 + 8))[1] * 0x14 + **(int **)(param_1 + 8)));
        goto LAB_0051de5c;
      }
      iVar2 = strcmp(__s1,"h");
      if (iVar2 != 0) break;
      iVar2 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0x10] = (Point)(iVar2 != 0);
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseKeyFrame<LottieGenericProperty<float>> @ 0051e40c ===

/* void LottieParser::parseKeyFrame<LottieGenericProperty<float> >(LottieGenericProperty<float>&) */

void __thiscall
LottieParser::parseKeyFrame<LottieGenericProperty<float>>
          (LottieParser *this,LottieGenericProperty *param_1)

{
  bool bVar1;
  int iVar2;
  char *__s1;
  float fVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  float *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  piVar7 = *(int **)(param_1 + 8);
  if (piVar7 == (int *)0x0) {
    piVar4 = operator_new(0xc);
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    *(int **)(param_1 + 8) = piVar4;
    uVar6 = 2;
    iVar2 = 0;
    uVar8 = 0;
LAB_0051e754:
    piVar4[2] = uVar6;
    pvVar5 = realloc((void *)*piVar4,uVar6 << 4);
    piVar7 = *(int **)(param_1 + 8);
    *piVar4 = (int)pvVar5;
  }
  else {
    iVar2 = piVar7[1];
    uVar8 = piVar7[2];
    uVar6 = iVar2 + 1;
    if (uVar6 < uVar8) goto LAB_0051e478;
    uVar6 = iVar2 * 2 + 2;
    iVar2 = uVar8 << 4;
    piVar4 = piVar7;
    if (uVar8 < uVar6) goto LAB_0051e754;
  }
  memset((void *)(*piVar7 + iVar2),0,(piVar7[2] - uVar8) * 0x10);
  piVar7 = *(int **)(param_1 + 8);
  iVar2 = piVar7[1];
  uVar6 = iVar2 + 1;
LAB_0051e478:
  piVar7[1] = uVar6;
  local_3c = (float *)(*piVar7 + iVar2 * 0x10);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051e4c4:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          fVar3 = (float)getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          local_3c[2] = fVar3;
        }
        return;
      }
      iVar2 = strcmp(__s1,"i");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051e4c4;
      }
      iVar2 = strcmp(__s1,"o");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051e4c4;
      }
      iVar2 = strcmp(__s1,"n");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar2 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar2 == 0) goto LAB_0051e4c4;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051e4c4;
      }
      iVar2 = strcmp(__s1,local_40);
      if (iVar2 == 0) {
        local_2c = 0;
        fVar3 = (float)LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        local_3c[1] = fVar3;
        goto LAB_0051e4c4;
      }
      iVar2 = strcmp(__s1,local_38 + -0x31c);
      if (iVar2 == 0) {
        getValue(this,local_3c);
        goto LAB_0051e4c4;
      }
      iVar2 = strcmp(__s1,"e");
      if (iVar2 == 0) {
        getValue(this,(float *)(**(int **)(param_1 + 8) + (*(int **)(param_1 + 8))[1] * 0x10));
        goto LAB_0051e4c4;
      }
      iVar2 = strcmp(__s1,"h");
      if (iVar2 != 0) break;
      iVar2 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      *(bool *)(local_3c + 3) = iVar2 != 0;
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseKeyFrame<LottieGenericProperty<unsigned_char>> @ 0051ea6c ===

/* void LottieParser::parseKeyFrame<LottieGenericProperty<unsigned char>
   >(LottieGenericProperty<unsigned char>&) */

void __thiscall
LottieParser::parseKeyFrame<LottieGenericProperty<unsigned_char>>
          (LottieParser *this,LottieGenericProperty *param_1)

{
  bool bVar1;
  int iVar2;
  char *__s1;
  undefined4 uVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  uchar *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  piVar7 = *(int **)(param_1 + 8);
  if (piVar7 == (int *)0x0) {
    piVar4 = operator_new(0xc);
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    *(int **)(param_1 + 8) = piVar4;
    uVar6 = 2;
    iVar2 = 0;
    uVar8 = 0;
LAB_0051edb4:
    piVar4[2] = uVar6;
    pvVar5 = realloc((void *)*piVar4,uVar6 << 4);
    piVar7 = *(int **)(param_1 + 8);
    *piVar4 = (int)pvVar5;
  }
  else {
    iVar2 = piVar7[1];
    uVar8 = piVar7[2];
    uVar6 = iVar2 + 1;
    if (uVar6 < uVar8) goto LAB_0051ead8;
    uVar6 = iVar2 * 2 + 2;
    iVar2 = uVar8 << 4;
    piVar4 = piVar7;
    if (uVar8 < uVar6) goto LAB_0051edb4;
  }
  memset((void *)(*piVar7 + iVar2),0,(piVar7[2] - uVar8) * 0x10);
  piVar7 = *(int **)(param_1 + 8);
  iVar2 = piVar7[1];
  uVar6 = iVar2 + 1;
LAB_0051ead8:
  piVar7[1] = uVar6;
  local_3c = (uchar *)(*piVar7 + iVar2 * 0x10);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051eb24:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar3 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 8) = uVar3;
        }
        return;
      }
      iVar2 = strcmp(__s1,"i");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051eb24;
      }
      iVar2 = strcmp(__s1,"o");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051eb24;
      }
      iVar2 = strcmp(__s1,"n");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar2 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar2 == 0) goto LAB_0051eb24;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051eb24;
      }
      iVar2 = strcmp(__s1,local_40);
      if (iVar2 == 0) {
        local_2c = 0;
        uVar3 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 4) = uVar3;
        goto LAB_0051eb24;
      }
      iVar2 = strcmp(__s1,local_38 + -0x31c);
      if (iVar2 == 0) {
        getValue(this,local_3c);
        goto LAB_0051eb24;
      }
      iVar2 = strcmp(__s1,"e");
      if (iVar2 == 0) {
        getValue(this,(uchar *)(**(int **)(param_1 + 8) + (*(int **)(param_1 + 8))[1] * 0x10));
        goto LAB_0051eb24;
      }
      iVar2 = strcmp(__s1,"h");
      if (iVar2 != 0) break;
      iVar2 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0xc] = iVar2 != 0;
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseProperty<(LottieProperty::Type)2,LottieGenericProperty<unsigned_char>> @ 0051edd0 ===

/* void LottieParser::parseProperty<(LottieProperty::Type)2, LottieGenericProperty<unsigned char>
   >(LottieGenericProperty<unsigned char>&, LottieObject*) */

void __thiscall
LottieParser::parseProperty<(LottieProperty::Type)2,LottieGenericProperty<unsigned_char>>
          (LottieParser *this,LottieGenericProperty *param_1,LottieObject *param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  void *pvVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
LAB_0051ee20:
  do {
    pcVar1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (pcVar1 == (char *)0x0) {
        return;
      }
      iVar2 = strcmp(pcVar1,"k");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 6) goto LAB_0051ef30;
        LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
        goto LAB_0051ef08;
      }
      if ((param_2 != (LottieObject *)0x0) &&
         (iVar2 = strcmp(pcVar1,(char *)&PTR_DAT_0069e2e8), iVar2 == 0)) break;
      iVar2 = strcmp(pcVar1,"x");
      if (iVar2 != 0) goto LAB_0051ef40;
      uVar3 = LookaheadParserHandler::getStringCopy((LookaheadParserHandler *)this);
      uVar3 = _expression(uVar3,*(undefined4 *)(this + 0x44),*(undefined4 *)(this + 0x4c),
                          *(undefined4 *)(this + 0x50),param_1,2);
      *(undefined4 *)(param_1 + 4) = uVar3;
      pcVar1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    pcVar1 = (char *)LookaheadParserHandler::getStringCopy((LookaheadParserHandler *)this);
    iVar2 = *(int *)(this + 0x44);
    puVar9 = *(undefined4 **)(iVar2 + 0x44);
    puVar6 = puVar9 + *(int *)(iVar2 + 0x48);
    while (puVar9 < puVar6) {
      puVar10 = (undefined4 *)*puVar9;
      puVar9 = puVar9 + 1;
      iVar4 = strcmp((char *)*puVar10,pcVar1);
      if (iVar4 == 0) {
        iVar2 = puVar10[2];
        uVar7 = iVar2 + 1;
        if ((uint)puVar10[3] < uVar7) {
          iVar2 = (iVar2 + 2U >> 1) + iVar2;
          puVar10[3] = iVar2;
          pvVar5 = realloc((void *)puVar10[1],iVar2 * 8);
          iVar2 = puVar10[2];
          puVar10[1] = pvVar5;
          uVar7 = iVar2 + 1;
        }
        else {
          pvVar5 = (void *)puVar10[1];
        }
        puVar9 = (undefined4 *)((int)pvVar5 + iVar2 * 8);
        puVar10[2] = uVar7;
        *puVar9 = param_2;
        puVar9[1] = 0;
        return;
      }
    }
    puVar9 = operator_new(0x14);
    *puVar9 = pcVar1;
    *(undefined1 *)(puVar9 + 4) = 2;
    puVar9[1] = 0;
    puVar9[2] = 0;
    *(undefined1 *)((int)puVar9 + 0x11) = 0;
    puVar9[3] = 1;
    pvVar5 = realloc((void *)0x0,8);
    iVar4 = *(int *)(iVar2 + 0x48);
    uVar7 = *(uint *)(iVar2 + 0x4c);
    uVar8 = iVar4 + 1;
    puVar6 = (undefined4 *)((int)pvVar5 + puVar9[2] * 8);
    puVar9[1] = pvVar5;
    puVar9[2] = puVar9[2] + 1;
    *puVar6 = param_2;
    puVar6[1] = 0;
    if (uVar7 < uVar8) {
      iVar4 = (iVar4 + 2U >> 1) + iVar4;
      *(int *)(iVar2 + 0x4c) = iVar4;
      pvVar5 = realloc(*(void **)(iVar2 + 0x44),iVar4 * 4);
      iVar4 = *(int *)(iVar2 + 0x48);
      *(void **)(iVar2 + 0x44) = pvVar5;
      uVar8 = iVar4 + 1;
    }
    else {
      pvVar5 = *(void **)(iVar2 + 0x44);
    }
    *(uint *)(iVar2 + 0x48) = uVar8;
    *(undefined4 **)((int)pvVar5 + iVar4 * 4) = puVar9;
  } while( true );
LAB_0051ef08:
  iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
  if (iVar2 == 0) goto LAB_0051ee20;
  iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
  if (iVar2 != 3) goto LAB_0051ef30;
  parseKeyFrame<LottieGenericProperty<unsigned_char>>(this,param_1);
  goto LAB_0051ef08;
LAB_0051ef30:
  getValue(this,(uchar *)(param_1 + 0xc));
  goto LAB_0051ee20;
LAB_0051ef40:
  LookaheadParserHandler::skip((char *)this);
  goto LAB_0051ee20;
}



// === parseKeyFrame<LottieGenericProperty<RGB24>> @ 0051f0e4 ===

/* void LottieParser::parseKeyFrame<LottieGenericProperty<RGB24> >(LottieGenericProperty<RGB24>&) */

void __thiscall
LottieParser::parseKeyFrame<LottieGenericProperty<RGB24>>
          (LottieParser *this,LottieGenericProperty *param_1)

{
  bool bVar1;
  char *__s1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  RGB24 *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  piVar7 = *(int **)(param_1 + 8);
  if (piVar7 == (int *)0x0) {
    piVar4 = operator_new(0xc);
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    *(int **)(param_1 + 8) = piVar4;
    iVar2 = 0;
    uVar6 = 2;
    uVar8 = 0;
LAB_0051f440:
    piVar4[2] = uVar6;
    pvVar5 = realloc((void *)*piVar4,uVar6 * 0x18);
    piVar7 = *(int **)(param_1 + 8);
    *piVar4 = (int)pvVar5;
  }
  else {
    uVar8 = piVar7[2];
    uVar6 = piVar7[1] + 1;
    if (uVar6 < uVar8) goto LAB_0051f150;
    uVar6 = piVar7[1] * 2 + 2;
    iVar2 = uVar8 * 0x18;
    piVar4 = piVar7;
    if (uVar8 < uVar6) goto LAB_0051f440;
  }
  memset((void *)(*piVar7 + iVar2),0,(piVar7[2] - uVar8) * 0x18);
  piVar7 = *(int **)(param_1 + 8);
  uVar6 = piVar7[1] + 1;
LAB_0051f150:
  piVar7[1] = uVar6;
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_3c = (RGB24 *)(*piVar7 + uVar6 * 0x18 + -0x18);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051f1a4:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar3 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 0x10) = uVar3;
        }
        return;
      }
      iVar2 = strcmp(__s1,"i");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051f1a4;
      }
      iVar2 = strcmp(__s1,"o");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051f1a4;
      }
      iVar2 = strcmp(__s1,"n");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar2 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar2 == 0) goto LAB_0051f1a4;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051f1a4;
      }
      iVar2 = strcmp(__s1,local_40);
      if (iVar2 == 0) {
        local_2c = 0;
        uVar3 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 0xc) = uVar3;
        goto LAB_0051f1a4;
      }
      iVar2 = strcmp(__s1,local_38 + -0x31c);
      if (iVar2 == 0) {
        getValue(this,local_3c);
        goto LAB_0051f1a4;
      }
      iVar2 = strcmp(__s1,"e");
      if (iVar2 == 0) {
        getValue(this,(RGB24 *)((*(int **)(param_1 + 8))[1] * 0x18 + **(int **)(param_1 + 8)));
        goto LAB_0051f1a4;
      }
      iVar2 = strcmp(__s1,"h");
      if (iVar2 != 0) break;
      iVar2 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0x14] = (RGB24)(iVar2 != 0);
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseKeyFrame<LottieColorStop> @ 0051f774 ===

/* void LottieParser::parseKeyFrame<LottieColorStop>(LottieColorStop&) */

void __thiscall
LottieParser::parseKeyFrame<LottieColorStop>(LottieParser *this,LottieColorStop *param_1)

{
  bool bVar1;
  uint uVar2;
  char *__s1;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  void *pvVar6;
  size_t __n;
  undefined4 *puVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  ColorStop *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  puVar7 = *(undefined4 **)(param_1 + 8);
  if (puVar7 == (undefined4 *)0x0) {
    puVar7 = calloc(1,0xc);
    *(undefined4 **)(param_1 + 8) = puVar7;
  }
  uVar8 = puVar7[2];
  uVar2 = puVar7[1] + 1;
  pvVar6 = (void *)*puVar7;
  if (uVar8 <= uVar2) {
    uVar2 = puVar7[1] * 2 + 2;
    __n = 0;
    if (uVar8 < uVar2) {
      puVar7[2] = uVar2;
      pvVar6 = realloc(pvVar6,uVar2 * 0x14);
      puVar5 = *(undefined4 **)(param_1 + 8);
      *puVar7 = pvVar6;
      pvVar6 = (void *)*puVar5;
      __n = (puVar5[2] - uVar8) * 0x14;
    }
    memset((void *)(uVar8 * 0x14 + (int)pvVar6),0,__n);
    puVar7 = *(undefined4 **)(param_1 + 8);
    pvVar6 = (void *)*puVar7;
    uVar2 = puVar7[1] + 1;
  }
  puVar7[1] = uVar2;
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_3c = (ColorStop *)((int)pvVar6 + uVar2 * 0x14 + -0x14);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051f830:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar4 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 0xc) = uVar4;
        }
        return;
      }
      iVar3 = strcmp(__s1,"i");
      if (iVar3 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051f830;
      }
      iVar3 = strcmp(__s1,"o");
      if (iVar3 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051f830;
      }
      iVar3 = strcmp(__s1,"n");
      if (iVar3 == 0) {
        iVar3 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar3 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar3 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar3 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar3 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar3 == 0) goto LAB_0051f830;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051f830;
      }
      iVar3 = strcmp(__s1,local_40);
      if (iVar3 == 0) {
        local_2c = 0;
        uVar4 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 8) = uVar4;
        goto LAB_0051f830;
      }
      iVar3 = strcmp(__s1,local_38 + -0x31c);
      if (iVar3 == 0) {
        getValue(this,local_3c);
        goto LAB_0051f830;
      }
      iVar3 = strcmp(__s1,"e");
      if (iVar3 == 0) {
        getValue(this,(ColorStop *)((*(int **)(param_1 + 8))[1] * 0x14 + **(int **)(param_1 + 8)));
        goto LAB_0051f830;
      }
      iVar3 = strcmp(__s1,"h");
      if (iVar3 != 0) break;
      iVar3 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0x10] = (ColorStop)(iVar3 != 0);
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === parseKeyFrame<LottieTextDoc> @ 0051fdec ===

/* void LottieParser::parseKeyFrame<LottieTextDoc>(LottieTextDoc&) */

void __thiscall
LottieParser::parseKeyFrame<LottieTextDoc>(LottieParser *this,LottieTextDoc *param_1)

{
  bool bVar1;
  char *__s1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  void *pvVar5;
  uint uVar6;
  int *piVar7;
  uint uVar8;
  char *pcVar9;
  Point aPStack_50 [8];
  Point aPStack_48 [8];
  char *local_40;
  TextDocument *local_3c;
  char *local_38;
  undefined4 local_2c;
  
  local_2c = 0;
  piVar7 = *(int **)(param_1 + 8);
  if (piVar7 == (int *)0x0) {
    piVar4 = operator_new(0xc);
    *piVar4 = 0;
    piVar4[1] = 0;
    piVar4[2] = 0;
    *(int **)(param_1 + 8) = piVar4;
    iVar2 = 0;
    uVar6 = 2;
    uVar8 = 0;
LAB_00520148:
    piVar4[2] = uVar6;
    pvVar5 = realloc((void *)*piVar4,uVar6 * 0x58);
    piVar7 = *(int **)(param_1 + 8);
    *piVar4 = (int)pvVar5;
  }
  else {
    uVar8 = piVar7[2];
    uVar6 = piVar7[1] + 1;
    if (uVar6 < uVar8) goto LAB_0051fe58;
    uVar6 = piVar7[1] * 2 + 2;
    iVar2 = uVar8 * 0x58;
    piVar4 = piVar7;
    if (uVar8 < uVar6) goto LAB_00520148;
  }
  memset((void *)(*piVar7 + iVar2),0,(piVar7[2] - uVar8) * 0x58);
  piVar7 = *(int **)(param_1 + 8);
  uVar6 = piVar7[1] + 1;
LAB_0051fe58:
  piVar7[1] = uVar6;
  bVar1 = false;
  pcVar9 = (char *)0x0;
  local_3c = (TextDocument *)(*piVar7 + uVar6 * 0x58 + -0x58);
  LookaheadParserHandler::enterObject((LookaheadParserHandler *)this);
  local_40 = "t";
  local_38 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
LAB_0051feac:
  do {
    __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    while( true ) {
      if (__s1 == (char *)0x0) {
        if (bVar1) {
          uVar3 = getInterpolator(this,pcVar9,aPStack_48,aPStack_50);
          *(undefined4 *)(local_3c + 0x50) = uVar3;
        }
        return;
      }
      iVar2 = strcmp(__s1,"i");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_48);
        bVar1 = true;
        goto LAB_0051feac;
      }
      iVar2 = strcmp(__s1,"o");
      if (iVar2 == 0) {
        getInterpolatorPoint(this,aPStack_50);
        goto LAB_0051feac;
      }
      iVar2 = strcmp(__s1,"n");
      if (iVar2 == 0) {
        iVar2 = LookaheadParserHandler::peekType((LookaheadParserHandler *)this);
        if (iVar2 == 5) {
          pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
        }
        else {
          LookaheadParserHandler::enterArray((LookaheadParserHandler *)this);
          while (iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this),
                iVar2 != 0) {
            while (pcVar9 != (char *)0x0) {
              LookaheadParserHandler::skip((char *)this);
              iVar2 = LookaheadParserHandler::nextArrayValue((LookaheadParserHandler *)this);
              if (iVar2 == 0) goto LAB_0051feac;
            }
            pcVar9 = (char *)LookaheadParserHandler::getString((LookaheadParserHandler *)this);
          }
        }
        goto LAB_0051feac;
      }
      iVar2 = strcmp(__s1,local_40);
      if (iVar2 == 0) {
        local_2c = 0;
        uVar3 = LookaheadParserHandler::getFloat((LookaheadParserHandler *)this);
        local_2c = 0;
        *(undefined4 *)(local_3c + 0x4c) = uVar3;
        goto LAB_0051feac;
      }
      iVar2 = strcmp(__s1,local_38 + -0x31c);
      if (iVar2 == 0) {
        getValue(this,local_3c);
        goto LAB_0051feac;
      }
      iVar2 = strcmp(__s1,"e");
      if (iVar2 == 0) {
        getValue(this,(TextDocument *)((*(int **)(param_1 + 8))[1] * 0x58 + **(int **)(param_1 + 8))
                );
        goto LAB_0051feac;
      }
      iVar2 = strcmp(__s1,"h");
      if (iVar2 != 0) break;
      iVar2 = LookaheadParserHandler::getInt((LookaheadParserHandler *)this);
      local_3c[0x54] = (TextDocument)(iVar2 != 0);
      __s1 = (char *)LookaheadParserHandler::nextObjectKey((LookaheadParserHandler *)this);
    }
    LookaheadParserHandler::skip((char *)this);
  } while( true );
}



// === nextObjectKey @ 00521590 ===

/* LookaheadParserHandler::nextObjectKey() */

LookaheadParserHandler * __thiscall
LookaheadParserHandler::nextObjectKey(LookaheadParserHandler *this)

{
  LookaheadParserHandler *pLVar1;
  int iVar2;
  
  iVar2 = *(int *)(this + 0x10);
  if (iVar2 != 6) {
    if ((iVar2 != 10) && (iVar2 != 7)) {
      if ((iVar2 == 8) && (*(int *)(this + 0x2c) == 0)) {
        parseNext(this);
        return (LookaheadParserHandler *)0x0;
      }
      *(undefined4 *)(this + 0x10) = 1;
    }
    return (LookaheadParserHandler *)0x0;
  }
  if ((*(ushort *)(this + 0xe) & 0x1000) == 0) {
    iVar2 = *(int *)(this + 0x2c);
    pLVar1 = *(LookaheadParserHandler **)(this + 8);
  }
  else {
    iVar2 = *(int *)(this + 0x2c);
    pLVar1 = this;
  }
  if (iVar2 == 0) {
    parseNext(this);
    return pLVar1;
  }
  *(undefined4 *)(this + 0x10) = 1;
  return pLVar1;
}



// === rotate @ 00523490 ===

/* tvg::Paint::Impl::rotate(float) */

undefined4 __thiscall tvg::Paint::Impl::rotate(Impl *this,float param_1)

{
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  
  iVar2 = *(int *)(this + 4);
  if (iVar2 == 0) {
    if (DAT_0069dea8 < ABS(param_1)) {
      pvVar3 = operator_new(0x38);
      uVar1 = DAT_00586c20;
      *(undefined4 *)((int)pvVar3 + 0x24) = 0;
      *(undefined4 *)((int)pvVar3 + 0x28) = 0;
      *(undefined4 *)((int)pvVar3 + 0x30) = uVar1;
      *(undefined1 *)((int)pvVar3 + 0x34) = 0;
      *(void **)(this + 4) = pvVar3;
      *(float *)((int)pvVar3 + 0x2c) = param_1;
      goto LAB_005235ac;
    }
  }
  else if ((DAT_0069dea8 < ABS(param_1 - *(float *)(iVar2 + 0x2c))) &&
          (*(float *)(iVar2 + 0x2c) = param_1, *(char *)(iVar2 + 0x34) == '\0')) {
LAB_005235ac:
    this[0x11] = (Impl)((byte)this[0x11] | 0x10);
    return 1;
  }
  return 1;
}



// === update @ 00524038 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* tvg::Paint::Impl::update(tvg::RenderMethod*, tvg::RenderTransform const*, tvg::Array<void*>&,
   unsigned char, tvg::RenderUpdateFlag, bool) */

int __thiscall
tvg::Paint::Impl::update
          (Impl *this,int *param_1,Matrix *param_2,undefined4 *param_3,byte param_4,byte param_6,
          byte param_7)

{
  Impl IVar1;
  Impl IVar2;
  Impl IVar3;
  undefined4 *puVar4;
  int iVar5;
  RenderTransform *this_00;
  undefined4 uVar6;
  void *__ptr;
  Fill *pFVar7;
  float *pfVar8;
  int *piVar9;
  uint uVar10;
  int iVar11;
  uchar uVar12;
  int *piVar14;
  int iVar15;
  Impl *this_01;
  uint uVar16;
  Shape *pSVar17;
  code *pcVar18;
  float fVar19;
  float fVar20;
  void *local_e8;
  uint local_e4;
  uint local_e0;
  int local_dc;
  float local_b0;
  float local_ac;
  float local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  Point *local_68;
  uchar local_64;
  uchar local_63 [3];
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  Fill *local_50;
  RenderTransform *local_4c;
  Fill *local_48;
  Fill *local_44;
  uint local_40;
  undefined4 local_34;
  uint uVar13;
  
  local_34 = 0;
  local_50 = (Fill *)(uint)param_7;
  if (*(int **)(this + 0xc) != param_1) {
    param_1[1] = param_1[1] + 1;
    *(int **)(this + 0xc) = param_1;
  }
  if (((byte)this[0x11] & 0x10) != 0) {
    if (*(RenderTransform **)(this + 4) == (RenderTransform *)0x0) {
      return 0;
    }
    RenderTransform::update(*(RenderTransform **)(this + 4));
  }
  puVar4 = *(undefined4 **)(this + 8);
  if (puVar4 == (undefined4 *)0x0) {
LAB_00524570:
    local_4c = (RenderTransform *)0x0;
    iVar5 = 2;
  }
  else {
    pSVar17 = (Shape *)*puVar4;
    iVar11 = puVar4[2];
    iVar5 = *(int *)(pSVar17 + 4);
    *(byte *)(iVar5 + 0x12) = *(byte *)(iVar5 + 0x12) & 0xfe;
    if (*(char *)(iVar5 + 0x13) == '\x01') {
      if (iVar11 == 1) goto LAB_0052416c;
      Shape::fillColor(pSVar17,(uchar *)0x0,(uchar *)0x0,(uchar *)0x0,(uchar *)&local_e8);
      iVar5 = Shape::fill(pSVar17);
      if (iVar5 != 0) {
        iVar5 = *(int *)(pSVar17 + 4);
LAB_00524530:
        iVar11 = *(int *)(this + 8);
LAB_00524534:
        iVar11 = *(int *)(iVar11 + 8);
        goto LAB_00524538;
      }
      iVar5 = *(int *)(pSVar17 + 4);
      if (*(int *)(iVar5 + 8) != 0) goto LAB_00524530;
      if (iVar11 != 2) {
        if (iVar11 != 3) goto LAB_00524530;
        if ((local_e8._0_1_ == (RenderRegion)0x0) || (*(char *)(iVar5 + 0x14) == '\0'))
        goto LAB_0052416c;
        iVar11 = *(int *)(this + 8);
        goto LAB_00524534;
      }
      if (((uint)local_e8 & 0xff) != 0xff) goto LAB_00524530;
      if (*(char *)(iVar5 + 0x14) != -1) {
        iVar11 = *(int *)(*(int *)(this + 8) + 8);
        goto LAB_00524538;
      }
LAB_0052416c:
      this_00 = *(RenderTransform **)(iVar5 + 4);
      local_4c = this_00;
      iVar5 = Shape::pathCoords(pSVar17,&local_68);
      if (iVar5 != 0) {
        if (iVar5 == 4) {
          if (this_00 == (RenderTransform *)0x0) {
            if (param_2 != (Matrix *)0x0) goto LAB_00524c6c;
          }
          else {
            RenderTransform::update(this_00);
            if (param_2 != (Matrix *)0x0) {
LAB_00524c6c:
              local_34 = 0;
              fVar19 = atan2f(*(float *)(param_2 + 0xc),*(float *)param_2);
              fVar19 = ABS(fVar19);
              if ((((DAT_0069dea8 <= fVar19) && (DAT_0069dea8 < ABS(fVar19 - DAT_00590e50))) &&
                  (local_34 = 0, DAT_0069dea8 < ABS(fVar19 - _DAT_005901e0))) ||
                 (local_34 = 0,
                 DAT_0069dea8 < ABS(*(float *)(param_2 + 4) + *(float *)(param_2 + 0xc))))
              goto LAB_005249e0;
              if (local_4c == (RenderTransform *)0x0) goto LAB_00524280;
            }
            local_34 = 0;
            fVar19 = atan2f(*(float *)(local_4c + 0xc),*(float *)local_4c);
            fVar19 = ABS(fVar19);
            if ((((DAT_0069dea8 <= fVar19) && (DAT_0069dea8 < ABS(fVar19 - DAT_00590e50))) &&
                (local_34 = 0, DAT_0069dea8 < ABS(fVar19 - _DAT_005901e0))) ||
               (local_34 = 0,
               DAT_0069dea8 < ABS(*(float *)(local_4c + 4) + *(float *)(local_4c + 0xc))))
            goto LAB_005249e0;
          }
LAB_00524280:
          if ((((ABS(*(float *)local_68 - *(float *)(local_68 + 8)) <= DAT_0069dea8) &&
               (ABS(*(float *)(local_68 + 0xc) - *(float *)(local_68 + 0x14)) <= DAT_0069dea8)) &&
              ((ABS(*(float *)(local_68 + 0x10) - *(float *)(local_68 + 0x18)) <= DAT_0069dea8 &&
               (ABS(*(float *)(local_68 + 4) - *(float *)(local_68 + 0x1c)) <= DAT_0069dea8)))) ||
             ((((local_34 = 0,
                ABS(*(float *)(local_68 + 8) - *(float *)(local_68 + 0x10)) <= DAT_0069dea8 &&
                (local_34 = 0,
                ABS(*(float *)(local_68 + 4) - *(float *)(local_68 + 0xc)) <= DAT_0069dea8)) &&
               (local_34 = 0, ABS(*(float *)local_68 - *(float *)(local_68 + 0x18)) <= DAT_0069dea8)
               ) && (local_34 = 0,
                    ABS(*(float *)(local_68 + 0x14) - *(float *)(local_68 + 0x1c)) <= DAT_0069dea8))
             )) {
            local_34 = 0;
            local_74 = *(float *)(local_68 + 4);
            local_78 = *(float *)local_68;
            local_b0 = *(float *)(local_68 + 0x10);
            local_ac = *(float *)(local_68 + 0x14);
            if (local_4c != (RenderTransform *)0x0) {
              mathMultiply((Point *)&local_78,(Matrix *)local_4c);
              mathMultiply((Point *)&local_b0,(Matrix *)local_4c);
            }
            if (param_2 != (Matrix *)0x0) {
              mathMultiply((Point *)&local_78,param_2);
              mathMultiply((Point *)&local_b0,param_2);
            }
            fVar20 = local_ac;
            fVar19 = local_b0;
            if (local_b0 < local_78) {
              local_b0 = local_78;
              local_78 = fVar19;
            }
            if (local_ac < local_74) {
              local_ac = local_74;
              local_74 = fVar20;
            }
            local_34 = 0;
            local_e8 = (void *)(int)local_78;
            local_e4 = (uint)local_74;
            fVar19 = local_ac;
            local_4c = (RenderTransform *)local_e4;
            fVar20 = ceilf(local_b0 - (float)(int)local_e8);
            local_34 = 0;
            local_e0 = (uint)fVar20;
            fVar20 = (float)(int)local_4c;
            local_4c = (RenderTransform *)local_e0;
            fVar19 = ceilf(fVar19 - fVar20);
            local_34 = 0;
            local_dc = (int)fVar19;
            if ((int)local_4c < 0) {
              local_e0 = 0;
            }
            if (local_dc < 0) {
              local_dc = 0;
            }
            (**(code **)(*param_1 + 0x2c))(&local_60,param_1);
            local_78 = local_60;
            local_74 = (float)local_5c;
            local_70 = local_58;
            local_6c = local_54;
            RenderRegion::intersect((RenderRegion *)&local_e8,(RenderRegion *)&local_78);
            (**(code **)(*param_1 + 0x30))(param_1,&local_e8);
            iVar5 = 0;
            local_4c = (RenderTransform *)0x0;
            *(byte *)(*(int *)(pSVar17 + 4) + 0x12) = *(byte *)(*(int *)(pSVar17 + 4) + 0x12) | 1;
            goto LAB_0052457c;
          }
        }
LAB_005249e0:
        iVar5 = *(int *)(pSVar17 + 4);
        iVar11 = *(int *)(*(int *)(this + 8) + 8);
        goto LAB_00524538;
      }
      iVar5 = 1;
      local_4c = (RenderTransform *)0x0;
    }
    else {
LAB_00524538:
      uVar6 = update((Impl *)iVar5,param_1,param_2,param_3,0xff,param_6,iVar11 == 1);
      if (iVar11 != 1) goto LAB_00524570;
      iVar5 = param_3[1];
      uVar10 = iVar5 + 1;
      __ptr = (void *)*param_3;
      if ((uint)param_3[2] < uVar10) {
        iVar5 = (iVar5 + 2U >> 1) + iVar5;
        param_3[2] = iVar5;
        __ptr = realloc(__ptr,iVar5 * 4);
        iVar5 = param_3[1];
        *param_3 = __ptr;
        uVar10 = iVar5 + 1;
      }
      param_3[1] = uVar10;
      local_4c = (RenderTransform *)0x1;
      *(undefined4 *)((int)__ptr + iVar5 * 4) = uVar6;
      iVar5 = 2;
    }
  }
LAB_0052457c:
  IVar1 = this[0x11];
  this[0x11] = (Impl)0x0;
  uVar10 = (uint)(param_6 | (byte)IVar1);
  iVar11 = (uint)(byte)this[0x14] * (uint)param_4 + 0xff;
  uVar16 = iVar11 >> 8;
  RenderTransform::RenderTransform
            ((RenderTransform *)&local_b0,(RenderTransform *)param_2,*(RenderTransform **)(this + 4)
            );
  IVar2 = this[0x13];
  uVar13 = uVar16 & 0xff;
  uVar12 = (uchar)((uint)iVar11 >> 8);
  if (IVar2 == (Impl)0x2) {
    piVar9 = *(int **)(*(int *)this + 8);
    if (uVar16 == 0) {
      *(undefined1 *)((int)piVar9 + 0x15) = 0;
      uVar13 = 0;
LAB_00524a64:
      if (local_50 != (Fill *)0x0) {
        uVar16 = piVar9[2];
        local_e8 = (void *)0x0;
        local_e4 = 0;
        local_e0 = 0;
        if (uVar16 != 0) {
LAB_00524f24:
          local_e4 = 0;
          local_e8 = (void *)0x0;
          local_e0 = uVar16;
          local_e8 = realloc((void *)0x0,uVar16 << 2);
        }
        for (piVar14 = (int *)*piVar9; piVar14 != piVar9; piVar14 = (int *)*piVar14) {
                    /* try { // try from 00524ab0 to 00524b47 has its CatchHandler @ 0052500c */
          pFVar7 = (Fill *)update((Impl *)*(undefined4 *)(piVar14[2] + 4),param_1,
                                  (RenderTransform *)&local_b0,param_3,uVar13,uVar10,1);
          uVar16 = local_e4 + 1;
          if (local_e0 < uVar16) {
            local_e0 = (local_e4 + 2 >> 1) + local_e4;
            local_50 = pFVar7;
            local_e8 = realloc(local_e8,local_e0 * 4);
            uVar16 = local_e4 + 1;
            pFVar7 = local_50;
          }
          *(Fill **)((int)local_e8 + local_e4 * 4) = pFVar7;
          local_e4 = uVar16;
        }
        iVar11 = (**(code **)(*param_1 + 0xc))
                           (param_1,&local_e8,piVar9[3],(RenderTransform *)&local_b0,param_3,uVar13,
                            uVar10);
        piVar9[3] = iVar11;
        free(local_e8);
        goto joined_r0x0052477c;
      }
    }
    else {
      if ((int *)*piVar9 == piVar9) {
        *(undefined1 *)((int)piVar9 + 0x15) = 0;
        goto LAB_00524a64;
      }
      iVar11 = *(int *)(*(int *)(piVar9[4] + 4) + 8);
      if (((iVar11 != 0) && (1 < *(uint *)(iVar11 + 8))) ||
         (*(char *)(*(int *)(piVar9[4] + 4) + 0x10) != '\0')) {
LAB_00524928:
        *(uchar *)(piVar9 + 5) = uVar12;
        *(undefined1 *)((int)piVar9 + 0x15) = 1;
        uVar13 = 0xff;
        goto LAB_00524a64;
      }
      if (uVar16 == 0xff) {
        *(undefined1 *)((int)piVar9 + 0x15) = 0;
        uVar13 = 0xff;
        goto LAB_00524a64;
      }
      if (piVar9[2] != 1) {
        *(uchar *)(piVar9 + 5) = uVar12;
        *(undefined1 *)((int)piVar9 + 0x15) = 1;
        uVar13 = 0xff;
        goto LAB_00524a64;
      }
      if (*(char *)(*(int *)(((int *)*piVar9)[2] + 4) + 0x13) != '\x01') goto LAB_00524928;
      *(undefined1 *)((int)piVar9 + 0x15) = 0;
      if (local_50 != (Fill *)0x0) {
        uVar16 = 1;
        goto LAB_00524f24;
      }
    }
    for (piVar14 = (int *)*piVar9; piVar14 != piVar9; piVar14 = (int *)*piVar14) {
      update((Impl *)*(undefined4 *)(piVar14[2] + 4),param_1,(RenderTransform *)&local_b0,param_3,
             uVar13,uVar10,0);
    }
  }
  else if ((byte)IVar2 < 3) {
    if (IVar2 == (Impl)0x1) {
      iVar15 = *(int *)(*(int *)this + 8);
      if (uVar16 == 0) {
        *(undefined1 *)(iVar15 + 0x32) = 0;
        uVar13 = 0;
      }
      else {
        pfVar8 = *(float **)(iVar15 + 0x1c);
        if (((pfVar8 == (float *)0x0) || (local_34 = 0, *pfVar8 < DAT_0069dea8)) ||
           ((pfVar8[2] == 0.0 && (*(char *)((int)pfVar8 + 7) == '\0')))) {
          *(undefined1 *)(iVar15 + 0x32) = 0;
        }
        else if ((*(int *)(iVar15 + 0x18) == 0) && (*(char *)(iVar15 + 0x23) == '\0')) {
          *(undefined1 *)(iVar15 + 0x32) = 0;
        }
        else {
          if (uVar16 != 0xff) goto LAB_0052472c;
          puVar4 = *(undefined4 **)(*(int *)(*(int *)(iVar15 + 0x2c) + 4) + 8);
          if (((puVar4 == (undefined4 *)0x0) ||
              (pSVar17 = (Shape *)*puVar4, pSVar17 == (Shape *)0x0)) ||
             ((Fill *)puVar4[2] == (Fill *)0x1)) goto LAB_00524fec;
          if (((byte)(*(char *)(*(int *)(pSVar17 + 4) + 0x14) - 1U) < 0xfe) ||
             (uVar10 = (uint)*(byte *)(*(int *)(pSVar17 + 4) + 0x13), uVar10 != 1)) {
            *(uchar *)(iVar15 + 0x31) = uVar12;
            *(undefined1 *)(iVar15 + 0x32) = 1;
            uVar13 = 0xff;
          }
          else {
            local_48 = (Fill *)pSVar17;
            local_44 = (Fill *)puVar4[2];
            local_40 = uVar10;
            iVar11 = Shape::fill(pSVar17);
            pFVar7 = local_48;
            if (iVar11 == 0) {
              local_48 = local_44;
              Shape::fillColor((Shape *)pFVar7,local_63,&local_64,(uchar *)&local_68,
                               (uchar *)&local_e8);
              if ((((uint)local_e8 & 0xff) - 1 & 0xff) < 0xfe) goto LAB_0052472c;
              if ((Fill *)0x1 < local_48 + -4) {
LAB_00524fec:
                *(undefined1 *)(iVar15 + 0x32) = 0;
                uVar13 = 0xff;
                goto LAB_00524828;
              }
              if (local_63[0] == 0xff) {
                if (local_64 != 0xff) goto LAB_0052472c;
                if (((uint)local_68 & 0xff) == 0xff) goto LAB_00524fec;
                *(undefined1 *)(iVar15 + 0x32) = 1;
              }
              else {
                if (((local_63[0] == '\0') && (local_64 == '\0')) && ((char)local_68 == '\0'))
                goto LAB_00524fec;
LAB_0052472c:
                *(undefined1 *)(iVar15 + 0x32) = 1;
              }
              *(uchar *)(iVar15 + 0x31) = uVar12;
              uVar13 = 0xff;
            }
            else {
              *(uchar *)(iVar15 + 0x31) = uVar12;
              *(char *)(iVar15 + 0x32) = (char)local_40;
              uVar13 = 0xff;
            }
          }
        }
      }
LAB_00524828:
      iVar11 = (**(code **)(*param_1 + 8))
                         (param_1,iVar15,*(undefined4 *)(iVar15 + 0x28),(RenderTransform *)&local_b0
                          ,param_3,uVar13,param_6 | (byte)IVar1 | *(byte *)(iVar15 + 0x30),local_50)
      ;
      *(int *)(iVar15 + 0x28) = iVar11;
      *(undefined1 *)(iVar15 + 0x30) = 0;
      goto joined_r0x0052477c;
    }
  }
  else {
    if (IVar2 == (Impl)0x3) {
      this_01 = *(Impl **)(*(int *)this + 8);
      pFVar7 = (Fill *)Picture::Impl::load(this_01);
      if (*(int *)(this_01 + 8) == 0) {
        if (*(int *)(this_01 + 4) == 0) {
          iVar11 = *(int *)(this_01 + 0xc);
        }
        else {
          local_48 = pFVar7;
          if (this_01[0x24] != (Impl)0x0) {
            pcVar18 = *(code **)(**(int **)this_01 + 0x10);
            if (pcVar18 == LoadModule::resize) {
              this_01[0x24] = (Impl)0x0;
            }
            else {
              local_34 = 0;
              (*pcVar18)(*(int **)this_01,*(int *)(this_01 + 4),*(undefined4 *)(this_01 + 0x10),
                         *(undefined4 *)(this_01 + 0x14));
              this_01[0x24] = (Impl)0x0;
            }
          }
          IVar3 = (Impl)Picture::Impl::needComposition(this_01,uVar12);
          uVar6 = *(undefined4 *)(*(int *)(this_01 + 4) + 4);
          this_01[0x25] = IVar3;
          iVar11 = update((Impl *)uVar6,param_1,(RenderTransform *)&local_b0,param_3,uVar13,
                          uVar10 | (uint)local_48 & 0xff,local_50);
          *(int *)(this_01 + 0xc) = iVar11;
        }
      }
      else {
        local_50 = pFVar7;
        Picture::Impl::resizeTransform((RenderTransform *)&local_e8);
        iVar11 = (**(code **)(*param_1 + 0x10))
                           (param_1,*(undefined4 *)(this_01 + 8),this_01 + 0x18,
                            *(undefined4 *)(this_01 + 0xc),(RenderTransform *)&local_e8,param_3,
                            uVar13,uVar10 | (uint)local_50 & 0xff);
        *(int *)(this_01 + 0xc) = iVar11;
      }
      goto joined_r0x0052477c;
    }
    if (IVar2 == (Impl)0x6) {
      piVar14 = *(int **)(*(int *)this + 8);
      piVar9 = (int *)*piVar14;
      if (piVar9 != (int *)0x0) {
        iVar11 = piVar14[1];
        if (*(char *)((int)piVar14 + 0x11) != '\0') {
          (**(code **)(*piVar9 + 0x20))(piVar9,iVar11,piVar14[2],(char)piVar14[4]);
          piVar9 = (int *)*piVar14;
          if (*(code **)(*piVar9 + 0x18) == LoadModule::read) {
            if (*(char *)((int)piVar9 + 0x16) == '\0') {
              *(undefined1 *)((int)piVar9 + 0x16) = 1;
            }
            iVar11 = piVar14[1];
            *(undefined1 *)((int)piVar14 + 0x11) = 0;
          }
          else {
            (**(code **)(*piVar9 + 0x18))();
            iVar11 = piVar14[1];
            *(undefined1 *)((int)piVar14 + 0x11) = 0;
          }
        }
        if (iVar11 != 0) {
          pcVar18 = *(code **)(*(int *)*piVar14 + 0x10);
          if (pcVar18 != LoadModule::resize) {
            local_34 = 0;
            (*pcVar18)((int *)*piVar14,iVar11,piVar14[3]);
            iVar11 = piVar14[1];
          }
          if ((*(byte *)(*(int *)(iVar11 + 8) + 0x30) & 4) != 0) {
            local_34 = 0;
            local_48 = *(Fill **)(*(int *)(iVar11 + 8) + 0x18);
            fVar19 = DAT_00586c20 / *(float *)(*piVar14 + 0x18);
            iVar11 = Fill::identifier(local_48);
            if (iVar11 == 4) {
              local_34 = 0;
              pfVar8 = *(float **)(local_48 + 8);
              iVar11 = piVar14[1];
              *pfVar8 = *pfVar8 * fVar19;
              pfVar8[1] = pfVar8[1] * fVar19;
              pfVar8[2] = pfVar8[2] * fVar19;
              pfVar8[3] = pfVar8[3] * fVar19;
            }
            else {
              local_34 = 0;
              pfVar8 = *(float **)(local_48 + 8);
              iVar11 = piVar14[1];
              *pfVar8 = *pfVar8 * fVar19;
              pfVar8[1] = pfVar8[1] * fVar19;
              pfVar8[4] = pfVar8[4] * fVar19;
              pfVar8[2] = pfVar8[2] * fVar19;
              pfVar8[3] = pfVar8[3] * fVar19;
              pfVar8[5] = pfVar8[5] * fVar19;
            }
          }
          iVar11 = update((Impl *)*(undefined4 *)(iVar11 + 4),param_1,(RenderTransform *)&local_b0,
                          param_3,uVar13,uVar10,local_50);
          goto joined_r0x0052477c;
        }
      }
    }
  }
  iVar11 = 0;
joined_r0x0052477c:
  if (iVar5 == 0) {
    (**(code **)(*param_1 + 0x30))(param_1,&local_78);
  }
  else if ((local_4c != (RenderTransform *)0x0) && (param_3[1] != 0)) {
    param_3[1] = param_3[1] + -1;
  }
  return iVar11;
}



// === rotate @ 005265a0 ===

/* tvg::Paint::rotate(float) */

undefined4 __thiscall tvg::Paint::rotate(Paint *this,float param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = Impl::rotate(*(Impl **)(this + 4),param_1);
  uVar2 = 3;
  if (iVar1 != 0) {
    uVar2 = 0;
  }
  return uVar2;
}



// === update @ 005282a8 ===

/* tvg::RenderTransform::update() */

void __thiscall tvg::RenderTransform::update(RenderTransform *this)

{
  bool bVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  
  uVar2 = DAT_00586c20;
  if (this[0x34] == (RenderTransform)0x0) {
    bVar1 = ABS(*(float *)(this + 0x2c)) <= DAT_0069dea8;
    *(undefined4 *)(this + 4) = 0;
    *(undefined4 *)(this + 8) = 0;
    *(undefined4 *)(this + 0xc) = 0;
    *(undefined4 *)(this + 0x14) = 0;
    *(undefined4 *)(this + 0x18) = 0;
    *(undefined4 *)(this + 0x1c) = 0;
    *(undefined4 *)(this + 0x20) = uVar2;
    *(undefined4 *)this = *(undefined4 *)(this + 0x30);
    *(undefined4 *)(this + 0x10) = *(undefined4 *)(this + 0x30);
    if (bVar1) {
      fVar3 = 0.0;
      fVar4 = 0.0;
    }
    else {
      mathRotate((Matrix *)this,*(float *)(this + 0x2c));
      fVar4 = *(float *)(this + 8);
      fVar3 = *(float *)(this + 0x14);
    }
    *(float *)(this + 0x14) = *(float *)(this + 0x28) + fVar3;
    *(float *)(this + 8) = *(float *)(this + 0x24) + fVar4;
  }
  return;
}



// === _updateComposite @ 00530198 ===

/* _updateComposite(SvgNode*, SvgNode*) */

void _updateComposite(SvgNode *param_1,SvgNode *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(param_1 + 0x18);
  if (((*(char **)(iVar2 + 0x5c) != (char *)0x0) && (*(int *)(iVar2 + 0x60) == 0)) &&
     (iVar1 = _findNodeById(param_2,*(char **)(iVar2 + 0x5c)), iVar1 != 0)) {
    *(int *)(iVar2 + 0x60) = iVar1;
  }
  if (((*(char **)(iVar2 + 0x68) != (char *)0x0) && (*(int *)(iVar2 + 0x6c) == 0)) &&
     (iVar1 = _findNodeById(param_2,*(char **)(iVar2 + 0x68)), iVar1 != 0)) {
    *(int *)(iVar2 + 0x6c) = iVar1;
  }
  uVar3 = 0;
  if (*(int *)(param_1 + 0xc) != 0) {
    puVar4 = *(undefined4 **)(param_1 + 8);
    do {
      uVar3 = uVar3 + 1;
      _updateComposite((SvgNode *)*puVar4,param_2);
      puVar4 = puVar4 + 1;
    } while (uVar3 < *(uint *)(param_1 + 0xc));
  }
  return;
}



// === _updateStyle @ 005367a8 ===

/* _updateStyle(SvgNode*, SvgStyleProperty*) */

void _updateStyle(SvgNode *param_1,SvgStyleProperty *param_2)

{
  SvgNode *pSVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  _styleInherit(*(SvgStyleProperty **)(param_1 + 0x18),param_2);
  uVar2 = 0;
  if (*(int *)(param_1 + 0xc) != 0) {
    puVar3 = *(undefined4 **)(param_1 + 8);
    do {
      pSVar1 = (SvgNode *)*puVar3;
      uVar2 = uVar2 + 1;
      puVar3 = puVar3 + 1;
      _updateStyle(pSVar1,*(SvgStyleProperty **)(param_1 + 0x18));
    } while (uVar2 < *(uint *)(param_1 + 0xc));
  }
  return;
}



// === _updateGradient @ 00537510 ===

/* _updateGradient(SvgLoaderData*, SvgNode*, tvg::Array<SvgStyleGradient*>*) */

void _updateGradient(SvgLoaderData *param_1,SvgNode *param_2,Array *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  if (*(int *)(param_2 + 0xc) == 0) {
    iVar2 = *(int *)(param_2 + 0x18);
    if (*(int *)(iVar2 + 8) != 0) {
      iVar1 = _gradientDup(param_1,param_3,(char *)(param_3 + 4));
      iVar2 = *(int *)(param_2 + 0x18);
      if (iVar1 != 0) {
        iVar4 = *(int *)(iVar2 + 4);
        if (iVar4 != 0) {
          free(*(void **)(iVar4 + 0x1c));
          *(undefined4 *)(iVar4 + 0x1c) = 0;
          *(undefined4 *)(iVar4 + 0x24) = 0;
          *(undefined4 *)(iVar4 + 0x20) = 0;
          free(*(void **)(iVar4 + 0x18));
          free(*(void **)(iVar4 + 0x10));
          free(*(void **)(iVar4 + 0x14));
          free(*(void **)(iVar4 + 8));
          free(*(void **)(iVar4 + 4));
          free(*(void **)(*(int *)(param_2 + 0x18) + 4));
          iVar2 = *(int *)(param_2 + 0x18);
        }
        *(int *)(iVar2 + 4) = iVar1;
      }
    }
    if ((*(int *)(iVar2 + 0x24) != 0) &&
       (iVar2 = _gradientDup(param_1,param_3,(char *)(param_3 + 4)), iVar2 != 0)) {
      iVar1 = *(int *)(param_2 + 0x18);
      iVar4 = *(int *)(iVar1 + 0x20);
      if (iVar4 != 0) {
        free(*(void **)(iVar4 + 0x1c));
        *(undefined4 *)(iVar4 + 0x1c) = 0;
        *(undefined4 *)(iVar4 + 0x24) = 0;
        *(undefined4 *)(iVar4 + 0x20) = 0;
        free(*(void **)(iVar4 + 0x18));
        free(*(void **)(iVar4 + 0x10));
        free(*(void **)(iVar4 + 0x14));
        free(*(void **)(iVar4 + 8));
        free(*(void **)(iVar4 + 4));
        free(*(void **)(*(int *)(param_2 + 0x18) + 0x20));
        iVar1 = *(int *)(param_2 + 0x18);
      }
      *(int *)(iVar1 + 0x20) = iVar2;
      return;
    }
  }
  else {
    puVar5 = *(undefined4 **)(param_2 + 8);
    uVar3 = 0;
    do {
      _updateGradient(param_1,(SvgNode *)*puVar5,param_3);
      uVar3 = uVar3 + 1;
      puVar5 = puVar5 + 1;
    } while (uVar3 < *(uint *)(param_2 + 0xc));
  }
  return;
}



// === _isIgnoreUnsupportedLogAttributes @ 00547630 ===

/* _isIgnoreUnsupportedLogAttributes(char const*, char const*) */

undefined4 _isIgnoreUnsupportedLogAttributes(char *param_1,char *param_2)

{
  return 1;
}



// === isIgnoreUnsupportedLogElements @ 00547640 ===

/* isIgnoreUnsupportedLogElements(char const*) */

undefined4 isIgnoreUnsupportedLogElements(char *param_1)

{
  return 1;
}



// === totalFrame @ 00548714 ===

/* tvg::Animation::totalFrame() const */

undefined4 __thiscall tvg::Animation::totalFrame(Animation *this)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  piVar2 = (int *)**(undefined4 **)(**(int **)this + 8);
  if ((piVar2 != (int *)0x0) && (iVar1 = (**(code **)(*piVar2 + 0x20))(piVar2), iVar1 != 0)) {
                    /* WARNING: Could not recover jumptable at 0x005487c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (**(code **)(*piVar2 + 0x30))(piVar2);
    return uVar3;
  }
  return 0;
}



// === update @ 00549174 ===

/* tvg::Canvas::update(tvg::Paint*) */

undefined4 __thiscall tvg::Canvas::update(Canvas *this,Paint *param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  void *local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  piVar3 = *(int **)(this + 4);
  piVar4 = (int *)*piVar3;
  if ((piVar4 != piVar3) && ((char)piVar3[8] != '\x02')) {
    cVar1 = *(char *)((int)piVar3 + 0x21);
    local_28 = (void *)0x0;
    local_24 = 0;
    local_20 = 0;
    iVar2 = piVar3[3];
    if (param_1 == (Paint *)0x0) {
      while( true ) {
        Paint::Impl::update(*(Impl **)(piVar4[2] + 4),iVar2,0,&local_28,0xff,-cVar1,0);
        piVar4 = (int *)*piVar4;
        if (piVar3 == piVar4) break;
        iVar2 = piVar3[3];
      }
      *(undefined1 *)((int)piVar3 + 0x21) = 0;
    }
    else {
                    /* try { // try from 005491e4 to 0054923f has its CatchHandler @ 00549274 */
      Paint::Impl::update(*(Impl **)(param_1 + 4),iVar2,0,&local_28,0xff,-cVar1,0);
    }
    *(undefined1 *)(piVar3 + 8) = 1;
    free(local_28);
    return 0;
  }
  return 2;
}



// === _updateStroke @ 0054cf7c ===

/* WARNING: Removing unreachable block (ram,0x0054d434) */
/* WARNING: Removing unreachable block (ram,0x0054d0d4) */
/* WARNING: Removing unreachable block (ram,0x0054d2b0) */
/* WARNING: Removing unreachable block (ram,0x0054d598) */
/* _updateStroke(LottieStroke*, float, RenderContext*, LottieExpressions*) [clone .isra.80] */

void _updateStroke(LottieStroke *param_1,float param_2,RenderContext *param_3,
                  LottieExpressions *param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  Array *pAVar8;
  float *pfVar9;
  float fVar10;
  LottieExpression *pLVar11;
  Shape *this;
  float fVar12;
  float fVar13;
  float fVar14;
  
  this = *(Shape **)param_3;
  pAVar8 = *(Array **)(param_1 + 0xc);
  fVar12 = param_2;
  if ((param_4 == (LottieExpressions *)0x0) ||
     (pLVar11 = *(LottieExpression **)(param_1 + 8), pLVar11 == (LottieExpression *)0x0)) {
    if (pAVar8 != (Array *)0x0) goto LAB_0054d03c;
LAB_0054d6dc:
    fVar10 = *(float *)(param_1 + 0x10);
  }
  else {
    if ((pLVar11[0x15] != (LottieExpression)0x0) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      param_2 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,param_2,pLVar11);
      pAVar8 = *(Array **)(param_1 + 0xc);
    }
    if (pAVar8 == (Array *)0x0) goto LAB_0054d6dc;
LAB_0054d03c:
    iVar5 = *(int *)(pAVar8 + 4);
    pfVar9 = *(float **)pAVar8;
    if ((iVar5 == 1) || (param_2 <= pfVar9[1])) {
      fVar10 = *pfVar9;
    }
    else {
      iVar6 = iVar5 + -1;
      if (param_2 < (pfVar9 + iVar5 * 4 + -4)[1]) {
        if (-1 < iVar6) {
          iVar5 = 0;
          do {
            while (iVar7 = (iVar6 - iVar5) / 2 + iVar5, param_2 < pfVar9[iVar7 * 4 + 1]) {
              iVar6 = iVar7 + -1;
              if (iVar6 < iVar5) goto LAB_0054d108;
            }
            iVar5 = iVar7 + 1;
          } while (iVar5 <= iVar6);
        }
LAB_0054d108:
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        pfVar9 = pfVar9 + iVar6 * 4;
        fVar10 = pfVar9[1];
        if (ABS(fVar10 - param_2) <= DAT_0069dea8) {
LAB_0054d148:
          fVar10 = *pfVar9;
        }
        else {
          fVar10 = (param_2 - fVar10) / (pfVar9[5] - fVar10);
          if ((LottieInterpolator *)pfVar9[2] != (LottieInterpolator *)0x0) {
            fVar10 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar9[2],fVar10);
          }
          if (*(char *)(pfVar9 + 3) == '\0') {
            fVar10 = (pfVar9[4] - *pfVar9) * fVar10 + *pfVar9;
          }
          else {
            if (fVar10 < DAT_00586c20) goto LAB_0054d148;
            fVar10 = pfVar9[4];
          }
        }
      }
      else {
        fVar10 = pfVar9[iVar5 * 4 + -4];
      }
    }
  }
  tvg::Shape::stroke(this,fVar10);
  tvg::Shape::stroke(*(Shape **)param_3,*(undefined4 *)(param_1 + 0x1c));
  tvg::Shape::stroke(*(Shape **)param_3,*(undefined4 *)(param_1 + 0x20));
  tvg::Shape::strokeMiterlimit(*(Shape **)param_3,*(float *)(param_1 + 0x18));
  iVar5 = *(int *)(param_1 + 0x14);
  if (iVar5 == 0) {
    tvg::Shape::stroke(*(Shape **)param_3,(float *)0x0,0);
    return;
  }
  pAVar8 = *(Array **)(iVar5 + 0x18);
  fVar10 = fVar12;
  if ((param_4 == (LottieExpressions *)0x0) ||
     (pLVar11 = *(LottieExpression **)(iVar5 + 0x14), pLVar11 == (LottieExpression *)0x0)) {
    if (pAVar8 != (Array *)0x0) goto LAB_0054d21c;
LAB_0054d760:
    fVar12 = *(float *)(iVar5 + 0x1c);
  }
  else {
    if ((pLVar11[0x15] != (LottieExpression)0x0) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      fVar12 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar12,pLVar11);
      pAVar8 = *(Array **)(iVar5 + 0x18);
    }
    if (pAVar8 == (Array *)0x0) goto LAB_0054d760;
LAB_0054d21c:
    iVar5 = *(int *)(pAVar8 + 4);
    pfVar9 = *(float **)pAVar8;
    if ((iVar5 == 1) || (fVar12 <= pfVar9[1])) {
      fVar12 = *pfVar9;
    }
    else {
      iVar6 = iVar5 + -1;
      if (fVar12 < (pfVar9 + iVar5 * 4 + -4)[1]) {
        iVar5 = 0;
        if (-1 < iVar6) {
          do {
            iVar7 = (iVar6 - iVar5) / 2 + iVar5;
            if (pfVar9[iVar7 * 4 + 1] <= fVar12) {
              iVar5 = iVar7 + 1;
            }
            else {
              iVar6 = iVar7 + -1;
            }
          } while (iVar5 <= iVar6);
        }
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        pfVar9 = pfVar9 + iVar6 * 4;
        fVar14 = pfVar9[1];
        if (ABS(fVar14 - fVar12) <= DAT_0069dea8) {
LAB_0054d998:
          fVar12 = *pfVar9;
        }
        else {
          fVar12 = (fVar12 - fVar14) / (pfVar9[5] - fVar14);
          if ((LottieInterpolator *)pfVar9[2] != (LottieInterpolator *)0x0) {
            fVar12 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar9[2],fVar12);
          }
          if (*(char *)(pfVar9 + 3) == '\0') {
            fVar12 = (pfVar9[4] - *pfVar9) * fVar12 + *pfVar9;
          }
          else {
            if (fVar12 < DAT_00586c20) goto LAB_0054d998;
            fVar12 = pfVar9[4];
          }
        }
      }
      else {
        fVar12 = pfVar9[iVar5 * 4 + -4];
      }
    }
  }
  fVar14 = DAT_0069e6b0;
  if (fVar12 != 0.0) {
    fVar14 = fVar12;
  }
  puVar2 = *(undefined4 **)(param_1 + 0x14);
  fVar12 = fVar10;
  if (puVar2 == (undefined4 *)0x0) {
    puVar2 = operator_new(0x30);
    puVar2[1] = 0;
    *puVar2 = &PTR__LottieGenericProperty_0069e0f4;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[5] = 0;
    puVar2[4] = &PTR__LottieGenericProperty_0069e0f4;
    puVar2[6] = 0;
    puVar2[7] = 0;
    puVar2[9] = 0;
    puVar2[8] = &PTR__LottieGenericProperty_0069e0f4;
    puVar2[10] = 0;
    puVar2[0xb] = 0;
    *(undefined4 **)(param_1 + 0x14) = puVar2;
    if (param_4 != (LottieExpressions *)0x0) goto LAB_0054d93c;
    iVar5 = *(int *)(*(int *)param_3 + 8);
    fVar10 = fVar14 + 0.0;
LAB_0054d498:
    pAVar8 = (Array *)puVar2[2];
    if (((param_4 != (LottieExpressions *)0x0) &&
        (pLVar11 = (LottieExpression *)puVar2[1], pLVar11 != (LottieExpression *)0x0)) &&
       ((pLVar11[0x15] != (LottieExpression)0x0 && (pLVar11[0x20] != (LottieExpression)0x0)))) {
      fVar12 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar12,pLVar11);
      pAVar8 = (Array *)puVar2[2];
    }
    if (pAVar8 != (Array *)0x0) {
      iVar6 = *(int *)(pAVar8 + 4);
      pfVar9 = *(float **)pAVar8;
      if ((iVar6 == 1) || (fVar12 <= pfVar9[1])) {
        fVar12 = *pfVar9;
      }
      else {
        iVar7 = iVar6 + -1;
        if (fVar12 < (pfVar9 + iVar6 * 4 + -4)[1]) {
          iVar6 = 0;
          if (-1 < iVar7) {
            do {
              iVar3 = (iVar7 - iVar6) / 2 + iVar6;
              if (pfVar9[iVar3 * 4 + 1] <= fVar12) {
                iVar6 = iVar3 + 1;
              }
              else {
                iVar7 = iVar3 + -1;
              }
            } while (iVar6 <= iVar7);
          }
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          pfVar9 = pfVar9 + iVar7 * 4;
          fVar13 = pfVar9[1];
          if (DAT_0069dea8 < ABS(fVar13 - fVar12)) {
            fVar12 = (fVar12 - fVar13) / (pfVar9[5] - fVar13);
            if ((LottieInterpolator *)pfVar9[2] != (LottieInterpolator *)0x0) {
              fVar12 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar9[2],fVar12);
            }
            if (*(char *)(pfVar9 + 3) == '\0') {
              fVar12 = (pfVar9[4] - *pfVar9) * fVar12 + *pfVar9;
              goto LAB_0054d5d8;
            }
            if (DAT_00586c20 <= fVar12) {
              fVar12 = pfVar9[4];
              goto LAB_0054d5d8;
            }
          }
          fVar12 = *pfVar9;
        }
        else {
          fVar12 = pfVar9[iVar6 * 4 + -4];
        }
      }
      goto LAB_0054d5d8;
    }
  }
  else {
    pAVar8 = (Array *)puVar2[10];
    if ((((param_4 != (LottieExpressions *)0x0) &&
         (pLVar11 = (LottieExpression *)puVar2[9], pLVar11 != (LottieExpression *)0x0)) &&
        (pLVar11[0x15] != (LottieExpression)0x0)) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      fVar10 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar10,pLVar11);
      pAVar8 = (Array *)puVar2[10];
    }
    if (pAVar8 == (Array *)0x0) {
LAB_0054d93c:
      fVar10 = (float)puVar2[0xb];
      puVar2 = *(undefined4 **)(param_1 + 0x14);
    }
    else {
      iVar5 = *(int *)(pAVar8 + 4);
      pfVar9 = *(float **)pAVar8;
      if ((iVar5 == 1) || (fVar10 <= pfVar9[1])) {
        fVar10 = *pfVar9;
        puVar2 = *(undefined4 **)(param_1 + 0x14);
      }
      else {
        iVar6 = iVar5 + -1;
        if (fVar10 < (pfVar9 + iVar5 * 4 + -4)[1]) {
          iVar5 = 0;
          if (-1 < iVar6) {
            do {
              iVar7 = (iVar6 - iVar5) / 2 + iVar5;
              if (pfVar9[iVar7 * 4 + 1] <= fVar10) {
                iVar5 = iVar7 + 1;
              }
              else {
                iVar6 = iVar7 + -1;
              }
            } while (iVar5 <= iVar6);
          }
          if (iVar6 < 0) {
            iVar6 = 0;
          }
          pfVar9 = pfVar9 + iVar6 * 4;
          fVar13 = pfVar9[1];
          if (ABS(fVar13 - fVar10) <= DAT_0069dea8) {
            fVar10 = *pfVar9;
            puVar2 = *(undefined4 **)(param_1 + 0x14);
          }
          else {
            fVar10 = (fVar10 - fVar13) / (pfVar9[5] - fVar13);
            if ((LottieInterpolator *)pfVar9[2] != (LottieInterpolator *)0x0) {
              fVar10 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar9[2],fVar10);
            }
            puVar2 = *(undefined4 **)(param_1 + 0x14);
            if (*(char *)(pfVar9 + 3) == '\0') {
              fVar10 = (pfVar9[4] - *pfVar9) * fVar10 + *pfVar9;
            }
            else if (DAT_00586c20 <= fVar10) {
              fVar10 = pfVar9[4];
            }
            else {
              fVar10 = *pfVar9;
            }
          }
        }
        else {
          fVar10 = pfVar9[iVar5 * 4 + -4];
          puVar2 = *(undefined4 **)(param_1 + 0x14);
        }
      }
    }
    fVar10 = fVar14 + fVar10;
    iVar5 = *(int *)(*(int *)param_3 + 8);
    if (puVar2 != (undefined4 *)0x0) goto LAB_0054d498;
    puVar2 = operator_new(0x30);
    puVar2[1] = 0;
    *puVar2 = &PTR__LottieGenericProperty_0069e0f4;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[5] = 0;
    puVar2[4] = &PTR__LottieGenericProperty_0069e0f4;
    puVar2[6] = 0;
    puVar2[7] = 0;
    puVar2[9] = 0;
    puVar2[8] = &PTR__LottieGenericProperty_0069e0f4;
    puVar2[10] = 0;
    puVar2[0xb] = 0;
    *(undefined4 **)(param_1 + 0x14) = puVar2;
    fVar12 = 0.0;
    if (param_4 == (LottieExpressions *)0x0) goto LAB_0054d5d8;
  }
  fVar12 = (float)puVar2[3];
LAB_0054d5d8:
  if ((DAT_0069dea8 <= fVar14) && (DAT_0069dea8 <= fVar10)) {
    puVar2 = *(undefined4 **)(iVar5 + 0x1c);
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = operator_new(0x34);
      uVar1 = DAT_00585ff8;
      *puVar2 = 0;
      puVar2[8] = uVar1;
      fVar13 = DAT_00586c20;
      puVar2[1] = 0;
      puVar2[2] = 0;
      puVar2[3] = 0;
      puVar2[4] = 0;
      puVar2[5] = 0;
      puVar2[6] = 0;
      puVar2[7] = 0;
      puVar2[9] = 0;
      puVar2[0xc] = 0;
      puVar2[10] = 0;
      puVar2[0xb] = fVar13;
      *(undefined4 **)(iVar5 + 0x1c) = puVar2;
    }
    pfVar9 = (float *)puVar2[3];
    if (puVar2[4] != 2) {
      free(pfVar9);
      *(undefined4 *)(*(int *)(iVar5 + 0x1c) + 0xc) = 0;
      puVar2 = *(undefined4 **)(iVar5 + 0x1c);
      pfVar9 = (float *)puVar2[3];
    }
    if (pfVar9 == (float *)0x0) {
      pvVar4 = malloc(8);
      puVar2[3] = pvVar4;
      pfVar9 = *(float **)(*(int *)(iVar5 + 0x1c) + 0xc);
      if (pfVar9 == (float *)0x0) {
        return;
      }
    }
    *pfVar9 = fVar14;
    *(float *)(*(int *)(*(int *)(iVar5 + 0x1c) + 0xc) + 4) = fVar10;
    *(undefined4 *)(*(int *)(iVar5 + 0x1c) + 0x10) = 2;
    *(float *)(*(int *)(iVar5 + 0x1c) + 0x14) = fVar12;
    *(byte *)(iVar5 + 0x30) = *(byte *)(iVar5 + 0x30) | 8;
  }
  return;
}



// === _updatePolygon @ 0054dda0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x0054e098) */
/* WARNING: Removing unreachable block (ram,0x0054df0c) */
/* WARNING: Removing unreachable block (ram,0x0054e1c0) */
/* _updatePolygon(LottieGroup*, LottiePolyStar*, tvg::Matrix*, float, tvg::Shape*,
   LottieExpressions*) [clone .isra.82] */

void _updatePolygon(LottieGroup *param_1,LottiePolyStar *param_2,Matrix *param_3,float param_4,
                   Shape *param_5,LottieExpressions *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  Array *pAVar4;
  float *pfVar5;
  int iVar6;
  LottieExpression *pLVar7;
  Matrix *pMVar8;
  float fVar9;
  
  pAVar4 = *(Array **)(param_1 + 0x78);
  pMVar8 = param_3;
  if ((param_5 == (Shape *)0x0) ||
     (pLVar7 = *(LottieExpression **)(param_1 + 0x74), pLVar7 == (LottieExpression *)0x0)) {
    if (pAVar4 != (Array *)0x0) goto LAB_0054de74;
LAB_0054e484:
    fVar9 = *(float *)(param_1 + 0x7c);
LAB_0054e3bc:
    fVar9 = floorf(fVar9);
    if (fVar9 < DAT_0069e1bc) goto LAB_0054e3f8;
LAB_0054dfbc:
    pAVar4 = *(Array **)(param_1 + 0x38);
  }
  else {
    if ((pLVar7[0x15] != (LottieExpression)0x0) && (pLVar7[0x20] != (LottieExpression)0x0)) {
      pMVar8 = (Matrix *)_loop<tvg::Array<LottieScalarFrame<float>>>(pAVar4,(float)param_3,pLVar7);
      pAVar4 = *(Array **)(param_1 + 0x78);
    }
    if (pAVar4 == (Array *)0x0) goto LAB_0054e484;
LAB_0054de74:
    iVar2 = *(int *)(pAVar4 + 4);
    pfVar5 = *(float **)pAVar4;
    if ((iVar2 == 1) || ((float)pMVar8 <= pfVar5[1])) {
      fVar9 = *pfVar5;
      goto LAB_0054e3bc;
    }
    iVar6 = iVar2 + -1;
    if ((pfVar5 + iVar2 * 4 + -4)[1] <= (float)pMVar8) {
      fVar9 = pfVar5[iVar2 * 4 + -4];
      goto LAB_0054e3bc;
    }
    if (-1 < iVar6) {
      iVar2 = 0;
      do {
        while (iVar3 = (iVar6 - iVar2) / 2 + iVar2, (float)pMVar8 < pfVar5[iVar3 * 4 + 1]) {
          iVar6 = iVar3 + -1;
          if (iVar6 < iVar2) goto LAB_0054df40;
        }
        iVar2 = iVar3 + 1;
      } while (iVar2 <= iVar6);
    }
LAB_0054df40:
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    pfVar5 = pfVar5 + iVar6 * 4;
    fVar9 = pfVar5[1];
    if (DAT_0069dea8 < ABS(fVar9 - (float)pMVar8)) {
      fVar9 = ((float)pMVar8 - fVar9) / (pfVar5[5] - fVar9);
      if ((LottieInterpolator *)pfVar5[2] != (LottieInterpolator *)0x0) {
        fVar9 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar5[2],fVar9);
      }
      if (*(char *)(pfVar5 + 3) == '\0') {
        fVar9 = (pfVar5[4] - *pfVar5) * fVar9 + *pfVar5;
      }
      else {
        if (fVar9 < DAT_00586c20) goto LAB_0054df80;
        fVar9 = pfVar5[4];
      }
      goto LAB_0054e3bc;
    }
LAB_0054df80:
    fVar9 = floorf(*pfVar5);
    if (DAT_0069e1bc <= fVar9) goto LAB_0054dfbc;
LAB_0054e3f8:
    pAVar4 = *(Array **)(param_1 + 0x38);
  }
  pMVar8 = param_3;
  if ((((param_5 != (Shape *)0x0) &&
       (pLVar7 = *(LottieExpression **)(param_1 + 0x34), pLVar7 != (LottieExpression *)0x0)) &&
      (pLVar7[0x15] != (LottieExpression)0x0)) && (pLVar7[0x20] != (LottieExpression)0x0)) {
    pMVar8 = (Matrix *)_loop<tvg::Array<LottieScalarFrame<float>>>(pAVar4,(float)param_3,pLVar7);
    pAVar4 = *(Array **)(param_1 + 0x38);
  }
  if (pAVar4 != (Array *)0x0) {
    iVar2 = *(int *)(pAVar4 + 4);
    iVar6 = *(int *)pAVar4;
    if (((iVar2 != 1) && (*(float *)(iVar6 + 4) < (float)pMVar8)) &&
       (iVar3 = iVar2 + -1, (float)pMVar8 < *(float *)(iVar6 + iVar2 * 0x10 + -0xc))) {
      if (-1 < iVar3) {
        iVar2 = 0;
        do {
          while (iVar1 = (iVar3 - iVar2) / 2 + iVar2,
                (float)pMVar8 < *(float *)(iVar6 + iVar1 * 0x10 + 4)) {
            iVar3 = iVar1 + -1;
            if (iVar3 < iVar2) goto LAB_0054e0cc;
          }
          iVar2 = iVar1 + 1;
        } while (iVar2 <= iVar3);
      }
LAB_0054e0cc:
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      iVar6 = iVar6 + iVar3 * 0x10;
      fVar9 = *(float *)(iVar6 + 4);
      if (DAT_0069dea8 < ABS(fVar9 - (float)pMVar8)) {
        fVar9 = ((float)pMVar8 - fVar9) / (*(float *)(iVar6 + 0x14) - fVar9);
        if (*(LottieInterpolator **)(iVar6 + 8) != (LottieInterpolator *)0x0) {
          fVar9 = (float)LottieInterpolator::progress(*(LottieInterpolator **)(iVar6 + 8),fVar9);
        }
        if ((*(char *)(iVar6 + 0xc) == '\0') || (DAT_00586c20 <= fVar9)) goto LAB_0054e4b4;
      }
      pAVar4 = *(Array **)(param_1 + 0x58);
      goto joined_r0x0054e4b4;
    }
  }
LAB_0054e4b4:
  pAVar4 = *(Array **)(param_1 + 0x58);
joined_r0x0054e4b4:
  if ((((param_5 != (Shape *)0x0) &&
       (pLVar7 = *(LottieExpression **)(param_1 + 0x54), pLVar7 != (LottieExpression *)0x0)) &&
      (pLVar7[0x15] != (LottieExpression)0x0)) && (pLVar7[0x20] != (LottieExpression)0x0)) {
    param_3 = (Matrix *)_loop<tvg::Array<LottieScalarFrame<float>>>(pAVar4,(float)param_3,pLVar7);
    pAVar4 = *(Array **)(param_1 + 0x58);
  }
  if (pAVar4 != (Array *)0x0) {
    iVar2 = *(int *)(pAVar4 + 4);
    iVar6 = *(int *)pAVar4;
    if (((iVar2 != 1) && (*(float *)(iVar6 + 4) < (float)param_3)) &&
       (iVar3 = iVar2 + -1, (float)param_3 < *(float *)(iVar6 + iVar2 * 0x10 + -0xc))) {
      if (-1 < iVar3) {
        iVar2 = 0;
        do {
          while (iVar1 = (iVar3 - iVar2) / 2 + iVar2,
                (float)param_3 < *(float *)(iVar6 + iVar1 * 0x10 + 4)) {
            iVar3 = iVar1 + -1;
            if (iVar3 < iVar2) goto LAB_0054e1f4;
          }
          iVar2 = iVar1 + 1;
        } while (iVar2 <= iVar3);
      }
LAB_0054e1f4:
      if (iVar3 < 0) {
        iVar3 = 0;
      }
      iVar6 = iVar6 + iVar3 * 0x10;
      fVar9 = *(float *)(iVar6 + 4);
      if (DAT_0069dea8 < ABS(fVar9 - (float)param_3)) {
        fVar9 = ((float)param_3 - fVar9) / (*(float *)(iVar6 + 0x14) - fVar9);
        if (*(LottieInterpolator **)(iVar6 + 8) != (LottieInterpolator *)0x0) {
          fVar9 = (float)LottieInterpolator::progress(*(LottieInterpolator **)(iVar6 + 8),fVar9);
        }
        if (*(char *)(iVar6 + 0xc) == '\0') {
          halt_baddata();
        }
        if (DAT_00586c20 <= fVar9) {
          halt_baddata();
        }
      }
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === _updateTransform @ 0054ebf0 ===

/* WARNING: Removing unreachable block (ram,0x0054f970) */
/* WARNING: Removing unreachable block (ram,0x0054f490) */
/* WARNING: Removing unreachable block (ram,0x0054fdd8) */
/* WARNING: Removing unreachable block (ram,0x0054ef9c) */
/* WARNING: Removing unreachable block (ram,0x0055001c) */
/* WARNING: Removing unreachable block (ram,0x0054ed64) */
/* WARNING: Removing unreachable block (ram,0x0054ee44) */
/* WARNING: Removing unreachable block (ram,0x0054fba0) */
/* WARNING: Removing unreachable block (ram,0x0054f168) */
/* WARNING: Removing unreachable block (ram,0x0054f2dc) */
/* WARNING: Removing unreachable block (ram,0x0054f6c4) */
/* WARNING: Removing unreachable block (ram,0x0054fefc) */
/* _updateTransform(LottieTransform*, float, bool, tvg::Matrix&, unsigned char&, LottieExpressions*)
    */

undefined4
_updateTransform(LottieTransform *param_1,float param_2,bool param_3,Matrix *param_4,uchar *param_5,
                LottieExpressions *param_6)

{
  char cVar1;
  LottieTransform LVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  Array *pAVar8;
  LottieTransform *pLVar9;
  float *pfVar10;
  undefined3 in_register_00000019;
  LottieExpression *pLVar11;
  Matrix *pMVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  undefined4 local_5c;
  
  fVar14 = DAT_00586c20;
  *(undefined4 *)(param_4 + 4) = 0;
  *(float *)param_4 = fVar14;
  *(undefined4 *)(param_4 + 8) = 0;
  *(undefined4 *)(param_4 + 0xc) = 0;
  *(float *)(param_4 + 0x10) = fVar14;
  *(undefined4 *)(param_4 + 0x14) = 0;
  *(undefined4 *)(param_4 + 0x18) = 0;
  *(undefined4 *)(param_4 + 0x1c) = 0;
  *(float *)(param_4 + 0x20) = fVar14;
  if (param_1 == (LottieTransform *)0x0) {
    *param_5 = 0xff;
    return 0;
  }
  iVar6 = *(int *)(param_1 + 0x88);
  fVar14 = param_2;
  if (iVar6 == 0) {
    pAVar8 = *(Array **)(param_1 + 0x14);
    pMVar12 = param_4;
    if ((((param_6 != (LottieExpressions *)0x0) &&
         (pLVar11 = *(LottieExpression **)(param_1 + 0x10), pLVar11 != (LottieExpression *)0x0)) &&
        (pLVar11[0x15] != (LottieExpression)0x0)) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      local_5c = 0;
      param_2 = _loop<tvg::Array<LottieVectorFrame<tvg::Point>>>(pAVar8,param_2,pLVar11);
      pAVar8 = *(Array **)(param_1 + 0x14);
    }
    if (pAVar8 == (Array *)0x0) {
      local_78 = *(float *)(param_1 + 0x18);
      local_74 = *(float *)(param_1 + 0x1c);
    }
    else {
      iVar6 = *(int *)(pAVar8 + 4);
      pfVar10 = *(float **)pAVar8;
      if ((iVar6 == 1) || (param_2 <= pfVar10[2])) {
        local_78 = *pfVar10;
        local_74 = pfVar10[1];
      }
      else if (param_2 < pfVar10[iVar6 * 10 + -8]) {
        iVar6 = iVar6 + -1;
        iVar7 = 0;
        if (-1 < iVar6) {
          do {
            iVar5 = (iVar6 - iVar7) / 2 + iVar7;
            pMVar12 = (Matrix *)(pfVar10 + iVar5 * 10);
            if (*(float *)(pMVar12 + 8) <= param_2) {
              iVar7 = iVar5 + 1;
            }
            else {
              iVar6 = iVar5 + -1;
            }
          } while (iVar7 <= iVar6);
        }
        if (iVar6 < 0) {
          iVar6 = 0;
        }
        pfVar10 = pfVar10 + iVar6 * 10;
        fVar18 = pfVar10[2];
        if (ABS(fVar18 - param_2) <= DAT_0069dea8) {
LAB_00550d18:
          local_78 = *pfVar10;
          local_74 = pfVar10[1];
        }
        else {
          fVar18 = (param_2 - fVar18) / (pfVar10[0xc] - fVar18);
          if ((LottieInterpolator *)pfVar10[3] != (LottieInterpolator *)0x0) {
            local_5c = 0;
            fVar18 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[3],fVar18);
          }
          if (*(char *)((int)pfVar10 + 0x25) == '\0') {
            if (*(char *)(pfVar10 + 9) == '\0') {
              local_78 = (pfVar10[10] - *pfVar10) * fVar18 + *pfVar10;
              local_74 = (pfVar10[0xb] - pfVar10[1]) * fVar18 + pfVar10[1];
            }
            else {
              local_5c = 0;
              local_98 = *pfVar10;
              local_94 = pfVar10[1];
              local_90 = *pfVar10 + pfVar10[4];
              local_80 = pfVar10[10];
              local_8c = pfVar10[1] + pfVar10[5];
              local_7c = pfVar10[0xb];
              local_88 = pfVar10[6] + pfVar10[10];
              local_84 = pfVar10[7] + pfVar10[0xb];
              fVar18 = (float)tvg::bezAtApprox((tvg *)&local_98,(Bezier *)(fVar18 * pfVar10[8]),
                                               pfVar10[8],(float)pMVar12);
              local_5c = 0;
              tvg::bezPointAt((tvg *)&local_78,(Bezier *)&local_98,fVar18);
            }
          }
          else {
            if (fVar18 < DAT_00586c20) goto LAB_00550d18;
            local_78 = pfVar10[10];
            local_74 = pfVar10[0xb];
          }
        }
      }
      else {
        local_78 = pfVar10[iVar6 * 10 + -10];
        local_74 = pfVar10[iVar6 * 10 + -9];
      }
    }
    *(float *)(param_4 + 8) = *(float *)(param_4 + 8) + local_78;
    *(float *)(param_4 + 0x14) = *(float *)(param_4 + 0x14) + local_74;
  }
  else {
    piVar3 = *(int **)(iVar6 + 8);
    if (piVar3 == (int *)0x0) {
      piVar3 = *(int **)(iVar6 + 0x18);
      fVar18 = *(float *)(iVar6 + 0xc);
      if (piVar3 != (int *)0x0) goto LAB_0054edb0;
LAB_0054fc44:
      fVar13 = *(float *)(iVar6 + 0x1c);
    }
    else {
      iVar7 = piVar3[1];
      pfVar10 = (float *)*piVar3;
      if ((iVar7 == 1) || (param_2 <= pfVar10[1])) {
        fVar18 = *pfVar10;
      }
      else {
        iVar5 = iVar7 + -1;
        if (param_2 < (pfVar10 + iVar7 * 4 + -4)[1]) {
          iVar7 = 0;
          if (-1 < iVar5) {
            do {
              iVar4 = (iVar5 - iVar7) / 2 + iVar7;
              if (pfVar10[iVar4 * 4 + 1] <= param_2) {
                iVar7 = iVar4 + 1;
              }
              else {
                iVar5 = iVar4 + -1;
              }
            } while (iVar7 <= iVar5);
          }
          if (iVar5 < 0) {
            iVar5 = 0;
          }
          pfVar10 = pfVar10 + iVar5 * 4;
          fVar14 = pfVar10[1];
          if (ABS(fVar14 - param_2) <= DAT_0069dea8) {
LAB_0055031c:
            fVar18 = *pfVar10;
          }
          else {
            fVar14 = (param_2 - fVar14) / (pfVar10[5] - fVar14);
            if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
              local_5c = 0;
              fVar14 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar14);
              iVar6 = *(int *)(param_1 + 0x88);
            }
            if (*(char *)(pfVar10 + 3) == '\0') {
              fVar18 = (pfVar10[4] - *pfVar10) * fVar14 + *pfVar10;
            }
            else {
              if (fVar14 < DAT_00586c20) goto LAB_0055031c;
              fVar18 = pfVar10[4];
            }
          }
        }
        else {
          fVar18 = pfVar10[iVar7 * 4 + -4];
        }
      }
      piVar3 = *(int **)(iVar6 + 0x18);
      fVar14 = param_2;
      if (piVar3 == (int *)0x0) goto LAB_0054fc44;
LAB_0054edb0:
      iVar6 = piVar3[1];
      pfVar10 = (float *)*piVar3;
      if ((iVar6 == 1) || (fVar14 <= pfVar10[1])) {
        fVar13 = *pfVar10;
      }
      else {
        iVar7 = iVar6 + -1;
        if (fVar14 < (pfVar10 + iVar6 * 4 + -4)[1]) {
          iVar6 = 0;
          if (-1 < iVar7) {
            do {
              iVar5 = (iVar7 - iVar6) / 2 + iVar6;
              if (pfVar10[iVar5 * 4 + 1] <= fVar14) {
                iVar6 = iVar5 + 1;
              }
              else {
                iVar7 = iVar5 + -1;
              }
            } while (iVar6 <= iVar7);
          }
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          pfVar10 = pfVar10 + iVar7 * 4;
          fVar13 = pfVar10[1];
          if (ABS(fVar13 - fVar14) <= DAT_0069dea8) {
LAB_005502c4:
            fVar13 = *pfVar10;
          }
          else {
            fVar13 = (fVar14 - fVar13) / (pfVar10[5] - fVar13);
            if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
              local_5c = 0;
              fVar13 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar13);
            }
            if (*(char *)(pfVar10 + 3) == '\0') {
              fVar13 = (pfVar10[4] - *pfVar10) * fVar13 + *pfVar10;
            }
            else {
              if (fVar13 < DAT_00586c20) goto LAB_005502c4;
              fVar13 = pfVar10[4];
            }
          }
        }
        else {
          fVar13 = pfVar10[iVar6 * 4 + -4];
        }
      }
    }
    *(float *)(param_4 + 8) = *(float *)(param_4 + 8) + fVar18;
    *(float *)(param_4 + 0x14) = *(float *)(param_4 + 0x14) + fVar13;
  }
  fVar18 = 0.0;
  if ((((CONCAT31(in_register_00000019,param_3) != 0) &&
       (pfVar10 = *(float **)(param_1 + 0x14), pfVar10 != (float *)0x0)) &&
      (fVar13 = pfVar10[1], fVar13 != 1.4013e-45)) &&
     ((fVar15 = *pfVar10, *(float *)((int)fVar15 + 8) < fVar14 &&
      (iVar6 = (int)fVar13 + -1, fVar14 < *(float *)((int)fVar13 * 0x28 + (int)fVar15 + -0x20))))) {
    iVar7 = 0;
    if (-1 < iVar6) {
      do {
        iVar5 = (iVar6 - iVar7) / 2 + iVar7;
        if (*(float *)(iVar5 * 0x28 + (int)fVar15 + 8) <= fVar14) {
          iVar7 = iVar5 + 1;
        }
        else {
          iVar6 = iVar5 + -1;
        }
      } while (iVar7 <= iVar6);
    }
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    pfVar10 = (float *)(iVar6 * 0x28 + (int)fVar15);
    fVar18 = 0.0;
    if (*(char *)(pfVar10 + 9) != '\0') {
      fVar18 = (fVar14 - pfVar10[2]) / (pfVar10[0xc] - pfVar10[2]);
      if ((LottieInterpolator *)pfVar10[3] != (LottieInterpolator *)0x0) {
        local_5c = 0;
        fVar18 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[3],fVar18);
      }
      local_5c = 0;
      local_98 = *pfVar10;
      local_94 = pfVar10[1];
      local_90 = *pfVar10 + pfVar10[4];
      local_80 = pfVar10[10];
      local_8c = pfVar10[1] + pfVar10[5];
      local_7c = pfVar10[0xb];
      local_88 = pfVar10[10] + pfVar10[6];
      local_84 = pfVar10[0xb] + pfVar10[7];
      fVar18 = (float)tvg::bezAtApprox((tvg *)&local_98,(Bezier *)(pfVar10[8] * fVar18),pfVar10[8],
                                       fVar15);
      local_5c = 0;
      fVar18 = (float)tvg::bezAngleAt((Bezier *)&local_98,fVar18);
      fVar18 = -fVar18;
    }
  }
  pAVar8 = *(Array **)(param_1 + 0x28);
  fVar13 = fVar14;
  if ((param_6 == (LottieExpressions *)0x0) ||
     (pLVar11 = *(LottieExpression **)(param_1 + 0x24), pLVar11 == (LottieExpression *)0x0)) {
    if (pAVar8 != (Array *)0x0) goto LAB_0054ef08;
LAB_0054efe0:
    fVar14 = *(float *)(param_1 + 0x2c);
  }
  else {
    if ((pLVar11[0x15] != (LottieExpression)0x0) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      local_5c = 0;
      fVar14 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar14,pLVar11);
      pAVar8 = *(Array **)(param_1 + 0x28);
    }
    if (pAVar8 == (Array *)0x0) goto LAB_0054efe0;
LAB_0054ef08:
    iVar6 = *(int *)(pAVar8 + 4);
    pfVar10 = *(float **)pAVar8;
    if ((iVar6 == 1) || (fVar14 <= pfVar10[1])) {
      fVar14 = *pfVar10;
    }
    else {
      iVar7 = iVar6 + -1;
      if (fVar14 < (pfVar10 + iVar6 * 4 + -4)[1]) {
        iVar6 = 0;
        if (-1 < iVar7) {
          do {
            iVar5 = (iVar7 - iVar6) / 2 + iVar6;
            if (pfVar10[iVar5 * 4 + 1] <= fVar14) {
              iVar6 = iVar5 + 1;
            }
            else {
              iVar7 = iVar5 + -1;
            }
          } while (iVar6 <= iVar7);
        }
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        pfVar10 = pfVar10 + iVar7 * 4;
        fVar15 = pfVar10[1];
        if (ABS(fVar15 - fVar14) <= DAT_0069dea8) {
LAB_005501d0:
          fVar14 = *pfVar10;
        }
        else {
          fVar14 = (fVar14 - fVar15) / (pfVar10[5] - fVar15);
          if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
            local_5c = 0;
            fVar14 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar14);
          }
          if (*(char *)(pfVar10 + 3) == '\0') {
            fVar14 = (pfVar10[4] - *pfVar10) * fVar14 + *pfVar10;
          }
          else {
            if (fVar14 < DAT_00586c20) goto LAB_005501d0;
            fVar14 = pfVar10[4];
          }
        }
      }
      else {
        fVar14 = pfVar10[iVar6 * 4 + -4];
      }
    }
  }
  if (fVar18 + fVar14 != 0.0) {
    local_5c = 0;
    sincosf((fVar18 + fVar14) * DAT_00590e4c,&local_70,&local_6c);
    *(float *)param_4 = local_6c;
    *(float *)(param_4 + 4) = -local_70;
    *(float *)(param_4 + 0xc) = local_70;
    *(float *)(param_4 + 0x10) = local_6c;
  }
  iVar6 = *(int *)(param_1 + 0x8c);
  if (iVar6 != 0) {
    pAVar8 = *(Array **)(iVar6 + 0x18);
    fVar14 = fVar13;
    if ((param_6 == (LottieExpressions *)0x0) ||
       (pLVar11 = *(LottieExpression **)(iVar6 + 0x14), pLVar11 == (LottieExpression *)0x0)) {
      if (pAVar8 != (Array *)0x0) goto LAB_0054f0d4;
LAB_00550140:
      fVar18 = *(float *)(iVar6 + 0x1c);
    }
    else {
      if ((pLVar11[0x15] != (LottieExpression)0x0) && (pLVar11[0x20] != (LottieExpression)0x0)) {
        local_5c = 0;
        fVar13 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar13,pLVar11);
        pAVar8 = *(Array **)(iVar6 + 0x18);
      }
      if (pAVar8 == (Array *)0x0) goto LAB_00550140;
LAB_0054f0d4:
      iVar6 = *(int *)(pAVar8 + 4);
      pfVar10 = *(float **)pAVar8;
      if ((iVar6 == 1) || (fVar13 <= pfVar10[1])) {
        fVar18 = *pfVar10;
      }
      else {
        iVar7 = iVar6 + -1;
        if (fVar13 < (pfVar10 + iVar6 * 4 + -4)[1]) {
          iVar6 = 0;
          if (-1 < iVar7) {
            do {
              iVar5 = (iVar7 - iVar6) / 2 + iVar6;
              if (pfVar10[iVar5 * 4 + 1] <= fVar13) {
                iVar6 = iVar5 + 1;
              }
              else {
                iVar7 = iVar5 + -1;
              }
            } while (iVar6 <= iVar7);
          }
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          pfVar10 = pfVar10 + iVar7 * 4;
          fVar18 = pfVar10[1];
          if (ABS(fVar18 - fVar13) <= DAT_0069dea8) {
LAB_00550088:
            fVar18 = *pfVar10;
          }
          else {
            fVar18 = (fVar13 - fVar18) / (pfVar10[5] - fVar18);
            if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
              local_5c = 0;
              fVar18 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar18);
            }
            if (*(char *)(pfVar10 + 3) == '\0') {
              fVar18 = (pfVar10[4] - *pfVar10) * fVar18 + *pfVar10;
            }
            else {
              if (fVar18 < DAT_00586c20) goto LAB_00550088;
              fVar18 = pfVar10[4];
            }
          }
        }
        else {
          fVar18 = pfVar10[iVar6 * 4 + -4];
        }
      }
    }
    if (fVar18 != 0.0) {
      local_5c = 0;
      fVar18 = cosf(fVar18 * DAT_00590e4c);
      *(float *)param_4 = *(float *)param_4 * fVar18;
    }
    iVar6 = *(int *)(param_1 + 0x8c);
    pAVar8 = *(Array **)(iVar6 + 8);
    fVar13 = fVar14;
    if ((param_6 == (LottieExpressions *)0x0) ||
       (pLVar11 = *(LottieExpression **)(iVar6 + 4), pLVar11 == (LottieExpression *)0x0)) {
      if (pAVar8 != (Array *)0x0) goto LAB_0054fd44;
LAB_00550110:
      fVar14 = *(float *)(iVar6 + 0xc);
    }
    else {
      if ((pLVar11[0x15] != (LottieExpression)0x0) && (pLVar11[0x20] != (LottieExpression)0x0)) {
        local_5c = 0;
        fVar14 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar14,pLVar11);
        pAVar8 = *(Array **)(iVar6 + 8);
      }
      if (pAVar8 == (Array *)0x0) goto LAB_00550110;
LAB_0054fd44:
      iVar6 = *(int *)(pAVar8 + 4);
      pfVar10 = *(float **)pAVar8;
      if ((iVar6 == 1) || (fVar14 <= pfVar10[1])) {
        fVar14 = *pfVar10;
      }
      else {
        iVar7 = iVar6 + -1;
        if (fVar14 < (pfVar10 + iVar6 * 4 + -4)[1]) {
          iVar6 = 0;
          if (-1 < iVar7) {
            do {
              iVar5 = (iVar7 - iVar6) / 2 + iVar6;
              if (pfVar10[iVar5 * 4 + 1] <= fVar14) {
                iVar6 = iVar5 + 1;
              }
              else {
                iVar7 = iVar5 + -1;
              }
            } while (iVar6 <= iVar7);
          }
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          pfVar10 = pfVar10 + iVar7 * 4;
          fVar18 = pfVar10[1];
          if (ABS(fVar18 - fVar14) <= DAT_0069dea8) {
LAB_005500e0:
            fVar14 = *pfVar10;
          }
          else {
            fVar14 = (fVar14 - fVar18) / (pfVar10[5] - fVar18);
            if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
              local_5c = 0;
              fVar14 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar14);
            }
            if (*(char *)(pfVar10 + 3) == '\0') {
              fVar14 = (pfVar10[4] - *pfVar10) * fVar14 + *pfVar10;
            }
            else {
              if (fVar14 < DAT_00586c20) goto LAB_005500e0;
              fVar14 = pfVar10[4];
            }
          }
        }
        else {
          fVar14 = pfVar10[iVar6 * 4 + -4];
        }
      }
    }
    if (fVar14 != 0.0) {
      local_5c = 0;
      fVar14 = cosf(fVar14 * DAT_00590e4c);
      *(float *)(param_4 + 0x10) = *(float *)(param_4 + 0x10) * fVar14;
    }
  }
  pAVar8 = *(Array **)(param_1 + 0x70);
  fVar14 = fVar13;
  if ((param_6 == (LottieExpressions *)0x0) ||
     (pLVar11 = *(LottieExpression **)(param_1 + 0x6c), pLVar11 == (LottieExpression *)0x0)) {
    if (pAVar8 != (Array *)0x0) goto LAB_0054f248;
LAB_0054f320:
    fVar18 = *(float *)(param_1 + 0x74);
  }
  else {
    if ((pLVar11[0x15] != (LottieExpression)0x0) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      local_5c = 0;
      fVar13 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar13,pLVar11);
      pAVar8 = *(Array **)(param_1 + 0x70);
    }
    if (pAVar8 == (Array *)0x0) goto LAB_0054f320;
LAB_0054f248:
    iVar6 = *(int *)(pAVar8 + 4);
    pfVar10 = *(float **)pAVar8;
    if ((iVar6 == 1) || (fVar13 <= pfVar10[1])) {
      fVar18 = *pfVar10;
    }
    else {
      iVar7 = iVar6 + -1;
      if (fVar13 < (pfVar10 + iVar6 * 4 + -4)[1]) {
        iVar6 = 0;
        if (-1 < iVar7) {
          do {
            iVar5 = (iVar7 - iVar6) / 2 + iVar6;
            if (pfVar10[iVar5 * 4 + 1] <= fVar13) {
              iVar6 = iVar5 + 1;
            }
            else {
              iVar7 = iVar5 + -1;
            }
          } while (iVar6 <= iVar7);
        }
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        pfVar10 = pfVar10 + iVar7 * 4;
        fVar18 = pfVar10[1];
        if (ABS(fVar18 - fVar13) <= DAT_0069dea8) {
LAB_00550228:
          fVar18 = *pfVar10;
        }
        else {
          fVar18 = (fVar13 - fVar18) / (pfVar10[5] - fVar18);
          if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
            local_5c = 0;
            fVar18 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar18);
          }
          if (*(char *)(pfVar10 + 3) == '\0') {
            fVar18 = (pfVar10[4] - *pfVar10) * fVar18 + *pfVar10;
          }
          else {
            if (fVar18 < DAT_00586c20) goto LAB_00550228;
            fVar18 = pfVar10[4];
          }
        }
      }
      else {
        fVar18 = pfVar10[iVar6 * 4 + -4];
      }
    }
  }
  if (fVar18 != 0.0) {
    local_5c = 0;
    fVar13 = fVar14;
    fVar18 = fmodf(fVar18,DAT_00585fe4);
    if (ABS(fVar18 - DAT_006a0fec) < DAT_0069e1c0) {
      return 0;
    }
    if (ABS(fVar18 + DAT_006a0fec) < DAT_0069e1c0) {
      return 0;
    }
    pAVar8 = *(Array **)(param_1 + 0x80);
    fVar14 = fVar13;
    if ((((param_6 != (LottieExpressions *)0x0) &&
         (pLVar11 = *(LottieExpression **)(param_1 + 0x7c), pLVar11 != (LottieExpression *)0x0)) &&
        (pLVar11[0x15] != (LottieExpression)0x0)) && (pLVar11[0x20] != (LottieExpression)0x0)) {
      local_5c = 0;
      fVar13 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar8,fVar13,pLVar11);
      pAVar8 = *(Array **)(param_1 + 0x80);
    }
    if (pAVar8 == (Array *)0x0) {
      fVar13 = *(float *)(param_1 + 0x84);
    }
    else {
      iVar6 = *(int *)(pAVar8 + 4);
      pfVar10 = *(float **)pAVar8;
      if ((iVar6 == 1) || (fVar13 <= pfVar10[1])) {
        fVar13 = *pfVar10;
      }
      else {
        iVar7 = iVar6 + -1;
        if (fVar13 < (pfVar10 + iVar6 * 4 + -4)[1]) {
          iVar6 = 0;
          if (-1 < iVar7) {
            do {
              iVar5 = (iVar7 - iVar6) / 2 + iVar6;
              if (pfVar10[iVar5 * 4 + 1] <= fVar13) {
                iVar6 = iVar5 + 1;
              }
              else {
                iVar7 = iVar5 + -1;
              }
            } while (iVar6 <= iVar7);
          }
          if (iVar7 < 0) {
            iVar7 = 0;
          }
          pfVar10 = pfVar10 + iVar7 * 4;
          fVar15 = pfVar10[1];
          if (ABS(fVar15 - fVar13) <= DAT_0069dea8) {
LAB_00551008:
            fVar13 = *pfVar10;
          }
          else {
            fVar13 = (fVar13 - fVar15) / (pfVar10[5] - fVar15);
            if ((LottieInterpolator *)pfVar10[2] != (LottieInterpolator *)0x0) {
              local_5c = 0;
              fVar13 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[2],fVar13);
            }
            if (*(char *)(pfVar10 + 3) == '\0') {
              fVar13 = (pfVar10[4] - *pfVar10) * fVar13 + *pfVar10;
            }
            else {
              if (fVar13 < DAT_00586c20) goto LAB_00551008;
              fVar13 = pfVar10[4];
            }
          }
        }
        else {
          fVar13 = pfVar10[iVar6 * 4 + -4];
        }
      }
    }
    local_5c = 0;
    fVar15 = DAT_00590e4c;
    fVar16 = tanf(-(fVar18 * DAT_00590e4c));
    local_5c = 0;
    fVar18 = DAT_00585fe4;
    fVar13 = fmodf(fVar13,DAT_00585fe4);
    if (DAT_0069e1c0 <= ABS(fVar13)) {
      fVar17 = fVar13 * fVar15;
      local_68 = *(float *)param_4;
      fVar20 = *(float *)(param_4 + 0xc);
      fVar19 = *(float *)(param_4 + 4);
      local_64 = *(float *)(param_4 + 0x10);
      if ((DAT_0069e1c0 <= ABS(fVar13 - fVar18)) && (DAT_0069e1c0 <= ABS(fVar13 + fVar18))) {
        if ((ABS(fVar13 - DAT_006a0fec) < DAT_0069e1c0) ||
           (ABS(fVar13 + DAT_006a0fec) < DAT_0069e1c0)) {
          local_5c = 0;
          fVar18 = sinf(fVar17);
          fVar16 = fVar18 * fVar18 * fVar16;
          *(float *)param_4 = local_68 - fVar16 * fVar19;
          *(float *)(param_4 + 0xc) = fVar20 - fVar16 * local_64;
        }
        else {
          local_5c = 0;
          fVar18 = cosf(fVar17);
          local_5c = 0;
          fVar13 = sinf(-fVar17);
          fVar15 = fVar18 * fVar13 * fVar16;
          fVar13 = fVar13 * fVar13 * fVar16;
          fVar16 = fVar18 * fVar18 * fVar16;
          fVar18 = fVar15 + DAT_00586c20;
          fVar15 = DAT_00586c20 - fVar15;
          *(float *)param_4 = fVar15 * local_68 - fVar13 * fVar19;
          *(float *)(param_4 + 0xc) = fVar15 * fVar20 - fVar13 * local_64;
          *(float *)(param_4 + 4) = fVar16 * local_68 + fVar18 * fVar19;
          *(float *)(param_4 + 0x10) = fVar16 * fVar20 + fVar18 * local_64;
        }
        goto LAB_0054f4f4;
      }
    }
    else {
      local_68 = *(float *)param_4;
      fVar20 = *(float *)(param_4 + 0xc);
      fVar19 = *(float *)(param_4 + 4);
      local_64 = *(float *)(param_4 + 0x10);
    }
    local_5c = 0;
    fVar18 = cosf(fVar13 * fVar15);
    fVar16 = fVar18 * fVar18 * fVar16;
    *(float *)(param_4 + 4) = fVar16 * local_68 + fVar19;
    *(float *)(param_4 + 0x10) = fVar16 * fVar20 + local_64;
  }
LAB_0054f4f4:
  piVar3 = *(int **)(param_1 + 0x38);
  fVar18 = fVar14;
  if ((((param_6 == (LottieExpressions *)0x0) || (iVar6 = *(int *)(param_1 + 0x34), iVar6 == 0)) ||
      (*(char *)(iVar6 + 0x15) == '\0')) ||
     ((cVar1 = *(char *)(iVar6 + 0x20), cVar1 == '\0' || (*(float *)(iVar6 + 0x1c) <= fVar14)))) {
LAB_0054f620:
    if (piVar3 != (int *)0x0) goto LAB_0054f628;
    fVar14 = *(float *)(param_1 + 0x3c);
    fVar13 = *(float *)(param_1 + 0x40);
  }
  else {
    iVar7 = *piVar3;
    fVar13 = *(float *)(iVar7 + 8);
    if (fVar13 <= fVar14) {
      fVar15 = *(float *)(piVar3[1] * 0x14 + iVar7 + -0xc);
      if (fVar15 <= fVar14) {
        if (cVar1 == '\x01') {
          local_5c = 0;
          fVar14 = fmodf(fVar14 - fVar13,fVar15 - fVar13);
          iVar7 = *piVar3;
          piVar3 = *(int **)(param_1 + 0x38);
          fVar14 = fVar14 + *(float *)(*(int *)(iVar6 + 0x18) * 0x14 + iVar7 + 8);
        }
        else if (cVar1 == '\x05') {
          local_5c = 0;
          fVar14 = fmodf(fVar14 - fVar13,
                         *(float *)(((piVar3[1] + -1) - *(int *)(iVar6 + 0x18)) * 0x14 + iVar7 + 8)
                         - fVar13);
          iVar6 = *piVar3;
          piVar3 = *(int **)(param_1 + 0x38);
          fVar14 = fVar14 + *(float *)(iVar6 + 8);
        }
        goto LAB_0054f620;
      }
    }
LAB_0054f628:
    iVar6 = piVar3[1];
    pfVar10 = (float *)*piVar3;
    if ((iVar6 == 1) || (fVar14 <= pfVar10[2])) {
      fVar14 = *pfVar10;
      fVar13 = pfVar10[1];
    }
    else if (fVar14 < pfVar10[iVar6 * 5 + -3]) {
      iVar6 = iVar6 + -1;
      iVar7 = 0;
      if (-1 < iVar6) {
        do {
          iVar5 = (iVar6 - iVar7) / 2 + iVar7;
          if (pfVar10[iVar5 * 5 + 2] <= fVar14) {
            iVar7 = iVar5 + 1;
          }
          else {
            iVar6 = iVar5 + -1;
          }
        } while (iVar7 <= iVar6);
      }
      if (iVar6 < 0) {
        iVar6 = 0;
      }
      pfVar10 = pfVar10 + iVar6 * 5;
      fVar13 = pfVar10[2];
      if (ABS(fVar13 - fVar14) <= DAT_0069dea8) {
LAB_005503d8:
        fVar14 = *pfVar10;
        fVar13 = pfVar10[1];
      }
      else {
        fVar13 = (fVar14 - fVar13) / (pfVar10[7] - fVar13);
        if ((LottieInterpolator *)pfVar10[3] != (LottieInterpolator *)0x0) {
          local_5c = 0;
          fVar13 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[3],fVar13);
        }
        if (*(char *)(pfVar10 + 4) == '\0') {
          fVar14 = (pfVar10[5] - *pfVar10) * fVar13 + *pfVar10;
          fVar13 = (pfVar10[6] - pfVar10[1]) * fVar13 + pfVar10[1];
        }
        else {
          if (fVar13 < DAT_00586c20) goto LAB_005503d8;
          fVar14 = pfVar10[5];
          fVar13 = pfVar10[6];
        }
      }
    }
    else {
      fVar14 = pfVar10[iVar6 * 5 + -5];
      fVar13 = pfVar10[iVar6 * 5 + -4];
    }
  }
  fVar15 = fVar14 * DAT_0069e1c0;
  fVar16 = fVar13 * DAT_0069e1c0;
  if (fVar15 != DAT_00586c20) {
    *(float *)param_4 = *(float *)param_4 * fVar15;
    *(float *)(param_4 + 0xc) = *(float *)(param_4 + 0xc) * fVar15;
  }
  if (fVar16 != DAT_00586c20) {
    *(float *)(param_4 + 0x10) = *(float *)(param_4 + 0x10) * fVar16;
    *(float *)(param_4 + 4) = *(float *)(param_4 + 4) * fVar16;
  }
  piVar3 = *(int **)(param_1 + 0x4c);
  fVar15 = fVar18;
  if ((((param_6 == (LottieExpressions *)0x0) || (iVar6 = *(int *)(param_1 + 0x48), iVar6 == 0)) ||
      (*(char *)(iVar6 + 0x15) == '\0')) ||
     ((cVar1 = *(char *)(iVar6 + 0x20), cVar1 == '\0' || (*(float *)(iVar6 + 0x1c) <= fVar18)))) {
LAB_0054f8cc:
    if (piVar3 != (int *)0x0) goto LAB_0054f8d4;
    fVar16 = *(float *)(param_1 + 0x50);
    fVar18 = *(float *)(param_1 + 0x54);
  }
  else {
    iVar7 = *piVar3;
    fVar16 = *(float *)(iVar7 + 8);
    if (fVar16 <= fVar18) {
      fVar17 = *(float *)(piVar3[1] * 0x14 + iVar7 + -0xc);
      if (fVar17 <= fVar18) {
        if (cVar1 == '\x01') {
          local_5c = 0;
          fVar18 = fmodf(fVar18 - fVar16,fVar17 - fVar16);
          iVar7 = *piVar3;
          piVar3 = *(int **)(param_1 + 0x4c);
          fVar18 = fVar18 + *(float *)(*(int *)(iVar6 + 0x18) * 0x14 + iVar7 + 8);
        }
        else if (cVar1 == '\x05') {
          local_5c = 0;
          fVar18 = fmodf(fVar18 - fVar16,
                         *(float *)(((piVar3[1] + -1) - *(int *)(iVar6 + 0x18)) * 0x14 + iVar7 + 8)
                         - fVar16);
          iVar6 = *piVar3;
          piVar3 = *(int **)(param_1 + 0x4c);
          fVar18 = fVar18 + *(float *)(iVar6 + 8);
        }
        goto LAB_0054f8cc;
      }
    }
LAB_0054f8d4:
    iVar6 = piVar3[1];
    pfVar10 = (float *)*piVar3;
    if ((iVar6 == 1) || (fVar18 <= pfVar10[2])) {
      fVar16 = *pfVar10;
      fVar18 = pfVar10[1];
    }
    else if (fVar18 < pfVar10[iVar6 * 5 + -3]) {
      iVar6 = iVar6 + -1;
      iVar7 = 0;
      if (-1 < iVar6) {
        do {
          iVar5 = (iVar6 - iVar7) / 2 + iVar7;
          if (pfVar10[iVar5 * 5 + 2] <= fVar18) {
            iVar7 = iVar5 + 1;
          }
          else {
            iVar6 = iVar5 + -1;
          }
        } while (iVar7 <= iVar6);
      }
      if (iVar6 < 0) {
        iVar6 = 0;
      }
      pfVar10 = pfVar10 + iVar6 * 5;
      fVar16 = pfVar10[2];
      if (ABS(fVar16 - fVar18) <= DAT_0069dea8) {
LAB_00550378:
        fVar16 = *pfVar10;
        fVar18 = pfVar10[1];
      }
      else {
        fVar18 = (fVar18 - fVar16) / (pfVar10[7] - fVar16);
        if ((LottieInterpolator *)pfVar10[3] != (LottieInterpolator *)0x0) {
          local_5c = 0;
          fVar18 = (float)LottieInterpolator::progress((LottieInterpolator *)pfVar10[3],fVar18);
        }
        if (*(char *)(pfVar10 + 4) == '\0') {
          fVar16 = (pfVar10[5] - *pfVar10) * fVar18 + *pfVar10;
          fVar18 = (pfVar10[6] - pfVar10[1]) * fVar18 + pfVar10[1];
        }
        else {
          if (fVar18 < DAT_00586c20) goto LAB_00550378;
          fVar16 = pfVar10[5];
          fVar18 = pfVar10[6];
        }
      }
    }
    else {
      fVar16 = pfVar10[iVar6 * 5 + -5];
      fVar18 = pfVar10[iVar6 * 5 + -4];
    }
  }
  if ((fVar16 != 0.0) || (fVar18 != 0.0)) {
    *(float *)(param_4 + 8) =
         *(float *)(param_4 + 8) + -fVar16 * *(float *)param_4 + -fVar18 * *(float *)(param_4 + 4);
    *(float *)(param_4 + 0x14) =
         *(float *)(param_4 + 0x14) +
         -fVar16 * *(float *)(param_4 + 0xc) + -fVar18 * *(float *)(param_4 + 0x10);
  }
  if ((fVar14 == 0.0) || (fVar13 == 0.0)) {
    *param_5 = '\0';
    return 1;
  }
  pAVar8 = *(Array **)(param_1 + 0x60);
  if ((((param_6 != (LottieExpressions *)0x0) &&
       (pLVar11 = *(LottieExpression **)(param_1 + 0x5c), pLVar11 != (LottieExpression *)0x0)) &&
      (pLVar11[0x15] != (LottieExpression)0x0)) && (pLVar11[0x20] != (LottieExpression)0x0)) {
    local_5c = 0;
    fVar15 = _loop<tvg::Array<LottieScalarFrame<unsigned_char>>>(pAVar8,fVar15,pLVar11);
    pAVar8 = *(Array **)(param_1 + 0x60);
  }
  if (pAVar8 == (Array *)0x0) {
    LVar2 = param_1[100];
  }
  else {
    iVar6 = *(int *)(pAVar8 + 4);
    pLVar9 = *(LottieTransform **)pAVar8;
    if ((iVar6 == 1) || (fVar15 <= *(float *)(pLVar9 + 4))) {
      LVar2 = *pLVar9;
    }
    else {
      iVar7 = iVar6 + -1;
      if (fVar15 < *(float *)(pLVar9 + iVar6 * 0x10 + -0x10 + 4)) {
        iVar6 = 0;
        if (-1 < iVar7) {
          do {
            iVar5 = (iVar7 - iVar6) / 2 + iVar6;
            if (*(float *)(pLVar9 + iVar5 * 0x10 + 4) <= fVar15) {
              iVar6 = iVar5 + 1;
            }
            else {
              iVar7 = iVar5 + -1;
            }
          } while (iVar6 <= iVar7);
        }
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        pLVar9 = pLVar9 + iVar7 * 0x10;
        fVar14 = *(float *)(pLVar9 + 4);
        if (DAT_0069dea8 < ABS(fVar14 - fVar15)) {
          fVar14 = (fVar15 - fVar14) / (*(float *)(pLVar9 + 0x14) - fVar14);
          if (*(LottieInterpolator **)(pLVar9 + 8) != (LottieInterpolator *)0x0) {
            local_5c = 0;
            fVar14 = (float)LottieInterpolator::progress
                                      (*(LottieInterpolator **)(pLVar9 + 8),fVar14);
          }
          if (pLVar9[0xc] == (LottieTransform)0x0) {
            fVar14 = (float)(int)((uint)(byte)pLVar9[0x10] - (uint)(byte)*pLVar9) * fVar14 +
                     (float)(byte)*pLVar9;
            if (fVar14 < DAT_0069e1bc) {
              LVar2 = SUB41((int)fVar14,0);
            }
            else {
              LVar2 = SUB41((int)(fVar14 - DAT_0069e1bc),0);
            }
            goto LAB_005508e4;
          }
          if (DAT_00586c20 <= fVar14) {
            LVar2 = pLVar9[0x10];
            goto LAB_005508e4;
          }
        }
        LVar2 = *pLVar9;
      }
      else {
        LVar2 = pLVar9[iVar6 * 0x10 + -0x10];
      }
    }
  }
LAB_005508e4:
  *param_5 = (uchar)LVar2;
  return 1;
}



// === _updateTransform @ 005513cc ===

/* _updateTransform(LottieLayer*, float, LottieExpressions*) */

void _updateTransform(LottieLayer *param_1,float param_2,LottieExpressions *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  Matrix *pMVar6;
  Matrix *pMVar7;
  LottieLayer *pLVar8;
  LottieTransform *pLVar9;
  Matrix local_58 [32];
  Matrix aMStack_38 [12];
  undefined4 local_2c;
  
  if ((param_1 != (LottieLayer *)0x0) &&
     (local_2c = 0, DAT_0069dea8 < ABS(*(float *)(param_1 + 0x80) - param_2))) {
    pLVar8 = *(LottieLayer **)(param_1 + 0x2c);
    pLVar9 = *(LottieTransform **)(param_1 + 0x44);
    pMVar7 = (Matrix *)(param_1 + 0x84);
    if (pLVar8 == (LottieLayer *)0x0) {
      _updateTransform(pLVar9,param_2,(bool)param_1[0xad],pMVar7,(uchar *)(param_1 + 0xa8),param_3);
    }
    else {
      _updateTransform(pLVar8,param_2,param_3);
      local_2c = 0;
      pMVar6 = (Matrix *)(pLVar8 + 0x84);
      _updateTransform(pLVar9,param_2,(bool)param_1[0xad],pMVar7,(uchar *)(param_1 + 0xa8),param_3);
      iVar1 = mathIdentity(pMVar6);
      if (iVar1 == 0) {
        iVar1 = mathIdentity(pMVar7);
        if (iVar1 != 0) {
          do {
            uVar5 = *(undefined4 *)pMVar6;
            uVar4 = *(undefined4 *)(pMVar6 + 4);
            uVar3 = *(undefined4 *)(pMVar6 + 8);
            uVar2 = *(undefined4 *)(pMVar6 + 0xc);
            pMVar6 = pMVar6 + 0x10;
            *(undefined4 *)pMVar7 = uVar5;
            *(undefined4 *)(pMVar7 + 4) = uVar4;
            *(undefined4 *)(pMVar7 + 8) = uVar3;
            *(undefined4 *)(pMVar7 + 0xc) = uVar2;
            pMVar7 = pMVar7 + 0x10;
          } while (pMVar6 != (Matrix *)(pLVar8 + 0xa4));
          *(undefined4 *)pMVar7 = *(undefined4 *)pMVar6;
          *(float *)(param_1 + 0x80) = param_2;
          return;
        }
        mathMultiply(local_58,pMVar6);
        pMVar6 = local_58;
        do {
          uVar5 = *(undefined4 *)pMVar6;
          uVar4 = *(undefined4 *)(pMVar6 + 4);
          uVar3 = *(undefined4 *)(pMVar6 + 8);
          uVar2 = *(undefined4 *)(pMVar6 + 0xc);
          pMVar6 = pMVar6 + 0x10;
          *(undefined4 *)pMVar7 = uVar5;
          *(undefined4 *)(pMVar7 + 4) = uVar4;
          *(undefined4 *)(pMVar7 + 8) = uVar3;
          *(undefined4 *)(pMVar7 + 0xc) = uVar2;
          pMVar7 = pMVar7 + 0x10;
        } while (pMVar6 != aMStack_38);
        local_2c = 0;
        *(undefined4 *)pMVar7 = *(undefined4 *)pMVar6;
        *(float *)(param_1 + 0x80) = param_2;
        return;
      }
    }
    *(float *)(param_1 + 0x80) = param_2;
  }
  return;
}



// === _updateStar @ 005515e8 ===

/* WARNING: Removing unreachable block (ram,0x00551b64) */
/* WARNING: Removing unreachable block (ram,0x005518e4) */
/* WARNING: Removing unreachable block (ram,0x00551754) */
/* WARNING: Removing unreachable block (ram,0x00551a24) */
/* WARNING: Removing unreachable block (ram,0x00551ca0) */
/* _updateStar(LottieGroup*, LottiePolyStar*, tvg::Matrix*, float, float, tvg::Shape*,
   LottieExpressions*) [clone .isra.119] */

void _updateStar(LottieGroup *param_1,LottiePolyStar *param_2,Matrix *param_3,float param_4,
                float param_5,Shape *param_6,LottieExpressions *param_7)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  Array *pAVar6;
  float *pfVar7;
  uint uVar8;
  uint uVar9;
  LottieExpression *pLVar10;
  undefined4 *puVar11;
  uint uVar12;
  Point *pPVar13;
  Point *this;
  Point *pPVar14;
  int iVar15;
  float fVar16;
  Matrix *pMVar17;
  double dVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  ulonglong uVar29;
  double dVar30;
  float fVar31;
  float fVar33;
  float fVar34;
  float fVar35;
  ulonglong uVar36;
  float fVar37;
  ulonglong uVar38;
  Point *local_c8 [2];
  float local_c0;
  float local_bc;
  char *local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  char *local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  int local_74;
  float local_70;
  int local_6c;
  float local_68;
  float local_64;
  undefined4 local_5c;
  ulonglong uVar32;
  
  pAVar6 = *(Array **)(param_1 + 0x78);
  fVar16 = param_4;
  if ((param_6 == (Shape *)0x0) ||
     (pLVar10 = *(LottieExpression **)(param_1 + 0x74), pLVar10 == (LottieExpression *)0x0)) {
    if (pAVar6 != (Array *)0x0) goto LAB_005516bc;
LAB_00551d7c:
    local_90 = *(float *)(param_1 + 0x7c);
  }
  else {
    if ((pLVar10[0x15] != (LottieExpression)0x0) && (pLVar10[0x20] != (LottieExpression)0x0)) {
      local_5c = 0;
      local_b8 = (char *)param_4;
      fVar16 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar6,param_4,pLVar10);
      pAVar6 = *(Array **)(param_1 + 0x78);
      param_4 = (float)local_b8;
    }
    if (pAVar6 == (Array *)0x0) goto LAB_00551d7c;
LAB_005516bc:
    iVar5 = *(int *)(pAVar6 + 4);
    pfVar7 = *(float **)pAVar6;
    if ((iVar5 == 1) || (fVar16 <= pfVar7[1])) {
      local_90 = *pfVar7;
    }
    else {
      iVar15 = iVar5 + -1;
      if (fVar16 < (pfVar7 + iVar5 * 4 + -4)[1]) {
        if (-1 < iVar15) {
          iVar5 = 0;
          do {
            while (iVar3 = (iVar15 - iVar5) / 2 + iVar5, fVar16 < pfVar7[iVar3 * 4 + 1]) {
              iVar15 = iVar3 + -1;
              if (iVar15 < iVar5) goto LAB_00551788;
            }
            iVar5 = iVar3 + 1;
          } while (iVar5 <= iVar15);
        }
LAB_00551788:
        if (iVar15 < 0) {
          iVar15 = 0;
        }
        pfVar7 = pfVar7 + iVar15 * 4;
        fVar33 = pfVar7[1];
        if (ABS(fVar33 - fVar16) <= DAT_0069dea8) {
          local_90 = *pfVar7;
        }
        else {
          fVar16 = (fVar16 - fVar33) / (pfVar7[5] - fVar33);
          if ((LottieInterpolator *)pfVar7[2] != (LottieInterpolator *)0x0) {
            local_5c = 0;
            local_b8 = (char *)param_4;
            LottieInterpolator::progress((LottieInterpolator *)pfVar7[2],fVar16);
            param_4 = (float)local_b8;
          }
          if (*(char *)(pfVar7 + 3) == '\0') {
            local_90 = (pfVar7[4] - *pfVar7) * fVar16 + *pfVar7;
          }
          else if (DAT_00586c20 <= fVar16) {
            local_90 = pfVar7[4];
          }
          else {
            local_90 = *pfVar7;
          }
        }
      }
      else {
        local_90 = pfVar7[iVar5 * 4 + -4];
      }
    }
  }
  pAVar6 = *(Array **)(param_1 + 0x28);
  fVar16 = param_4;
  if ((param_6 == (Shape *)0x0) ||
     (pLVar10 = *(LottieExpression **)(param_1 + 0x24), pLVar10 == (LottieExpression *)0x0)) {
    if (pAVar6 != (Array *)0x0) goto LAB_0055184c;
LAB_00551d48:
    local_b0 = *(float *)(param_1 + 0x2c);
LAB_00551db8:
    pAVar6 = *(Array **)(param_1 + 0x38);
  }
  else {
    if ((pLVar10[0x15] != (LottieExpression)0x0) && (pLVar10[0x20] != (LottieExpression)0x0)) {
      local_5c = 0;
      local_b8 = (char *)param_4;
      fVar16 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar6,param_4,pLVar10);
      pAVar6 = *(Array **)(param_1 + 0x28);
      param_4 = (float)local_b8;
    }
    if (pAVar6 == (Array *)0x0) goto LAB_00551d48;
LAB_0055184c:
    iVar5 = *(int *)(pAVar6 + 4);
    pfVar7 = *(float **)pAVar6;
    if ((iVar5 == 1) || (fVar16 <= pfVar7[1])) {
      local_b0 = *pfVar7;
      goto LAB_00551db8;
    }
    iVar15 = iVar5 + -1;
    if ((pfVar7 + iVar5 * 4 + -4)[1] <= fVar16) {
      local_b0 = pfVar7[iVar5 * 4 + -4];
      goto LAB_00551db8;
    }
    if (-1 < iVar15) {
      iVar5 = 0;
      do {
        while (iVar3 = (iVar15 - iVar5) / 2 + iVar5, fVar16 < pfVar7[iVar3 * 4 + 1]) {
          iVar15 = iVar3 + -1;
          if (iVar15 < iVar5) goto LAB_00551918;
        }
        iVar5 = iVar3 + 1;
      } while (iVar5 <= iVar15);
    }
LAB_00551918:
    if (iVar15 < 0) {
      iVar15 = 0;
    }
    pfVar7 = pfVar7 + iVar15 * 4;
    fVar33 = pfVar7[1];
    if (DAT_0069dea8 < ABS(fVar33 - fVar16)) {
      fVar16 = (fVar16 - fVar33) / (pfVar7[5] - fVar33);
      if ((LottieInterpolator *)pfVar7[2] != (LottieInterpolator *)0x0) {
        local_5c = 0;
        local_b8 = (char *)param_4;
        LottieInterpolator::progress((LottieInterpolator *)pfVar7[2],fVar16);
        param_4 = (float)local_b8;
      }
      if (*(char *)(pfVar7 + 3) == '\0') {
        local_b0 = (pfVar7[4] - *pfVar7) * fVar16 + *pfVar7;
      }
      else {
        if (fVar16 < DAT_00586c20) goto LAB_00551954;
        local_b0 = pfVar7[4];
      }
      goto LAB_00551db8;
    }
LAB_00551954:
    local_b0 = *pfVar7;
    pAVar6 = *(Array **)(param_1 + 0x38);
  }
  fVar16 = param_4;
  if ((((param_6 != (Shape *)0x0) &&
       (pLVar10 = *(LottieExpression **)(param_1 + 0x34), pLVar10 != (LottieExpression *)0x0)) &&
      (pLVar10[0x15] != (LottieExpression)0x0)) && (pLVar10[0x20] != (LottieExpression)0x0)) {
    local_5c = 0;
    local_b8 = (char *)param_4;
    fVar16 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar6,param_4,pLVar10);
    pAVar6 = *(Array **)(param_1 + 0x38);
    param_4 = (float)local_b8;
  }
  if (pAVar6 == (Array *)0x0) {
    local_ac = *(float *)(param_1 + 0x3c);
LAB_00551e44:
    pAVar6 = *(Array **)(param_1 + 0x48);
  }
  else {
    iVar5 = *(int *)(pAVar6 + 4);
    pfVar7 = *(float **)pAVar6;
    if ((iVar5 == 1) || (fVar16 <= pfVar7[1])) {
      local_ac = *pfVar7;
      goto LAB_00551e44;
    }
    iVar15 = iVar5 + -1;
    if ((pfVar7 + iVar5 * 4 + -4)[1] <= fVar16) {
      local_ac = pfVar7[iVar5 * 4 + -4];
      goto LAB_00551e44;
    }
    if (-1 < iVar15) {
      iVar5 = 0;
      do {
        while (iVar3 = (iVar15 - iVar5) / 2 + iVar5, fVar16 < pfVar7[iVar3 * 4 + 1]) {
          iVar15 = iVar3 + -1;
          if (iVar15 < iVar5) goto LAB_00551a58;
        }
        iVar5 = iVar3 + 1;
      } while (iVar5 <= iVar15);
    }
LAB_00551a58:
    if (iVar15 < 0) {
      iVar15 = 0;
    }
    pfVar7 = pfVar7 + iVar15 * 4;
    fVar33 = pfVar7[1];
    if (DAT_0069dea8 < ABS(fVar33 - fVar16)) {
      fVar16 = (fVar16 - fVar33) / (pfVar7[5] - fVar33);
      if ((LottieInterpolator *)pfVar7[2] != (LottieInterpolator *)0x0) {
        local_5c = 0;
        local_b8 = (char *)param_4;
        LottieInterpolator::progress((LottieInterpolator *)pfVar7[2],fVar16);
        param_4 = (float)local_b8;
      }
      if (*(char *)(pfVar7 + 3) == '\0') {
        local_ac = (pfVar7[4] - *pfVar7) * fVar16 + *pfVar7;
      }
      else {
        if (fVar16 < DAT_00586c20) goto LAB_00551a94;
        local_ac = pfVar7[4];
      }
      goto LAB_00551e44;
    }
LAB_00551a94:
    local_ac = *pfVar7;
    pAVar6 = *(Array **)(param_1 + 0x48);
  }
  fVar16 = param_4;
  if (((param_6 != (Shape *)0x0) &&
      (pLVar10 = *(LottieExpression **)(param_1 + 0x44), pLVar10 != (LottieExpression *)0x0)) &&
     ((pLVar10[0x15] != (LottieExpression)0x0 && (pLVar10[0x20] != (LottieExpression)0x0)))) {
    local_5c = 0;
    local_b8 = (char *)param_4;
    fVar16 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar6,param_4,pLVar10);
    pAVar6 = *(Array **)(param_1 + 0x48);
    param_4 = (float)local_b8;
  }
  if (pAVar6 == (Array *)0x0) {
    local_94 = *(float *)(param_1 + 0x4c);
LAB_00551ecc:
    pAVar6 = *(Array **)(param_1 + 0x58);
    local_94 = local_94 * DAT_0069e1c0;
  }
  else {
    iVar5 = *(int *)(pAVar6 + 4);
    pfVar7 = *(float **)pAVar6;
    if ((iVar5 == 1) || (fVar16 <= pfVar7[1])) {
      local_94 = *pfVar7;
      goto LAB_00551ecc;
    }
    iVar15 = iVar5 + -1;
    if ((pfVar7 + iVar5 * 4 + -4)[1] <= fVar16) {
      local_94 = pfVar7[iVar5 * 4 + -4];
      goto LAB_00551ecc;
    }
    if (-1 < iVar15) {
      iVar5 = 0;
      do {
        while (iVar3 = (iVar15 - iVar5) / 2 + iVar5, fVar16 < pfVar7[iVar3 * 4 + 1]) {
          iVar15 = iVar3 + -1;
          if (iVar15 < iVar5) goto LAB_00551b98;
        }
        iVar5 = iVar3 + 1;
      } while (iVar5 <= iVar15);
    }
LAB_00551b98:
    if (iVar15 < 0) {
      iVar15 = 0;
    }
    pfVar7 = pfVar7 + iVar15 * 4;
    fVar33 = pfVar7[1];
    if (DAT_0069dea8 < ABS(fVar33 - fVar16)) {
      fVar16 = (fVar16 - fVar33) / (pfVar7[5] - fVar33);
      if ((LottieInterpolator *)pfVar7[2] != (LottieInterpolator *)0x0) {
        local_5c = 0;
        local_b8 = (char *)param_4;
        LottieInterpolator::progress((LottieInterpolator *)pfVar7[2],fVar16);
        param_4 = (float)local_b8;
      }
      if (*(char *)(pfVar7 + 3) == '\0') {
        local_94 = (pfVar7[4] - *pfVar7) * fVar16 + *pfVar7;
      }
      else {
        if (fVar16 < DAT_00586c20) goto LAB_00551bd4;
        local_94 = pfVar7[4];
      }
      goto LAB_00551ecc;
    }
LAB_00551bd4:
    pAVar6 = *(Array **)(param_1 + 0x58);
    local_94 = *pfVar7 * DAT_0069e1c0;
  }
  if ((((param_6 != (Shape *)0x0) &&
       (pLVar10 = *(LottieExpression **)(param_1 + 0x54), pLVar10 != (LottieExpression *)0x0)) &&
      (pLVar10[0x15] != (LottieExpression)0x0)) && (pLVar10[0x20] != (LottieExpression)0x0)) {
    local_5c = 0;
    param_4 = _loop<tvg::Array<LottieScalarFrame<float>>>(pAVar6,param_4,pLVar10);
    pAVar6 = *(Array **)(param_1 + 0x58);
  }
  if (pAVar6 == (Array *)0x0) {
    local_98 = *(float *)(param_1 + 0x5c);
  }
  else {
    iVar5 = *(int *)(pAVar6 + 4);
    pfVar7 = *(float **)pAVar6;
    if ((iVar5 == 1) || (param_4 <= pfVar7[1])) {
      local_98 = *pfVar7;
    }
    else {
      iVar15 = iVar5 + -1;
      if (param_4 < (pfVar7 + iVar5 * 4 + -4)[1]) {
        if (-1 < iVar15) {
          iVar5 = 0;
          do {
            while (iVar3 = (iVar15 - iVar5) / 2 + iVar5, param_4 < pfVar7[iVar3 * 4 + 1]) {
              iVar15 = iVar3 + -1;
              if (iVar15 < iVar5) goto LAB_00551cd8;
            }
            iVar5 = iVar3 + 1;
          } while (iVar5 <= iVar15);
        }
LAB_00551cd8:
        if (iVar15 < 0) {
          iVar15 = 0;
        }
        pfVar7 = pfVar7 + iVar15 * 4;
        fVar16 = pfVar7[1];
        if (ABS(fVar16 - param_4) <= DAT_0069dea8) {
LAB_00551d18:
          local_98 = *pfVar7;
        }
        else {
          fVar16 = (param_4 - fVar16) / (pfVar7[5] - fVar16);
          if ((LottieInterpolator *)pfVar7[2] != (LottieInterpolator *)0x0) {
            local_5c = 0;
            LottieInterpolator::progress((LottieInterpolator *)pfVar7[2],fVar16);
          }
          if (*(char *)(pfVar7 + 3) == '\0') {
            local_98 = (pfVar7[4] - *pfVar7) * fVar16 + *pfVar7;
          }
          else {
            if (fVar16 < DAT_00586c20) goto LAB_00551d18;
            local_98 = pfVar7[4];
          }
        }
      }
      else {
        local_98 = pfVar7[iVar5 * 4 + -4];
      }
    }
  }
  fVar16 = local_90;
  local_5c = 0;
  local_68 = DAT_006a0fe0 / local_90;
  local_98 = local_98 * DAT_0069e1c0;
  local_74 = 0x580000;
  local_a8 = (char *)(local_68 * DAT_00585fd4);
  local_70 = floorf(local_90);
  local_5c = 0;
  local_70 = fVar16 - local_70;
  fVar16 = ceilf(fVar16);
  fVar16 = fVar16 + fVar16;
  if (fVar16 < DAT_0069e1bc) {
    uVar12 = (uint)fVar16;
    if (param_1[10] != (LottieGroup)0x0) goto LAB_005527f8;
LAB_00552018:
    local_b4 = DAT_00586c20;
  }
  else {
    uVar12 = (int)(fVar16 - DAT_0069e1bc) | 0x80000000;
    if (param_1[10] == (LottieGroup)0x0) goto LAB_00552018;
LAB_005527f8:
    local_b4 = DAT_00590e44;
  }
  fVar16 = ABS(local_94);
  if (((float)param_3 <= DAT_00586c20) ||
     ((DAT_0069dea8 < fVar16 && (DAT_0069dea8 < ABS(local_98))))) {
    local_80 = ABS(local_70);
    local_6c = 0;
    this = (Point *)param_5;
    if (local_80 <= DAT_0069dea8) goto LAB_00552760;
LAB_005520dc:
    local_5c = 0;
    local_b8 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
    fVar33 = (DAT_00586c20 - local_70) * (float)local_a8 * local_b4 - DAT_00590e50;
    fVar31 = local_70;
    fVar37 = local_b4;
    sincosf(fVar33,&local_c0,&local_bc);
    local_9c = (local_ac - local_b0) * fVar31 + local_b0;
    fVar33 = local_68 * fVar31 * *(float *)(local_74 + 0x5fd4) * fVar37 + fVar33;
    fVar31 = local_bc * local_9c;
    fVar37 = local_c0 * local_9c;
  }
  else {
    local_5c = 0;
    tvg::Shape::gen((Shape *)local_c8);
    local_80 = ABS(local_70);
    local_6c = 1;
    this = local_c8[0];
    if (DAT_0069dea8 < local_80) goto LAB_005520dc;
LAB_00552760:
    local_b8 = "y-build/vectorprime/localgui/lvgl/src/misc/lv_event.c";
    fVar37 = -local_ac;
    fVar31 = local_ac * DAT_006a0fe4;
    local_9c = 0.0;
    fVar33 = (float)local_a8 * local_b4 - DAT_00590e50;
  }
  uVar36 = (ulonglong)(uint)fVar37;
  uVar32 = (ulonglong)(uint)fVar31;
  uVar29 = (ulonglong)(uint)fVar33;
  puVar11 = *(undefined4 **)(this + 8);
  if ((DAT_0069dea8 < fVar16) || (local_5c = 0, DAT_0069dea8 < ABS(local_98))) {
    local_5c = 0;
    uVar8 = uVar12 * 3 + 2;
    if ((uint)puVar11[5] < uVar8) {
      puVar11[5] = uVar8;
      pvVar4 = realloc((void *)puVar11[3],uVar8 * 8);
      puVar11[3] = pvVar4;
      puVar11 = *(undefined4 **)(this + 8);
    }
    bVar1 = true;
    if (uVar12 + 3 <= (uint)puVar11[2]) goto joined_r0x005521d8;
  }
  else {
    uVar8 = uVar12 + 2;
    if ((uint)puVar11[5] < uVar8) {
      puVar11[5] = uVar8;
      pvVar4 = realloc((void *)puVar11[3],uVar8 * 8);
      puVar11[3] = pvVar4;
      puVar11 = *(undefined4 **)(this + 8);
    }
    bVar1 = false;
    if (uVar12 + 3 <= (uint)puVar11[2]) goto joined_r0x005521d8;
  }
  puVar11[2] = uVar12 + 3;
  pvVar4 = realloc((void *)*puVar11,(uVar12 + 3) * 4);
  *puVar11 = pvVar4;
joined_r0x005521d8:
  fVar33 = (float)uVar36;
  fVar16 = (float)uVar32;
  if (param_2 == (LottiePolyStar *)0x0) {
    local_5c = 0;
    tvg::Shape::moveTo((Shape *)this,fVar16,fVar33);
  }
  else {
    local_5c = 0;
    fVar31 = fVar16 * *(float *)(param_2 + 0xc);
    fVar16 = fVar16 * *(float *)param_2 + fVar33 * *(float *)(param_2 + 4) + *(float *)(param_2 + 8)
    ;
    tvg::Shape::moveTo((Shape *)this,fVar16,
                       fVar31 + fVar33 * *(float *)(param_2 + 0x10) + *(float *)(param_2 + 0x14));
  }
  if (uVar12 != 0) {
    local_a4 = ABS(local_9c);
    uVar8 = 0;
    bVar2 = false;
    local_64 = *(float *)(local_74 + 0x5fd4);
    local_7c = *(float *)(local_b8 + 0xe50);
    fVar33 = local_b0;
    local_a0 = DAT_0069dea8;
    local_78 = DAT_006a0ff0;
    while( true ) {
      fVar37 = (float)uVar29;
      fVar19 = (float)uVar32;
      fVar31 = (float)uVar36;
      if (local_a4 <= local_a0) {
        local_b8 = local_a8;
        fVar20 = fVar33;
      }
      else {
        local_b8 = local_a8;
        if (uVar8 == uVar12 - 2) {
          local_b8 = (char *)(local_68 * local_70 * local_64);
        }
        fVar20 = local_9c;
        if (uVar8 != uVar12 - 1) {
          fVar20 = fVar33;
        }
      }
      local_5c = 0;
      sincosf(fVar37,&local_c0,&local_bc);
      fVar16 = local_bc * fVar20;
      uVar32 = (ulonglong)(uint)fVar16;
      fVar20 = local_c0 * fVar20;
      if (bVar1) {
        local_5c = 0;
        fVar16 = atan2f(fVar31,fVar19);
        local_5c = 0;
        local_84 = local_b4 * local_7c;
        sincosf(fVar16 - local_84,&local_c0,&local_bc);
        local_5c = 0;
        local_88 = local_bc;
        local_8c = local_c0;
        fVar16 = atan2f(fVar20,(float)uVar32);
        local_5c = 0;
        sincosf(fVar16 - local_84,&local_c0,&local_bc);
        fVar16 = local_98;
        fVar22 = local_94;
        fVar27 = local_ac;
        if (bVar2) {
          fVar16 = local_94;
          fVar22 = local_98;
          fVar27 = local_b0;
        }
        fVar27 = fVar27 * fVar16 * local_78;
        fVar34 = fVar33 * fVar22 * local_78;
        fVar16 = (local_88 * fVar27) / local_90;
        fVar33 = (local_bc * fVar34) / local_90;
        fVar22 = (local_8c * fVar27) / local_90;
        fVar27 = (local_c0 * fVar34) / local_90;
        if ((DAT_0069dea8 < local_80) && ((uVar8 == 0 || (uVar8 == uVar12 - 1)))) {
          fVar16 = fVar16 * local_70;
          fVar22 = fVar22 * local_70;
          fVar33 = fVar33 * local_70;
          fVar27 = fVar27 * local_70;
        }
        fVar31 = fVar31 - fVar22;
        fVar16 = fVar19 - fVar16;
        fVar27 = fVar20 + fVar27;
        fVar22 = (float)uVar32;
        fVar33 = fVar22 + fVar33;
        fVar19 = fVar20;
        if (param_2 != (LottiePolyStar *)0x0) {
          fVar35 = *(float *)(param_2 + 4);
          fVar24 = *(float *)(param_2 + 0x10);
          fVar23 = *(float *)param_2;
          fVar28 = fVar27 * fVar35;
          fVar25 = *(float *)(param_2 + 0xc);
          fVar19 = fVar16 * fVar25;
          fVar21 = *(float *)(param_2 + 8);
          fVar34 = fVar22 * fVar25;
          fVar16 = fVar16 * fVar23 + fVar31 * fVar35 + fVar21;
          fVar26 = *(float *)(param_2 + 0x14);
          fVar31 = fVar19 + fVar31 * fVar24 + fVar26;
          fVar27 = fVar33 * fVar25 + fVar27 * fVar24 + fVar26;
          fVar33 = fVar33 * fVar23 + fVar28 + fVar21;
          fVar22 = fVar22 * fVar23 + fVar20 * fVar35 + fVar21;
          fVar19 = fVar34 + fVar20 * fVar24 + fVar26;
        }
        local_5c = 0;
        tvg::Shape::cubicTo((Shape *)this,fVar16,fVar31,fVar33,fVar27,fVar22,fVar19);
      }
      else {
        fVar33 = fVar20;
        if (param_2 != (LottiePolyStar *)0x0) {
          fVar33 = fVar16 * *(float *)(param_2 + 0xc);
          fVar16 = fVar16 * *(float *)param_2 + fVar20 * *(float *)(param_2 + 4) +
                   *(float *)(param_2 + 8);
          fVar33 = fVar33 + fVar20 * *(float *)(param_2 + 0x10) + *(float *)(param_2 + 0x14);
        }
        local_5c = 0;
        tvg::Shape::lineTo((Shape *)this,fVar16,fVar33);
      }
      local_5c = 0;
      uVar8 = uVar8 + 1;
      bVar2 = (bool)(bVar2 ^ 1);
      uVar29 = (ulonglong)(uint)(local_b4 * (float)local_b8 + fVar37);
      if (uVar12 == uVar8) break;
      uVar36 = (ulonglong)(uint)fVar20;
      uVar32 = uVar32 & 0xffffffff;
      fVar33 = local_ac;
      if (!bVar2) {
        fVar33 = local_b0;
      }
    }
  }
  tvg::Shape::close((Shape *)this,(int)fVar16);
  if (local_6c != 0) {
    uVar12 = tvg::Shape::pathCommands((Shape *)this,(PathCommand **)0x0);
    local_c8[0] = (Point *)0x0;
    uVar8 = tvg::Shape::pathCoords((Shape *)this,local_c8);
    fVar16 = (float)*(undefined8 *)(local_c8[0] + 0xc) - *(float *)(local_c8[0] + 0x14);
    fVar33 = *(float *)(local_c8[0] + 8) -
             (float)((ulonglong)*(undefined8 *)(local_c8[0] + 0xc) >> 0x20);
    fVar16 = fVar33 * fVar33 + fVar16 * fVar16;
    fVar33 = SQRT(fVar16);
    if (fVar16 < 0.0) {
      local_5c = 0;
      sqrtf(fVar16);
    }
    uVar29 = 0;
    if (0.0 < fVar33) {
      pMVar17 = (Matrix *)(fVar33 * *(float *)(local_74 + 0x5fd4));
      if ((float)param_3 <= (float)pMVar17) {
        pMVar17 = param_3;
      }
      uVar29 = (ulonglong)(uint)(((float)pMVar17 * DAT_006a0ff4) / fVar33);
    }
    local_5c = 0;
    puVar11 = *(undefined4 **)((int)param_5 + 8);
    if (bVar1) {
      dVar30 = (double)uVar12;
      dVar18 = dVar30 * DAT_00612558 + 0.0;
      if (dVar18 < DAT_00614a18) {
        uVar12 = (uint)dVar18;
      }
      else {
        uVar12 = (int)(dVar18 - DAT_00614a18) | 0x80000000;
      }
      local_5c = 0;
      uVar12 = uVar12 + puVar11[1];
      if ((uint)puVar11[2] < uVar12) {
        puVar11[2] = uVar12;
        pvVar4 = realloc((void *)*puVar11,uVar12 * 4);
        *puVar11 = pvVar4;
        puVar11 = *(undefined4 **)((int)param_5 + 8);
      }
      dVar18 = dVar30 * DAT_00614a10 + 0.0;
      if (dVar18 < DAT_00614a18) {
        uVar12 = (uint)dVar18;
      }
      else {
        uVar12 = (int)(dVar18 - DAT_00614a18) | 0x80000000;
      }
      local_5c = 0;
      uVar12 = uVar12 + puVar11[4];
      if ((uint)puVar11[5] < uVar12) {
        puVar11[5] = uVar12;
        pvVar4 = realloc((void *)puVar11[3],uVar12 * 8);
        puVar11[3] = pvVar4;
      }
      local_5c = 0;
      iVar5 = 3;
      if (DAT_0069dea8 < ABS(local_98)) {
        iVar5 = 0;
      }
      fVar16 = *(float *)(local_c8[0] + iVar5 * 8);
      uVar12 = iVar5 + 1;
      tvg::Shape::moveTo((Shape *)param_5,fVar16,*(float *)(local_c8[0] + iVar5 * 8 + 4));
      if (uVar12 < uVar8) {
        iVar15 = uVar12 * 8;
        do {
          if (uVar12 < uVar8 - iVar5) {
            pPVar14 = local_c8[0] + iVar15 + 0x20;
            pPVar13 = local_c8[0] + iVar15 + 0x28;
          }
          else {
            pPVar14 = local_c8[0] + 0x10;
            pPVar13 = local_c8[0] + 0x18;
          }
          local_5c = 0;
          fVar33 = *(float *)(local_c8[0] + iVar15);
          fVar31 = *(float *)(local_c8[0] + iVar15 + 4);
          fVar16 = *(float *)(local_c8[0] + iVar15 + 0x10);
          fVar19 = *(float *)(local_c8[0] + iVar15 + 0x10 + 4);
          fVar37 = (float)uVar29;
          fVar20 = (fVar16 - fVar33) * fVar37;
          fVar22 = (fVar19 - fVar31) * fVar37;
          uVar12 = uVar12 + 6;
          fVar34 = (fVar19 - *(float *)(pPVar14 + 4)) * fVar37;
          fVar37 = (fVar16 - *(float *)pPVar14) * fVar37;
          fVar35 = fVar16 - fVar20;
          local_b8 = (char *)(fVar19 - fVar22);
          fVar27 = fVar16 - (fVar20 + fVar20);
          fVar20 = fVar19 - (fVar22 + fVar22);
          fVar22 = fVar16 - fVar37;
          fVar16 = fVar16 - (fVar37 + fVar37);
          fVar37 = fVar19 - (fVar34 + fVar34);
          fVar19 = fVar19 - fVar34;
          tvg::Shape::cubicTo((Shape *)param_5,fVar33,fVar31,fVar27,fVar20,fVar27,fVar20);
          local_5c = 0;
          tvg::Shape::cubicTo((Shape *)param_5,fVar35,(float)local_b8,fVar22,fVar19,fVar16,fVar37);
          local_5c = 0;
          iVar15 = iVar15 + 0x30;
          tvg::Shape::cubicTo((Shape *)param_5,fVar16,fVar37,*(float *)pPVar14,
                              *(float *)(pPVar14 + 4),*(float *)pPVar13,*(float *)(pPVar13 + 4));
        } while (uVar12 < uVar8);
      }
    }
    else {
      uVar9 = uVar12 * 2 + puVar11[1];
      if ((uint)puVar11[2] < uVar9) {
        puVar11[2] = uVar9;
        pvVar4 = realloc((void *)*puVar11,uVar9 * 4);
        *puVar11 = pvVar4;
        puVar11 = *(undefined4 **)((int)param_5 + 8);
      }
      uVar12 = uVar12 * 4 + puVar11[4];
      if ((uint)puVar11[5] < uVar12) {
        puVar11[5] = uVar12;
        pvVar4 = realloc((void *)puVar11[3],uVar12 * 8);
        puVar11[3] = pvVar4;
      }
      local_5c = 0;
      fVar16 = (*(float *)(local_c8[0] + 8) - *(float *)local_c8[0]) * (float)uVar29;
      uVar36 = (ulonglong)(uint)fVar16;
      fVar33 = (*(float *)(local_c8[0] + 0xc) - *(float *)(local_c8[0] + 4)) * (float)uVar29;
      uVar38 = (ulonglong)(uint)fVar33;
      local_b8 = (char *)(fVar16 + fVar16);
      uVar32 = (ulonglong)(uint)(fVar33 + fVar33);
      fVar16 = (float)local_b8 + *(float *)local_c8[0];
      tvg::Shape::moveTo((Shape *)param_5,fVar16,fVar33 + fVar33 + *(float *)(local_c8[0] + 4));
      if (1 < uVar8) {
        uVar12 = 1;
        iVar5 = 8;
        while( true ) {
          pPVar13 = local_c8[0] + iVar5 + 8;
          if (uVar12 == uVar8 - 1) {
            pPVar13 = local_c8[0] + 8;
          }
          local_5c = 0;
          fVar33 = (float)*(undefined8 *)(local_c8[0] + iVar5);
          fVar16 = fVar33 - (float)uVar36;
          fVar31 = (float)((ulonglong)*(undefined8 *)(local_c8[0] + iVar5) >> 0x20);
          fVar34 = fVar31 - (float)uVar38;
          fVar22 = (fVar33 - *(float *)pPVar13) * (float)uVar29;
          fVar20 = (fVar31 - *(float *)(pPVar13 + 4)) * (float)uVar29;
          uVar12 = uVar12 + 1;
          fVar37 = fVar33 - (float)local_b8;
          local_b8 = (char *)(fVar33 - fVar22);
          fVar33 = fVar33 - (fVar22 + fVar22);
          fVar19 = fVar31 - fVar20;
          fVar27 = fVar31 - (fVar20 + fVar20);
          tvg::Shape::lineTo((Shape *)param_5,fVar37,fVar31 - (float)uVar32);
          local_5c = 0;
          uVar36 = (ulonglong)(uint)-fVar22;
          tvg::Shape::cubicTo((Shape *)param_5,fVar16,fVar34,(float)local_b8,fVar19,fVar33,fVar27);
          local_5c = 0;
          fVar20 = -fVar20;
          uVar38 = (ulonglong)(uint)fVar20;
          if (uVar8 == uVar12) break;
          uVar32 = (ulonglong)(uint)(fVar20 + fVar20);
          local_b8 = (char *)((float)uVar36 + (float)uVar36);
          iVar5 = iVar5 + 8;
        }
      }
    }
    tvg::Shape::close((Shape *)param_5,(int)fVar16);
    tvg::Shape::~Shape((Shape *)this);
  }
  return;
}



// === _updateChildren @ 005533f4 ===

/* WARNING: Removing unreachable block (ram,0x00554898) */
/* WARNING: Removing unreachable block (ram,0x00555470) */
/* WARNING: Removing unreachable block (ram,0x00553abc) */
/* WARNING: Removing unreachable block (ram,0x0055376c) */
/* WARNING: Removing unreachable block (ram,0x00554a54) */
/* WARNING: Removing unreachable block (ram,0x00555be4) */
/* WARNING: Removing unreachable block (ram,0x00554560) */
/* WARNING: Removing unreachable block (ram,0x00554cd0) */
/* _updateChildren(LottieGroup*, float, tvg::Inlist<RenderContext>&, LottieExpressions*) */

void _updateChildren(LottieGroup *param_1,float param_2,Inlist *param_3,LottieExpressions *param_4)

{
  bool bVar1;
  RenderContext RVar2;
  LottieTrimpath LVar3;
  char cVar4;
  ushort uVar5;
  Inlist IVar6;
  uchar uVar7;
  LottieGenericProperty<RGB24> LVar8;
  RenderContext *pRVar9;
  uchar uVar10;
  uchar uVar11;
  undefined1 uVar12;
  LottieObject **ppLVar13;
  LottieTrimpath *pLVar14;
  int iVar15;
  undefined4 *puVar16;
  Matrix *pMVar17;
  undefined4 *puVar18;
  LottieTrimpath **ppLVar19;
  LottieTrimpath *pLVar20;
  int iVar21;
  int iVar22;
  undefined4 *puVar23;
  undefined4 *puVar24;
  Point *pPVar25;
  EVP_PKEY_CTX *pEVar26;
  float *pfVar27;
  Matrix *pMVar28;
  LottieTrimpath **ppLVar29;
  Array *pAVar30;
  int iVar31;
  void *pvVar32;
  Array *pAVar33;
  LottieStroke *pLVar34;
  Shape *pSVar35;
  RenderTransform *this;
  float *pfVar36;
  LottieTrimpath *pLVar37;
  uint uVar38;
  LottiePolyStar *pLVar39;
  LottieTrimpath *pLVar40;
  LottieExpression *pLVar41;
  Scene *pSVar42;
  LottieTrimpath *pLVar43;
  undefined4 uVar44;
  undefined4 uVar45;
  uint uVar46;
  int *piVar47;
  Paint *pPVar48;
  LottieObject *pLVar49;
  LottieGradient *pLVar50;
  undefined4 *puVar51;
  EVP_PKEY_CTX *pEVar52;
  PathCommand *pPVar53;
  LottieObject *pLVar54;
  LottieObject **ppLVar55;
  uint uVar56;
  void *pvVar57;
  char *pcVar58;
  float *pfVar59;
  char *__s;
  code *pcVar60;
  float fVar61;
  float fVar62;
  undefined4 uVar63;
  undefined4 uVar64;
  float fVar65;
  float in_f12;
  ulonglong uVar66;
  LottieTrimpath *pLVar67;
  ulonglong uVar68;
  ulonglong uVar69;
  float fVar70;
  ulonglong uVar71;
  Matrix *in_stack_fffffe94;
  Matrix *in_stack_fffffe98;
  LottieTrimpath *local_158;
  LottieTrimpath *local_154;
  LottieTrimpath *local_150;
  LottieTrimpath *local_14c [2];
  float local_144;
  float local_140;
  float local_13c;
  LottieTrimpath *local_138;
  LottieTrimpath *local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  LottieTrimpath *pLStack_114;
  LottieGenericProperty<RGB24> local_110 [4];
  uchar local_10c;
  uchar local_108;
  float local_104;
  float local_100;
  float local_fc;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  LottieTrimpath *local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  Scene *local_d4;
  Matrix local_d0 [32];
  Matrix aMStack_b0 [8];
  undefined4 local_a8;
  undefined4 local_a4;
  LottieTrimpath *local_a0;
  RenderContext *local_9c;
  LottieTrimpath *local_98;
  Scene *local_94;
  Point *local_90;
  uint local_8c;
  LottieTrimpath *local_88;
  float local_84;
  int local_80;
  int local_7c;
  float local_78;
  undefined **local_74;
  float local_70;
  float local_6c;
  int local_68;
  undefined4 local_5c;
  
  local_84 = DAT_0069dea8;
  local_5c = 0;
  ppLVar13 = *(LottieObject ***)(param_1 + 0x10);
  local_9c = *(RenderContext **)param_3;
  local_74 = &PTR__handleLinearX1Attr_006a0000;
  ppLVar55 = ppLVar13 + *(int *)(param_1 + 0x14) + -1;
  *(LottieObject ***)(local_9c + 0x10) = ppLVar55;
  local_6c = DAT_00586c20;
  iVar21 = *(int *)(local_9c + 4);
  local_7c = 0x580000;
  uVar66 = (ulonglong)(uint)param_2;
  *(int *)param_3 = iVar21;
  pLVar43 = (LottieTrimpath *)param_4;
  do {
    if (iVar21 == 0) {
      *(undefined4 *)(param_3 + 4) = 0;
    }
    *(LottieGroup *)(local_9c + 0x21) = param_1[0x1c];
    if (ppLVar13 <= ppLVar55) {
      do {
        pRVar9 = local_9c;
        pLVar14 = (LottieTrimpath *)*ppLVar55;
        fVar61 = (float)uVar66;
        local_a0 = pLVar14;
        switch(pLVar14[8]) {
        default:
          goto switchD_00553514_caseD_0;
        case (LottieTrimpath)0x2:
          if (*(int *)(pLVar14 + 0x14) != 0) {
            RVar2 = local_9c[0x21];
            pcVar60 = *(code **)(*(int *)pLVar14 + 0xc);
            *(undefined4 *)(pLVar14 + 0xc) = *(undefined4 *)(param_1 + 0xc);
            pLVar14[0x1c] = (LottieTrimpath)((byte)pLVar14[0x1c] | (byte)RVar2);
            iVar21 = (*pcVar60)(pLVar14);
            if ((iVar21 != 0) && (*(int *)(pRVar9 + 0xc) == 0)) {
              _draw(param_1 + 0xc,*(RenderContext **)(local_9c + 8));
            }
            local_158 = (LottieTrimpath *)0x0;
            local_154 = (LottieTrimpath *)0x0;
            iVar21 = (**(code **)(*(int *)local_a0 + 0xc))();
            pLVar14 = operator_new(0x24);
            local_5c = 0;
            *(undefined4 *)(pLVar14 + 8) = 0;
            *(undefined4 *)(pLVar14 + 0xc) = 0;
            *(undefined4 *)(pLVar14 + 0x10) = 0;
            *(undefined4 *)(pLVar14 + 0x14) = 0;
            *(undefined4 *)(pLVar14 + 0x18) = 0;
            *(undefined4 *)(pLVar14 + 0x1c) = 0;
            pLVar14[0x20] = (LottieTrimpath)0x0;
            pLVar14[0x21] = (LottieTrimpath)0x0;
            pLVar14[0x22] = (LottieTrimpath)0x1;
            if (iVar21 == 0) {
              uVar63 = tvg::Paint::duplicate(*(Paint **)(local_9c + 8));
              *(undefined4 *)(pLVar14 + 8) = uVar63;
            }
            else {
              uVar64 = *(undefined4 *)(local_9c + 8);
              uVar63 = *(undefined4 *)(local_9c + 0xc);
              pLVar14[0x22] = (LottieTrimpath)0x0;
              *(undefined4 *)(pLVar14 + 8) = uVar64;
              *(undefined4 *)(pLVar14 + 0xc) = uVar63;
            }
            pRVar9 = local_9c;
            if (*(int *)(local_9c + 0x14) != 0) {
                    /* try { // try from 005538d4 to 005538db has its CatchHandler @ 00557428 */
              puVar18 = operator_new(0x28);
              *puVar18 = 0;
              puVar18[1] = 0;
              puVar18[8] = 0;
              *(undefined2 *)(puVar18 + 9) = 0;
              *(undefined4 **)(pLVar14 + 0x14) = puVar18;
              puVar51 = *(undefined4 **)(pRVar9 + 0x14);
              puVar18[2] = 0;
              puVar18[3] = 0;
              puVar18[4] = 0;
              puVar18[5] = 0;
              puVar18[6] = 0;
              puVar18[7] = 0;
              *(undefined1 *)((int)puVar18 + 0x26) = 0;
              *(undefined1 *)((int)puVar18 + 0x27) = 0;
              puVar24 = puVar51;
              do {
                puVar23 = puVar24;
                puVar16 = puVar18;
                uVar44 = puVar23[1];
                uVar64 = puVar23[2];
                uVar63 = puVar23[3];
                puVar24 = puVar23 + 4;
                *puVar16 = *puVar23;
                puVar16[1] = uVar44;
                puVar16[2] = uVar64;
                puVar16[3] = uVar63;
                puVar18 = puVar16 + 4;
              } while (puVar24 != puVar51 + 8);
              uVar63 = puVar23[5];
              puVar16[4] = *puVar24;
              puVar16[5] = uVar63;
            }
            *(undefined4 *)(pLVar14 + 0x1c) = *(undefined4 *)(local_9c + 0x1c);
            if (local_154 == (LottieTrimpath *)0x0) {
              *(undefined4 *)pLVar14 = 0;
              *(undefined4 *)(pLVar14 + 4) = 0;
              local_158 = pLVar14;
            }
            else {
              *(LottieTrimpath **)((int)local_154 + 4) = pLVar14;
              *(LottieTrimpath **)pLVar14 = local_154;
              *(undefined4 *)(pLVar14 + 4) = 0;
            }
            local_5c = 0;
            pLVar43 = (LottieTrimpath *)param_4;
            local_154 = pLVar14;
            _updateChildren((LottieGroup *)local_a0,(float)uVar66,(Inlist *)&local_158,param_4);
            pLVar14 = local_158;
            while (local_158 = pLVar14, pLVar14 != (LottieTrimpath *)0x0) {
              local_158 = *(LottieTrimpath **)(pLVar14 + 4);
              if ((pLVar14[0x22] != (LottieTrimpath)0x0) &&
                 (*(Shape **)(pLVar14 + 8) != (Shape *)0x0)) {
                tvg::Shape::~Shape(*(Shape **)(pLVar14 + 8));
              }
              operator_delete(*(void **)(pLVar14 + 0x14),0x28);
              free(*(void **)(pLVar14 + 0x18));
              operator_delete(pLVar14,0x24);
              pLVar14 = local_158;
            }
          }
          break;
        case (LottieTrimpath)0x3:
          iVar21 = (**(code **)(*(int *)param_1 + 0xc))(param_1);
          pRVar9 = local_9c;
          if (iVar21 == 0) {
            local_5c = 0;
            *(undefined4 *)(local_9c + 0xc) = 0;
            pLVar43 = (LottieTrimpath *)&local_134;
            in_stack_fffffe94 = (Matrix *)param_4;
            iVar21 = _updateTransform((LottieTransform *)local_a0,(float)uVar66,false,
                                      (Matrix *)pLVar43,(uchar *)&local_d4,param_4);
            if (iVar21 != 0) {
              pPVar48 = *(Paint **)(pRVar9 + 8);
              iVar21 = *(int *)(pPVar48 + 4);
              this = *(RenderTransform **)(iVar21 + 4);
              if (this == (RenderTransform *)0x0) {
LAB_005566a8:
                ppLVar29 = &local_158;
                ppLVar19 = &local_134;
                do {
                  pLVar20 = *ppLVar19;
                  pLVar43 = ppLVar19[1];
                  pLVar37 = ppLVar19[2];
                  pLVar14 = ppLVar19[3];
                  ppLVar19 = ppLVar19 + 4;
                  *ppLVar29 = pLVar20;
                  ppLVar29[1] = pLVar43;
                  ppLVar29[2] = pLVar37;
                  ppLVar29[3] = pLVar14;
                  ppLVar29 = ppLVar29 + 4;
                } while (ppLVar19 != &pLStack_114);
                *ppLVar29 = *ppLVar19;
              }
              else {
                tvg::RenderTransform::update(this);
                pMVar28 = *(Matrix **)(iVar21 + 4);
                pPVar48 = *(Paint **)(local_9c + 8);
                if (pMVar28 == (Matrix *)0x0) goto LAB_005566a8;
                mathMultiply((Matrix *)&local_158,pMVar28);
              }
              tvg::Paint::transform(pPVar48,(Matrix *)&local_158);
              pRVar9 = local_9c;
              tvg::Paint::opacity(*(Paint **)(local_9c + 8),
                                  (uchar)((uint)*(byte *)(*(int *)(*(Paint **)(local_9c + 8) + 4) +
                                                         0x14) * ((uint)local_d4 & 0xff) + 0xff >> 8
                                         ));
              pfVar36 = *(float **)(*(int *)(*(int *)(pRVar9 + 8) + 8) + 0x1c);
              if (pfVar36 == (float *)0x0) goto switchD_00553514_caseD_0;
              local_5c = 0;
              if (0.0 < *pfVar36) {
                in_f12 = (float)local_134 * (float)local_134 + local_130 * local_130;
                local_a0 = (LottieTrimpath *)SQRT(in_f12);
                if (in_f12 < 0.0) {
                  local_5c = 0;
                  sqrtf(in_f12);
                }
                local_5c = 0;
                if ((float)local_a0 <= *(float *)(local_7c + 0x6c20)) goto switchD_00553514_caseD_0;
                local_5c = 0;
                pSVar35 = *(Shape **)(local_9c + 8);
                fVar61 = (float)tvg::Shape::strokeWidth(pSVar35);
                local_5c = 0;
                tvg::Shape::stroke(pSVar35,fVar61 / (float)local_a0);
              }
            }
          }
          else {
            pLVar43 = *(LottieTrimpath **)(local_9c + 0x18);
            if (pLVar43 == (LottieTrimpath *)0x0) {
              pLVar43 = malloc(0x24);
              *(LottieTrimpath **)(local_9c + 0x18) = pLVar43;
            }
            local_5c = 0;
            in_stack_fffffe94 = (Matrix *)param_4;
            _updateTransform((LottieTransform *)local_a0,(float)uVar66,false,(Matrix *)pLVar43,
                             (uchar *)&local_d4,param_4);
          }
          break;
        case (LottieTrimpath)0x4:
          iVar21 = _fragmented(ppLVar55,param_3,local_9c);
          pRVar9 = local_9c;
          if (iVar21 == 0) {
            local_5c = 0;
            pLVar49 = *ppLVar55;
            *(undefined4 *)(local_9c + 0xc) = 0;
            LottieGenericProperty<RGB24>::operator()
                      ((LottieGenericProperty<RGB24> *)&local_158,(float)(pLVar49 + 0xc));
            pSVar35 = *(Shape **)(pRVar9 + 8);
            IVar6 = local_158._0_1_;
            uVar7 = (uchar)local_154;
            LVar3 = local_150._0_1_;
            pLVar43 = (LottieTrimpath *)((uint)local_150 & 0xff);
            fVar61 = (float)uVar66;
            if (((param_4 != (LottieExpressions *)0x0) &&
                (pLVar41 = *(LottieExpression **)(pLVar49 + 0x28),
                pLVar41 != (LottieExpression *)0x0)) &&
               ((pLVar41[0x15] != (LottieExpression)0x0 && (pLVar41[0x20] != (LottieExpression)0x0))
               )) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieScalarFrame<unsigned_char>>>
                                 (*(Array **)(pLVar49 + 0x2c),fVar61,pLVar41);
            }
            local_5c = 0;
            uVar10 = LottieGenericProperty<unsigned_char>::operator()
                               ((LottieGenericProperty<unsigned_char> *)(pLVar49 + 0x24),fVar61);
            tvg::Shape::fill(pSVar35,(uchar)IVar6,uVar7,(uchar)LVar3,uVar10);
            pRVar9 = local_9c;
            tvg::Shape::fill(*(Shape **)(local_9c + 8),*(undefined4 *)(pLVar49 + 0x34));
            local_5c = 0;
            fVar61 = (float)tvg::Shape::strokeWidth(*(Shape **)(pRVar9 + 8));
            local_5c = 0;
            if (fVar61 <= 0.0) goto switchD_00553514_caseD_0;
            tvg::Shape::order(*(Shape **)(pRVar9 + 8),true);
          }
          break;
        case (LottieTrimpath)0x5:
          iVar21 = _fragmented(ppLVar55,param_3,local_9c);
          if (iVar21 == 0) {
            pLVar49 = *ppLVar55;
            *(undefined4 *)(local_9c + 0xc) = 0;
            pLVar54 = pLVar49 + 0xc;
            if (param_4 == (LottieExpressions *)0x0) {
              local_5c = 0;
              LottieGenericProperty<RGB24>::operator()(local_110,(float)pLVar54);
              uVar10 = local_108;
              uVar7 = local_10c;
              LVar8 = local_110[0];
              local_5c = 0;
              pSVar35 = *(Shape **)(local_9c + 8);
              uVar11 = LottieGenericProperty<unsigned_char>::operator()
                                 ((LottieGenericProperty<unsigned_char> *)(pLVar49 + 0x24),
                                  (float)uVar66);
              tvg::Shape::stroke(pSVar35,(uchar)LVar8,uVar7,uVar10,uVar11);
              if (pLVar49 != (LottieObject *)0x0) goto LAB_005543a4;
              pLVar34 = (LottieStroke *)0x0;
            }
            else {
              iVar21 = *(int *)(pLVar49 + 0x10);
              if ((((iVar21 == 0) || (*(char *)(iVar21 + 0x15) == '\0')) ||
                  (cVar4 = *(char *)(iVar21 + 0x20), cVar4 == '\0')) ||
                 (fVar61 = (float)uVar66, *(float *)(iVar21 + 0x1c) <= fVar61)) {
LAB_00554308:
                local_5c = 0;
                LottieGenericProperty<RGB24>::operator()(local_110,(float)pLVar54);
                pSVar35 = *(Shape **)(local_9c + 8);
              }
              else {
                iVar22 = **(int **)(pLVar49 + 0x14);
                fVar65 = *(float *)(iVar22 + 0xc);
                if (fVar61 < fVar65) goto LAB_00554308;
                iVar31 = (*(int **)(pLVar49 + 0x14))[1];
                fVar62 = *(float *)(iVar31 * 0x18 + iVar22 + -0xc);
                if (fVar61 < fVar62) goto LAB_00554308;
                if (cVar4 == '\x01') {
                  local_5c = 0;
                  in_f12 = fVar61 - fVar65;
                  fmodf(in_f12,fVar62 - fVar65);
                  goto LAB_00554308;
                }
                if (cVar4 == '\x05') {
                  local_5c = 0;
                  in_f12 = fVar61 - fVar65;
                  fmodf(in_f12,*(float *)(((iVar31 + -1) - *(int *)(iVar21 + 0x18)) * 0x18 + iVar22
                                         + 0xc) - fVar65);
                  goto LAB_00554308;
                }
                local_5c = 0;
                LottieGenericProperty<RGB24>::operator()(local_110,(float)pLVar54);
                pSVar35 = *(Shape **)(local_9c + 8);
              }
              uVar10 = local_108;
              uVar7 = local_10c;
              LVar8 = local_110[0];
              pLVar41 = *(LottieExpression **)(pLVar49 + 0x28);
              fVar61 = (float)uVar66;
              if (((pLVar41 != (LottieExpression *)0x0) && (pLVar41[0x15] != (LottieExpression)0x0))
                 && (pLVar41[0x20] != (LottieExpression)0x0)) {
                local_5c = 0;
                fVar61 = _loop<tvg::Array<LottieScalarFrame<unsigned_char>>>
                                   (*(Array **)(pLVar49 + 0x2c),fVar61,pLVar41);
              }
              local_5c = 0;
              uVar11 = LottieGenericProperty<unsigned_char>::operator()
                                 ((LottieGenericProperty<unsigned_char> *)(pLVar49 + 0x24),fVar61);
              tvg::Shape::stroke(pSVar35,(uchar)LVar8,uVar7,uVar10,uVar11);
LAB_005543a4:
              pLVar34 = (LottieStroke *)(pLVar49 + 0x34);
            }
            local_5c = 0;
            pLVar43 = (LottieTrimpath *)param_4;
            _updateStroke(pLVar34,(float)uVar66,local_9c + 8,param_4);
          }
          break;
        case (LottieTrimpath)0x6:
          iVar21 = _fragmented(ppLVar55,param_3,local_9c);
          if (iVar21 == 0) {
            local_5c = 0;
            pLVar50 = (LottieGradient *)*ppLVar55;
            pSVar35 = *(Shape **)(local_9c + 8);
            *(undefined4 *)(local_9c + 0xc) = 0;
            local_158 = (LottieTrimpath *)LottieGradient::fill(pLVar50,(float)uVar66,param_4);
            tvg::Shape::fill(pSVar35,&local_158);
            if (local_158 != (LottieTrimpath *)0x0) {
              (**(code **)(*(int *)local_158 + 4))();
            }
            pRVar9 = local_9c;
            tvg::Shape::fill(*(Shape **)(local_9c + 8),*(undefined4 *)(pLVar50 + 0x80));
            local_5c = 0;
            pPVar48 = *(Paint **)(pRVar9 + 8);
            iVar21 = LottieGenericProperty<unsigned_char>::operator()
                               ((LottieGenericProperty<unsigned_char> *)(pLVar50 + 0x54),
                                (float)uVar66);
            tvg::Paint::opacity(pPVar48,(uchar)((uint)*(byte *)(*(int *)(*(int *)(pRVar9 + 8) + 4) +
                                                               0x14) * iVar21 + 0xff >> 8));
            local_5c = 0;
            fVar61 = (float)tvg::Shape::strokeWidth(*(Shape **)(pRVar9 + 8));
            local_5c = 0;
            if (fVar61 <= 0.0) goto switchD_00553514_caseD_0;
            tvg::Shape::order(*(Shape **)(pRVar9 + 8),true);
          }
          break;
        case (LottieTrimpath)0x7:
          iVar21 = _fragmented(ppLVar55,param_3,local_9c);
          if (iVar21 == 0) {
            local_5c = 0;
            pLVar50 = (LottieGradient *)*ppLVar55;
            pSVar35 = *(Shape **)(local_9c + 8);
            *(undefined4 *)(local_9c + 0xc) = 0;
            local_158 = (LottieTrimpath *)LottieGradient::fill(pLVar50,(float)uVar66,param_4);
            tvg::Shape::stroke(pSVar35,&local_158);
            if (local_158 != (LottieTrimpath *)0x0) {
              (**(code **)(*(int *)local_158 + 4))();
            }
            local_5c = 0;
            pLVar34 = (LottieStroke *)(pLVar50 + 0x80);
            if (pLVar50 == (LottieGradient *)0x0) {
              pLVar34 = (LottieStroke *)0x0;
            }
            pLVar43 = (LottieTrimpath *)param_4;
            _updateStroke(pLVar34,(float)uVar66,local_9c + 8,param_4);
          }
          break;
        case (LottieTrimpath)0x8:
          pAVar30 = *(Array **)(pLVar14 + 0x14);
          if ((param_4 == (LottieExpressions *)0x0) ||
             (pLVar41 = *(LottieExpression **)(pLVar14 + 0x10), pLVar41 == (LottieExpression *)0x0))
          {
            if (pAVar30 != (Array *)0x0) goto LAB_005544c4;
LAB_005555e4:
            fVar61 = *(float *)(local_a0 + 0x18);
            fVar65 = *(float *)(local_a0 + 0x1c);
          }
          else {
            if ((pLVar41[0x15] != (LottieExpression)0x0) && (pLVar41[0x20] != (LottieExpression)0x0)
               ) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieVectorFrame<tvg::Point>>>(pAVar30,fVar61,pLVar41);
              pAVar30 = *(Array **)(local_a0 + 0x14);
            }
            if (pAVar30 == (Array *)0x0) goto LAB_005555e4;
LAB_005544c4:
            iVar21 = *(int *)(pAVar30 + 4);
            pfVar36 = *(float **)pAVar30;
            if ((iVar21 == 1) || (fVar61 <= pfVar36[2])) {
              fVar61 = *pfVar36;
              fVar65 = pfVar36[1];
            }
            else if (fVar61 < pfVar36[iVar21 * 10 + -8]) {
              iVar21 = iVar21 + -1;
              iVar22 = 0;
              if (-1 < iVar21) {
                do {
                  while( true ) {
                    iVar31 = (iVar21 - iVar22) / 2 + iVar22;
                    pLVar43 = (LottieTrimpath *)(pfVar36 + iVar31 * 10);
                    if (*(float *)(pLVar43 + 8) <= fVar61) break;
                    iVar21 = iVar31 + -1;
                    if (iVar21 < iVar22) goto LAB_00554594;
                  }
                  iVar22 = iVar31 + 1;
                } while (iVar22 <= iVar21);
              }
LAB_00554594:
              if (iVar21 < 0) {
                iVar21 = 0;
              }
              pfVar36 = pfVar36 + iVar21 * 10;
              fVar65 = pfVar36[2];
              if (ABS(fVar65 - fVar61) <= (float)local_74[-0x856]) {
LAB_005545d8:
                fVar61 = *pfVar36;
                fVar65 = pfVar36[1];
              }
              else {
                fVar65 = (fVar61 - fVar65) / (pfVar36[0xc] - fVar65);
                if ((LottieInterpolator *)pfVar36[3] != (LottieInterpolator *)0x0) {
                  local_5c = 0;
                  fVar65 = (float)LottieInterpolator::progress
                                            ((LottieInterpolator *)pfVar36[3],fVar65);
                }
                if (*(char *)((int)pfVar36 + 0x25) == '\0') {
                  if (*(char *)(pfVar36 + 9) == '\0') {
                    fVar61 = (pfVar36[10] - *pfVar36) * fVar65 + *pfVar36;
                    fVar65 = (pfVar36[0xb] - pfVar36[1]) * fVar65 + pfVar36[1];
                  }
                  else {
                    local_5c = 0;
                    local_158 = (LottieTrimpath *)*pfVar36;
                    local_154 = (LottieTrimpath *)pfVar36[1];
                    local_150 = (LottieTrimpath *)(*pfVar36 + pfVar36[4]);
                    local_140 = pfVar36[10];
                    local_14c[0] = (LottieTrimpath *)(pfVar36[1] + pfVar36[5]);
                    local_13c = pfVar36[0xb];
                    local_14c[1] = (LottieTrimpath *)(pfVar36[6] + pfVar36[10]);
                    local_144 = pfVar36[7] + pfVar36[0xb];
                    fVar61 = (float)tvg::bezAtApprox((tvg *)&local_158,
                                                     (Bezier *)(fVar65 * pfVar36[8]),pfVar36[8],
                                                     (float)pLVar43);
                    local_5c = 0;
                    tvg::bezPointAt((tvg *)&local_dc,(Bezier *)&local_158,fVar61);
                    fVar61 = local_dc;
                    fVar65 = local_d8;
                  }
                }
                else {
                  if (fVar65 < *(float *)(local_7c + 0x6c20)) goto LAB_005545d8;
                  fVar61 = pfVar36[10];
                  fVar65 = pfVar36[0xb];
                }
              }
            }
            else {
              fVar61 = pfVar36[iVar21 * 10 + -10];
              fVar65 = pfVar36[iVar21 * 10 + -9];
            }
          }
          pLVar14 = local_a0;
          local_5c = 0;
          LottieGenericProperty<tvg::Point>::operator()
                    (in_f12,(LottieExpressions *)(local_a0 + 0x20));
          local_5c = 0;
          fVar62 = local_e0;
          pLVar43 = local_e4;
          pMVar28 = (Matrix *)
                    LottieGenericProperty<float>::operator()
                              ((LottieGenericProperty<float> *)(pLVar14 + 0x34),(float)uVar66,
                               param_4);
          pRVar9 = local_9c;
          in_stack_fffffe94 = *(Matrix **)(local_9c + 0x1c);
          if ((float)*(Matrix **)(local_9c + 0x1c) <= (float)pMVar28) {
            in_stack_fffffe94 = pMVar28;
          }
          if (*(float *)(local_7c + 0x6c20) < (float)in_stack_fffffe94) {
            pMVar28 = (Matrix *)((float)pLVar43 * DAT_00585fd4);
            if ((float)in_stack_fffffe94 <= (float)pLVar43 * DAT_00585fd4) {
              pMVar28 = in_stack_fffffe94;
            }
            in_stack_fffffe94 = (Matrix *)(fVar62 * DAT_00585fd4);
            if ((float)pMVar28 <= fVar62 * DAT_00585fd4) {
              in_stack_fffffe94 = pMVar28;
            }
          }
          local_5c = 0;
          if (*(int *)(local_9c + 0x14) != 0) {
            tvg::Shape::gen((Shape *)&local_134);
            local_5c = 0;
            in_stack_fffffe98 = *(Matrix **)(pRVar9 + 0x18);
            _appendRect((Shape *)local_134,fVar61 - (float)pLVar43 * DAT_00585fd4,
                        fVar65 - fVar62 * DAT_00585fd4,(float)pLVar43,fVar62,
                        (float)in_stack_fffffe94,in_stack_fffffe98);
            local_158 = local_134;
            local_134 = (LottieTrimpath *)0x0;
                    /* try { // try from 00555744 to 0055574b has its CatchHandler @ 00557450 */
            _repeat(param_1 + 0xc,&local_158,pRVar9);
LAB_005550f4:
            if (local_158 != (LottieTrimpath *)0x0) {
              tvg::Shape::~Shape((Shape *)local_158);
            }
            pLVar14 = local_134;
            if (local_134 != (LottieTrimpath *)0x0) goto LAB_00555110;
            goto switchD_00553514_caseD_0;
          }
          pSVar35 = *(Shape **)(local_9c + 0xc);
          if (pSVar35 == (Shape *)0x0) {
            pSVar35 = (Shape *)_draw(param_1 + 0xc,*(RenderContext **)(local_9c + 8));
          }
          local_5c = 0;
          in_stack_fffffe98 = *(Matrix **)(local_9c + 0x18);
          _appendRect(pSVar35,fVar61 - (float)pLVar43 * DAT_00585fd4,fVar65 - fVar62 * DAT_00585fd4,
                      (float)pLVar43,fVar62,(float)in_stack_fffffe94,in_stack_fffffe98);
          break;
        case (LottieTrimpath)0x9:
          pAVar30 = *(Array **)(pLVar14 + 0x14);
          if ((param_4 == (LottieExpressions *)0x0) ||
             (pLVar41 = *(LottieExpression **)(pLVar14 + 0x10), pLVar41 == (LottieExpression *)0x0))
          {
            if (pAVar30 != (Array *)0x0) goto LAB_005547fc;
LAB_005555ac:
            fVar61 = *(float *)(local_a0 + 0x18);
            fVar65 = *(float *)(local_a0 + 0x1c);
          }
          else {
            if ((pLVar41[0x15] != (LottieExpression)0x0) && (pLVar41[0x20] != (LottieExpression)0x0)
               ) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieVectorFrame<tvg::Point>>>(pAVar30,fVar61,pLVar41);
              pAVar30 = *(Array **)(local_a0 + 0x14);
            }
            if (pAVar30 == (Array *)0x0) goto LAB_005555ac;
LAB_005547fc:
            iVar21 = *(int *)(pAVar30 + 4);
            pfVar36 = *(float **)pAVar30;
            if ((iVar21 == 1) || (fVar61 <= pfVar36[2])) {
              fVar61 = *pfVar36;
              fVar65 = pfVar36[1];
            }
            else if (fVar61 < pfVar36[iVar21 * 10 + -8]) {
              iVar21 = iVar21 + -1;
              iVar22 = 0;
              if (-1 < iVar21) {
                do {
                  while( true ) {
                    iVar31 = (iVar21 - iVar22) / 2 + iVar22;
                    pLVar43 = (LottieTrimpath *)(pfVar36 + iVar31 * 10);
                    if (*(float *)(pLVar43 + 8) <= fVar61) break;
                    iVar21 = iVar31 + -1;
                    if (iVar21 < iVar22) goto LAB_005548cc;
                  }
                  iVar22 = iVar31 + 1;
                } while (iVar22 <= iVar21);
              }
LAB_005548cc:
              if (iVar21 < 0) {
                iVar21 = 0;
              }
              pfVar36 = pfVar36 + iVar21 * 10;
              fVar65 = pfVar36[2];
              if (ABS(fVar65 - fVar61) <= (float)local_74[-0x856]) {
LAB_00554910:
                fVar61 = *pfVar36;
                fVar65 = pfVar36[1];
              }
              else {
                fVar65 = (fVar61 - fVar65) / (pfVar36[0xc] - fVar65);
                if ((LottieInterpolator *)pfVar36[3] != (LottieInterpolator *)0x0) {
                  local_5c = 0;
                  fVar65 = (float)LottieInterpolator::progress
                                            ((LottieInterpolator *)pfVar36[3],fVar65);
                }
                if (*(char *)((int)pfVar36 + 0x25) == '\0') {
                  if (*(char *)(pfVar36 + 9) == '\0') {
                    fVar61 = (pfVar36[10] - *pfVar36) * fVar65 + *pfVar36;
                    fVar65 = (pfVar36[0xb] - pfVar36[1]) * fVar65 + pfVar36[1];
                  }
                  else {
                    local_5c = 0;
                    local_158 = (LottieTrimpath *)*pfVar36;
                    local_154 = (LottieTrimpath *)pfVar36[1];
                    local_150 = (LottieTrimpath *)(*pfVar36 + pfVar36[4]);
                    local_140 = pfVar36[10];
                    local_14c[0] = (LottieTrimpath *)(pfVar36[1] + pfVar36[5]);
                    local_13c = pfVar36[0xb];
                    local_14c[1] = (LottieTrimpath *)(pfVar36[6] + pfVar36[10]);
                    local_144 = pfVar36[7] + pfVar36[0xb];
                    fVar61 = (float)tvg::bezAtApprox((tvg *)&local_158,
                                                     (Bezier *)(fVar65 * pfVar36[8]),pfVar36[8],
                                                     (float)pLVar43);
                    local_5c = 0;
                    tvg::bezPointAt((tvg *)&local_ec,(Bezier *)&local_158,fVar61);
                    fVar61 = local_ec;
                    fVar65 = local_e8;
                  }
                }
                else {
                  if (fVar65 < *(float *)(local_7c + 0x6c20)) goto LAB_00554910;
                  fVar61 = pfVar36[10];
                  fVar65 = pfVar36[0xb];
                }
              }
            }
            else {
              fVar61 = pfVar36[iVar21 * 10 + -10];
              fVar65 = pfVar36[iVar21 * 10 + -9];
            }
          }
          local_5c = 0;
          LottieGenericProperty<tvg::Point>::operator()
                    (in_f12,(LottieExpressions *)(local_a0 + 0x20));
          pRVar9 = local_9c;
          local_5c = 0;
          if (*(int *)(local_9c + 0x14) != 0) {
            fVar62 = local_f0;
            fVar70 = local_f4;
            tvg::Shape::gen((Shape *)&local_134);
            local_5c = 0;
            in_stack_fffffe94 = *(Matrix **)(pRVar9 + 0x18);
            pLVar43 = (LottieTrimpath *)(fVar70 * DAT_00585fd4);
            _appendCircle((Shape *)local_134,fVar61,fVar65,(float)pLVar43,fVar62 * DAT_00585fd4,
                          in_stack_fffffe94);
            local_158 = local_134;
            local_134 = (LottieTrimpath *)0x0;
                    /* try { // try from 005550e8 to 005550ef has its CatchHandler @ 005573a0 */
            _repeat(param_1 + 0xc,&local_158,pRVar9);
            goto LAB_005550f4;
          }
          pSVar35 = *(Shape **)(local_9c + 0xc);
          fVar62 = local_f0;
          fVar70 = local_f4;
          if (pSVar35 == (Shape *)0x0) {
            pSVar35 = (Shape *)_draw(param_1 + 0xc,*(RenderContext **)(local_9c + 8));
          }
          local_5c = 0;
          pLVar43 = (LottieTrimpath *)(fVar70 * DAT_00585fd4);
          in_stack_fffffe94 = *(Matrix **)(local_9c + 0x18);
          _appendCircle(pSVar35,fVar61,fVar65,(float)pLVar43,fVar62 * DAT_00585fd4,in_stack_fffffe94
                       );
          break;
        case (LottieTrimpath)0xa:
          if (*(int *)(local_9c + 0x14) != 0) {
            tvg::Shape::gen((Shape *)&local_134);
            pLVar14 = *(LottieTrimpath **)(pRVar9 + 0x18);
            uVar68 = (ulonglong)*(uint *)(pRVar9 + 0x1c);
            pAVar30 = *(Array **)(local_134 + 8);
            local_98 = (LottieTrimpath *)(pAVar30 + 0xc);
            fVar61 = (float)uVar66;
            if (param_4 == (LottieExpressions *)0x0) {
              pAVar33 = *(Array **)(local_a0 + 0x14);
            }
            else {
              pLVar41 = *(LottieExpression **)(local_a0 + 0x10);
              pAVar33 = *(Array **)(local_a0 + 0x14);
              if (((pLVar41 != (LottieExpression *)0x0) && (pLVar41[0x15] != (LottieExpression)0x0))
                 && (pLVar41[0x20] != (LottieExpression)0x0)) {
                local_5c = 0;
                fVar61 = _loop<tvg::Array<LottieScalarFrame<PathSet>>>(pAVar33,fVar61,pLVar41);
                pAVar33 = *(Array **)(local_a0 + 0x14);
              }
            }
            fVar65 = (float)uVar68;
            if (pAVar33 == (Array *)0x0) {
              pEVar26 = (EVP_PKEY_CTX *)(local_a0 + 0x18);
LAB_00554214:
              local_5c = 0;
              pPVar53 = *(PathCommand **)(pEVar26 + 4);
              pLVar43 = (LottieTrimpath *)(uint)*(ushort *)(pEVar26 + 10);
              if (*(float *)(local_7c + 0x6c20) < fVar65) {
                local_5c = 0;
                in_stack_fffffe94 = (Matrix *)local_98;
                _modifier(*(Point **)pEVar26,(uint)*(ushort *)(pEVar26 + 8),pPVar53,(uint)pLVar43,
                          pAVar30,(Array *)local_98,(Matrix *)pLVar14,fVar65);
                in_stack_fffffe98 = (Matrix *)pLVar14;
              }
              else {
                if (pLVar43 != (LottieTrimpath *)0x0) {
                  iVar21 = *(int *)(pAVar30 + 4);
                  pLVar37 = pLVar43 + iVar21;
                  pvVar57 = *(void **)pAVar30;
                  if (*(LottieTrimpath **)(pAVar30 + 8) < pLVar37) {
                    *(LottieTrimpath **)(pAVar30 + 8) = pLVar37;
                    pvVar57 = realloc(pvVar57,(int)pLVar37 * 4);
                    iVar21 = *(int *)(pAVar30 + 4);
                    *(void **)pAVar30 = pvVar57;
                  }
                  memcpy((void *)((int)pvVar57 + iVar21 * 4),pPVar53,(int)pLVar43 << 2);
                  *(LottieTrimpath **)(pAVar30 + 4) = pLVar43 + *(int *)(pAVar30 + 4);
                }
                _copy(pEVar26,pEVar26 + 8);
                pLVar43 = pLVar14;
              }
            }
            else {
              iVar21 = *(int *)(pAVar33 + 4);
              pEVar52 = *(EVP_PKEY_CTX **)pAVar33;
              pEVar26 = pEVar52;
              if (((iVar21 == 1) || (fVar61 <= *(float *)(pEVar52 + 0xc))) ||
                 (pEVar26 = pEVar52 + iVar21 * 0x18 + -0x18,
                 *(float *)(pEVar52 + iVar21 * 0x18 + -0xc) <= fVar61)) goto LAB_00554214;
              iVar21 = iVar21 + -1;
              if (-1 < iVar21) {
                iVar22 = 0;
                do {
                  while( true ) {
                    iVar31 = (iVar21 - iVar22) / 2 + iVar22;
                    pLVar43 = (LottieTrimpath *)(pEVar52 + iVar31 * 0x18);
                    if (*(float *)(pLVar43 + 0xc) <= fVar61) break;
                    iVar21 = iVar31 + -1;
                    if (iVar21 < iVar22) goto LAB_00555c18;
                  }
                  iVar22 = iVar31 + 1;
                } while (iVar22 <= iVar21);
              }
LAB_00555c18:
              if (iVar21 < 0) {
                iVar21 = 0;
              }
              pEVar26 = pEVar52 + iVar21 * 0x18;
              fVar62 = *(float *)(pEVar26 + 0xc);
              if (ABS(fVar62 - fVar61) <= (float)local_74[-0x856]) goto LAB_00554214;
              fVar61 = (fVar61 - fVar62) / (*(float *)(pEVar26 + 0x24) - fVar62);
              if (*(LottieInterpolator **)(pEVar26 + 0x10) != (LottieInterpolator *)0x0) {
                local_5c = 0;
                    /* try { // try from 00555c94 to 00555e43 has its CatchHandler @ 00557448 */
                fVar61 = (float)LottieInterpolator::progress
                                          (*(LottieInterpolator **)(pEVar26 + 0x10),fVar61);
              }
              uVar69 = (ulonglong)(uint)fVar61;
              fVar65 = (float)uVar68;
              if (pEVar26[0x14] != (EVP_PKEY_CTX)0x0) {
                iVar21 = 0x18;
                if (fVar61 < *(float *)(local_7c + 0x6c20)) {
                  iVar21 = 0;
                }
                pEVar26 = pEVar26 + iVar21;
                goto LAB_00554214;
              }
              local_5c = 0;
              pfVar36 = *(float **)pEVar26;
              pfVar59 = *(float **)(pEVar26 + 0x18);
              uVar56 = (uint)*(ushort *)(pEVar26 + 8);
              if (fVar65 <= *(float *)(local_7c + 0x6c20)) {
                if (uVar56 != 0) {
                  iVar21 = 0;
                  do {
                    local_5c = 0;
                    local_154 = (LottieTrimpath *)
                                ((pfVar59[1] - pfVar36[1]) * (float)uVar69 + pfVar36[1]);
                    local_158 = (LottieTrimpath *)((*pfVar59 - *pfVar36) * (float)uVar69 + *pfVar36)
                    ;
                    if (pLVar14 != (LottieTrimpath *)0x0) {
                    /* try { // try from 00556940 to 00556a9b has its CatchHandler @ 00557448 */
                      mathMultiply((Point *)&local_158,(Matrix *)pLVar14);
                    }
                    local_5c = 0;
                    iVar22 = *(int *)(pAVar30 + 0x10);
                    uVar56 = iVar22 + 1;
                    pvVar57 = *(void **)(pAVar30 + 0xc);
                    pLVar37 = local_158;
                    pLVar20 = local_154;
                    if (*(uint *)(pAVar30 + 0x14) < uVar56) {
                      iVar22 = (iVar22 + 2U >> 1) + iVar22;
                      *(int *)(pAVar30 + 0x14) = iVar22;
                      pvVar57 = realloc(pvVar57,iVar22 * 8);
                      iVar22 = *(int *)(pAVar30 + 0x10);
                      *(void **)(pAVar30 + 0xc) = pvVar57;
                      uVar56 = iVar22 + 1;
                    }
                    uVar5 = *(ushort *)(pEVar26 + 8);
                    iVar21 = iVar21 + 1;
                    puVar18 = (undefined4 *)((int)pvVar57 + iVar22 * 8);
                    *(uint *)(pAVar30 + 0x10) = uVar56;
                    pfVar36 = pfVar36 + 2;
                    *puVar18 = pLVar37;
                    puVar18[1] = pLVar20;
                    pfVar59 = pfVar59 + 2;
                  } while (iVar21 < (int)(uint)uVar5);
                }
                local_5c = 0;
                uVar56 = (uint)*(ushort *)(pEVar26 + 10);
                pvVar57 = *(void **)(pEVar26 + 4);
                if (uVar56 != 0) {
                  iVar21 = *(int *)(pAVar30 + 4);
                  uVar38 = uVar56 + iVar21;
                  pvVar32 = *(void **)pAVar30;
                  if (*(uint *)(pAVar30 + 8) < uVar38) {
                    *(uint *)(pAVar30 + 8) = uVar38;
                    pvVar32 = realloc(pvVar32,uVar38 * 4);
                    iVar21 = *(int *)(pAVar30 + 4);
                    *(void **)pAVar30 = pvVar32;
                  }
                  memcpy((void *)((int)pvVar32 + iVar21 * 4),pvVar57,uVar56 << 2);
                  *(uint *)(pAVar30 + 4) = *(int *)(pAVar30 + 4) + uVar56;
                }
              }
              else {
                pPVar25 = malloc(uVar56 << 3);
                fVar61 = (float)uVar68;
                local_a0 = (LottieTrimpath *)pPVar25;
                if (uVar56 == 0) {
                  uVar56 = 0;
                }
                else {
                  iVar21 = 0;
                  do {
                    local_5c = 0;
                    fVar65 = *pfVar36;
                    fVar61 = *pfVar59;
                    *(float *)(pPVar25 + 4) = (pfVar59[1] - pfVar36[1]) * (float)uVar69 + pfVar36[1]
                    ;
                    *(float *)pPVar25 = (fVar61 - fVar65) * (float)uVar69 + fVar65;
                    if (pLVar14 != (LottieTrimpath *)0x0) {
                      mathMultiply(pPVar25,(Matrix *)pLVar14);
                    }
                    fVar61 = (float)uVar68;
                    uVar56 = (uint)*(ushort *)(pEVar26 + 8);
                    iVar21 = iVar21 + 1;
                    pfVar36 = pfVar36 + 2;
                    pfVar59 = pfVar59 + 2;
                    pPVar25 = pPVar25 + 8;
                  } while (iVar21 < (int)uVar56);
                }
                pLVar14 = local_a0;
                local_5c = 0;
                pLVar43 = (LottieTrimpath *)(uint)*(ushort *)(pEVar26 + 10);
                in_stack_fffffe98 = (Matrix *)0x0;
                in_stack_fffffe94 = (Matrix *)local_98;
                _modifier((Point *)local_a0,uVar56,*(PathCommand **)(pEVar26 + 4),(uint)pLVar43,
                          pAVar30,(Array *)local_98,(Matrix *)0x0,fVar61);
                free(pLVar14);
              }
            }
            local_158 = local_134;
            local_134 = (LottieTrimpath *)0x0;
                    /* try { // try from 00554290 to 00554297 has its CatchHandler @ 00557440 */
            _repeat(param_1 + 0xc,&local_158,local_9c);
            goto LAB_005550f4;
          }
          pLVar14 = *(LottieTrimpath **)(local_9c + 0xc);
          pMVar28 = in_stack_fffffe94;
          pMVar17 = in_stack_fffffe98;
          if (pLVar14 == (LottieTrimpath *)0x0) {
            pLVar14 = (LottieTrimpath *)_draw(param_1 + 0xc,*(RenderContext **)(local_9c + 8));
            pMVar28 = in_stack_fffffe94;
            pMVar17 = in_stack_fffffe98;
          }
          pAVar33 = *(Array **)(pLVar14 + 8);
          in_stack_fffffe98 = *(Matrix **)(local_9c + 0x18);
          fVar65 = *(float *)(local_9c + 0x1c);
          uVar68 = (ulonglong)(uint)fVar65;
          in_stack_fffffe94 = (Matrix *)(pAVar33 + 0xc);
          pAVar30 = *(Array **)(local_a0 + 0x14);
          fVar61 = (float)uVar66;
          if ((param_4 == (LottieExpressions *)0x0) ||
             (pLVar41 = *(LottieExpression **)(local_a0 + 0x10), pLVar41 == (LottieExpression *)0x0)
             ) {
            if (pAVar30 != (Array *)0x0) goto LAB_005553d4;
LAB_00555e94:
            pLVar20 = local_a0 + 0x18;
            pPVar53 = *(PathCommand **)(local_a0 + 0x1c);
            pLVar43 = (LottieTrimpath *)(uint)*(ushort *)(local_a0 + 0x22);
            if (*(float *)(local_7c + 0x6c20) < fVar65) {
LAB_00555510:
              local_5c = 0;
              iVar21 = _modifier(*(Point **)pLVar20,(uint)*(ushort *)(pLVar20 + 8),pPVar53,
                                 (uint)pLVar43,pAVar33,(Array *)in_stack_fffffe94,in_stack_fffffe98,
                                 fVar65);
              if (iVar21 == 0) break;
              iVar21 = *(int *)(pLVar14 + 8);
            }
            else {
LAB_00555ec4:
              in_stack_fffffe94 = pMVar28;
              local_5c = 0;
              if (pLVar43 != (LottieTrimpath *)0x0) {
                iVar21 = *(int *)(pAVar33 + 4);
                pLVar37 = pLVar43 + iVar21;
                pvVar57 = *(void **)pAVar33;
                if (*(LottieTrimpath **)(pAVar33 + 8) < pLVar37) {
                  *(LottieTrimpath **)(pAVar33 + 8) = pLVar37;
                  pvVar57 = realloc(pvVar57,(int)pLVar37 * 4);
                  iVar21 = *(int *)(pAVar33 + 4);
                  *(void **)pAVar33 = pvVar57;
                }
                memcpy((void *)((int)pvVar57 + iVar21 * 4),pPVar53,(int)pLVar43 << 2);
                *(LottieTrimpath **)(pAVar33 + 4) = pLVar43 + *(int *)(pAVar33 + 4);
              }
              _copy((EVP_PKEY_CTX *)pLVar20,(EVP_PKEY_CTX *)(pLVar20 + 8));
              iVar21 = *(int *)(pLVar14 + 8);
              pLVar43 = (LottieTrimpath *)in_stack_fffffe98;
              in_stack_fffffe98 = pMVar17;
            }
          }
          else {
            if ((pLVar41[0x15] != (LottieExpression)0x0) && (pLVar41[0x20] != (LottieExpression)0x0)
               ) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieScalarFrame<PathSet>>>(pAVar30,fVar61,pLVar41);
              pAVar30 = *(Array **)(local_a0 + 0x14);
            }
            fVar65 = (float)uVar68;
            if (pAVar30 == (Array *)0x0) goto LAB_00555e94;
LAB_005553d4:
            fVar65 = (float)uVar68;
            iVar21 = *(int *)(pAVar30 + 4);
            pLVar43 = *(LottieTrimpath **)pAVar30;
            pLVar20 = pLVar43;
            if (((iVar21 == 1) || (fVar61 <= *(float *)(pLVar43 + 0xc))) ||
               (pLVar20 = pLVar43 + iVar21 * 0x18 + -0x18,
               *(float *)(pLVar43 + iVar21 * 0x18 + -0xc) <= fVar61)) {
LAB_005554e8:
              pPVar53 = *(PathCommand **)(pLVar20 + 4);
              pLVar43 = (LottieTrimpath *)(uint)*(ushort *)(pLVar20 + 10);
              if (*(float *)(local_7c + 0x6c20) < fVar65) goto LAB_00555510;
              goto LAB_00555ec4;
            }
            iVar21 = iVar21 + -1;
            if (-1 < iVar21) {
              iVar22 = 0;
              do {
                while (iVar31 = (iVar21 - iVar22) / 2 + iVar22,
                      fVar61 < *(float *)(pLVar43 + iVar31 * 0x18 + 0xc)) {
                  iVar21 = iVar31 + -1;
                  if (iVar21 < iVar22) goto LAB_005554a4;
                }
                iVar22 = iVar31 + 1;
              } while (iVar22 <= iVar21);
            }
LAB_005554a4:
            if (iVar21 < 0) {
              iVar21 = 0;
            }
            pLVar37 = (LottieTrimpath *)0x18;
            pLVar20 = pLVar43 + iVar21 * 0x18;
            fVar62 = *(float *)(pLVar20 + 0xc);
            if (ABS(fVar62 - fVar61) <= (float)local_74[-0x856]) goto LAB_005554e8;
            pLVar43 = (LottieTrimpath *)((fVar61 - fVar62) / (*(float *)(pLVar20 + 0x24) - fVar62));
            if (*(LottieInterpolator **)(pLVar20 + 0x10) != (LottieInterpolator *)0x0) {
              local_5c = 0;
              pLVar43 = (LottieTrimpath *)
                        LottieInterpolator::progress
                                  (*(LottieInterpolator **)(pLVar20 + 0x10),(float)pLVar43);
            }
            fVar65 = (float)uVar68;
            if (pLVar20[0x14] != (LottieTrimpath)0x0) {
              iVar21 = 0x18;
              if ((float)pLVar43 < *(float *)(local_7c + 0x6c20)) {
                iVar21 = 0;
              }
              pLVar20 = pLVar20 + iVar21;
              goto LAB_005554e8;
            }
            pfVar36 = *(float **)pLVar20;
            pfVar59 = *(float **)(pLVar20 + 0x18);
            pLVar40 = (LottieTrimpath *)(uint)*(ushort *)(pLVar20 + 8);
            if (*(float *)(local_7c + 0x6c20) < fVar65) {
              local_5c = 0;
              local_a0 = pLVar40;
              local_98 = pLVar43;
              pPVar25 = malloc((int)pLVar40 << 3);
              fVar61 = (float)uVar68;
              local_90 = pPVar25;
              if (local_a0 == (LottieTrimpath *)0x0) {
                uVar56 = 0;
              }
              else {
                pSVar42 = (Scene *)0x0;
                pLVar43 = local_98;
                do {
                  fVar65 = *pfVar36;
                  fVar61 = *pfVar59;
                  *(float *)(pPVar25 + 4) = (pfVar59[1] - pfVar36[1]) * (float)pLVar43 + pfVar36[1];
                  *(float *)pPVar25 = (fVar61 - fVar65) * (float)pLVar43 + fVar65;
                  if (in_stack_fffffe98 != (Matrix *)0x0) {
                    local_5c = 0;
                    local_a0 = (LottieTrimpath *)pPVar25;
                    local_98 = pLVar43;
                    local_94 = pSVar42;
                    mathMultiply(pPVar25,in_stack_fffffe98);
                    pPVar25 = (Point *)local_a0;
                    pSVar42 = local_94;
                    pLVar43 = local_98;
                  }
                  fVar61 = (float)uVar68;
                  uVar56 = (uint)*(ushort *)(pLVar20 + 8);
                  pSVar42 = pSVar42 + 1;
                  pfVar36 = pfVar36 + 2;
                  pfVar59 = pfVar59 + 2;
                  pPVar25 = pPVar25 + 8;
                } while ((int)pSVar42 < (int)uVar56);
              }
              pPVar25 = local_90;
              local_5c = 0;
              pLVar43 = (LottieTrimpath *)(uint)*(ushort *)(pLVar20 + 10);
              in_stack_fffffe98 = (Matrix *)0x0;
              _modifier(local_90,uVar56,*(PathCommand **)(pLVar20 + 4),(uint)pLVar43,pAVar33,
                        (Array *)in_stack_fffffe94,(Matrix *)0x0,fVar61);
              free(pPVar25);
              iVar21 = *(int *)(pLVar14 + 8);
              goto LAB_00555348;
            }
            if (pLVar40 != (LottieTrimpath *)0x0) {
              iVar21 = 0;
              do {
                local_154 = (LottieTrimpath *)
                            ((pfVar59[1] - pfVar36[1]) * (float)pLVar43 + pfVar36[1]);
                local_158 = (LottieTrimpath *)((*pfVar59 - *pfVar36) * (float)pLVar43 + *pfVar36);
                if (in_stack_fffffe98 != (Matrix *)0x0) {
                  local_5c = 0;
                  local_a0 = pLVar43;
                  mathMultiply((Point *)&local_158,in_stack_fffffe98);
                  pLVar43 = local_a0;
                }
                iVar22 = *(int *)(pAVar33 + 0x10);
                uVar56 = iVar22 + 1;
                pvVar57 = *(void **)(pAVar33 + 0xc);
                pLVar40 = local_158;
                pLVar67 = local_154;
                if (*(uint *)(pAVar33 + 0x14) < uVar56) {
                  local_5c = 0;
                  iVar22 = (iVar22 + 2U >> 1) + iVar22;
                  *(int *)(pAVar33 + 0x14) = iVar22;
                  local_a0 = pLVar43;
                  pvVar57 = realloc(pvVar57,iVar22 * 8);
                  iVar22 = *(int *)(pAVar33 + 0x10);
                  *(void **)(pAVar33 + 0xc) = pvVar57;
                  uVar56 = iVar22 + 1;
                  pLVar43 = local_a0;
                }
                uVar5 = *(ushort *)(pLVar20 + 8);
                iVar21 = iVar21 + 1;
                puVar18 = (undefined4 *)((int)pvVar57 + iVar22 * 8);
                *(uint *)(pAVar33 + 0x10) = uVar56;
                pfVar36 = pfVar36 + 2;
                *puVar18 = pLVar40;
                puVar18[1] = pLVar67;
                pfVar59 = pfVar59 + 2;
              } while (iVar21 < (int)(uint)uVar5);
            }
            local_5c = 0;
            uVar56 = (uint)*(ushort *)(pLVar20 + 10);
            pvVar57 = *(void **)(pLVar20 + 4);
            if (uVar56 != 0) {
              iVar21 = *(int *)(pAVar33 + 4);
              uVar38 = uVar56 + iVar21;
              pvVar32 = *(void **)pAVar33;
              if (*(uint *)(pAVar33 + 8) < uVar38) {
                *(uint *)(pAVar33 + 8) = uVar38;
                pvVar32 = realloc(pvVar32,uVar38 * 4);
                iVar21 = *(int *)(pAVar33 + 4);
                *(void **)pAVar33 = pvVar32;
              }
              memcpy((void *)((int)pvVar32 + iVar21 * 4),pvVar57,uVar56 << 2);
              *(uint *)(pAVar33 + 4) = *(int *)(pAVar33 + 4) + uVar56;
            }
LAB_00555344:
            iVar21 = *(int *)(pLVar14 + 8);
            pLVar43 = pLVar37;
            in_stack_fffffe94 = pMVar28;
            in_stack_fffffe98 = pMVar17;
          }
LAB_00555348:
          *(byte *)(iVar21 + 0x30) = *(byte *)(iVar21 + 0x30) | 1;
          goto switchD_00553514_caseD_0;
        case (LottieTrimpath)0xb:
          local_154 = (LottieTrimpath *)0x0;
          local_158 = *(LottieTrimpath **)(local_7c + 0x6c20);
          local_150 = (LottieTrimpath *)0x0;
          local_14c[0] = (LottieTrimpath *)0x0;
          local_144 = 0.0;
          local_140 = 0.0;
          local_13c = 0.0;
          pAVar30 = *(Array **)(pLVar14 + 0x14);
          local_14c[1] = local_158;
          local_138 = local_158;
          if ((param_4 == (LottieExpressions *)0x0) ||
             (pLVar41 = *(LottieExpression **)(pLVar14 + 0x10), pLVar41 == (LottieExpression *)0x0))
          {
            if (pAVar30 != (Array *)0x0) goto LAB_005549b4;
LAB_00555574:
            fVar65 = *(float *)(local_a0 + 0x18);
            fVar61 = *(float *)(local_a0 + 0x1c);
          }
          else {
            if ((pLVar41[0x15] != (LottieExpression)0x0) && (pLVar41[0x20] != (LottieExpression)0x0)
               ) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieVectorFrame<tvg::Point>>>(pAVar30,fVar61,pLVar41);
              pAVar30 = *(Array **)(local_a0 + 0x14);
            }
            if (pAVar30 == (Array *)0x0) goto LAB_00555574;
LAB_005549b4:
            iVar21 = *(int *)(pAVar30 + 4);
            pfVar36 = *(float **)pAVar30;
            if ((iVar21 == 1) || (fVar61 <= pfVar36[2])) {
              fVar61 = pfVar36[1];
              fVar65 = *pfVar36;
            }
            else if (fVar61 < pfVar36[iVar21 * 10 + -8]) {
              iVar21 = iVar21 + -1;
              if (-1 < iVar21) {
                iVar22 = 0;
                do {
                  while( true ) {
                    iVar31 = (iVar21 - iVar22) / 2 + iVar22;
                    pLVar43 = (LottieTrimpath *)(pfVar36 + iVar31 * 10);
                    if (*(float *)(pLVar43 + 8) <= fVar61) break;
                    iVar21 = iVar31 + -1;
                    if (iVar21 < iVar22) goto LAB_00554a88;
                  }
                  iVar22 = iVar31 + 1;
                } while (iVar22 <= iVar21);
              }
LAB_00554a88:
              if (iVar21 < 0) {
                iVar21 = 0;
              }
              pfVar36 = pfVar36 + iVar21 * 10;
              fVar65 = pfVar36[2];
              if (ABS(fVar65 - fVar61) <= (float)local_74[-0x856]) {
LAB_00554acc:
                fVar61 = pfVar36[1];
                fVar65 = *pfVar36;
              }
              else {
                fVar65 = (fVar61 - fVar65) / (pfVar36[0xc] - fVar65);
                if ((LottieInterpolator *)pfVar36[3] != (LottieInterpolator *)0x0) {
                  local_5c = 0;
                  fVar65 = (float)LottieInterpolator::progress
                                            ((LottieInterpolator *)pfVar36[3],fVar65);
                }
                if (*(char *)((int)pfVar36 + 0x25) == '\0') {
                  if (*(char *)(pfVar36 + 9) == '\0') {
                    fVar61 = (pfVar36[0xb] - pfVar36[1]) * fVar65 + pfVar36[1];
                    fVar65 = (pfVar36[10] - *pfVar36) * fVar65 + *pfVar36;
                  }
                  else {
                    local_5c = 0;
                    local_134 = (LottieTrimpath *)*pfVar36;
                    local_130 = pfVar36[1];
                    local_12c = *pfVar36 + pfVar36[4];
                    local_11c = pfVar36[10];
                    local_128 = pfVar36[1] + pfVar36[5];
                    local_118 = pfVar36[0xb];
                    local_124 = pfVar36[6] + pfVar36[10];
                    local_120 = pfVar36[7] + pfVar36[0xb];
                    fVar61 = (float)tvg::bezAtApprox((tvg *)&local_134,
                                                     (Bezier *)(fVar65 * pfVar36[8]),pfVar36[8],
                                                     (float)pLVar43);
                    local_5c = 0;
                    tvg::bezPointAt((tvg *)&local_fc,(Bezier *)&local_134,fVar61);
                    fVar61 = local_f8;
                    fVar65 = local_fc;
                  }
                }
                else {
                  if (fVar65 < *(float *)(local_7c + 0x6c20)) goto LAB_00554acc;
                  fVar61 = pfVar36[0xb];
                  fVar65 = pfVar36[10];
                }
              }
            }
            else {
              fVar61 = pfVar36[iVar21 * 10 + -9];
              fVar65 = pfVar36[iVar21 * 10 + -10];
            }
          }
          local_5c = 0;
          local_150 = (LottieTrimpath *)((float)local_150 + fVar65);
          local_144 = local_144 + fVar61;
          fVar61 = (float)LottieGenericProperty<float>::operator()
                                    ((LottieGenericProperty<float> *)(local_a0 + 0x60),(float)uVar66
                                     ,param_4);
          local_5c = 0;
          pLVar39 = (LottiePolyStar *)&local_158;
          mathRotate((Matrix *)pLVar39,fVar61);
          if (*(Matrix **)(local_9c + 0x18) != (Matrix *)0x0) {
            mathMultiply(local_d0,*(Matrix **)(local_9c + 0x18));
            pMVar17 = local_d0;
            pMVar28 = (Matrix *)pLVar39;
            do {
              uVar45 = *(undefined4 *)pMVar17;
              uVar44 = *(undefined4 *)(pMVar17 + 4);
              uVar64 = *(undefined4 *)(pMVar17 + 8);
              uVar63 = *(undefined4 *)(pMVar17 + 0xc);
              pMVar17 = pMVar17 + 0x10;
              *(undefined4 *)pMVar28 = uVar45;
              *(undefined4 *)(pMVar28 + 4) = uVar44;
              *(undefined4 *)(pMVar28 + 8) = uVar64;
              *(undefined4 *)(pMVar28 + 0xc) = uVar63;
              pMVar28 = pMVar28 + 0x10;
            } while (pMVar17 != aMStack_b0);
            *(undefined4 *)pMVar28 = *(undefined4 *)pMVar17;
          }
          iVar21 = mathIdentity((Matrix *)pLVar39);
          if (*(int *)(local_9c + 0x14) == 0) {
            pLVar14 = *(LottieTrimpath **)(local_9c + 0xc);
            pMVar28 = in_stack_fffffe94;
            pMVar17 = in_stack_fffffe98;
            if (pLVar14 == (LottieTrimpath *)0x0) {
              pLVar14 = (LottieTrimpath *)_draw(param_1 + 0xc,*(RenderContext **)(local_9c + 8));
              pMVar28 = in_stack_fffffe94;
              pMVar17 = in_stack_fffffe98;
            }
            pLVar43 = (LottieTrimpath *)uVar66;
            if (*(LottieGroup *)(local_a0 + 0x80) != (LottieGroup)0x1) {
              local_5c = 0;
              if (iVar21 != 0) {
                pLVar39 = (LottiePolyStar *)0x0;
              }
              pLVar37 = pLVar14;
              _updatePolygon((LottieGroup *)local_a0,pLVar39,(Matrix *)pLVar43,(float)pLVar14,
                             (Shape *)param_4,(LottieExpressions *)pMVar28);
              goto LAB_00555344;
            }
            local_5c = 0;
            if (iVar21 != 0) {
              pLVar39 = (LottiePolyStar *)0x0;
            }
            in_stack_fffffe94 = (Matrix *)param_4;
            _updateStar((LottieGroup *)local_a0,pLVar39,*(Matrix **)(local_9c + 0x1c),(float)pLVar43
                        ,(float)pLVar14,(Shape *)param_4,(LottieExpressions *)pMVar17);
            iVar21 = *(int *)(pLVar14 + 8);
            in_stack_fffffe98 = pMVar17;
            goto LAB_00555348;
          }
          tvg::Shape::gen((Shape *)&local_d4);
          pLVar43 = (LottieTrimpath *)uVar66;
          if (*(LottieGroup *)(local_a0 + 0x80) == (LottieGroup)0x1) {
            local_5c = 0;
            local_98 = *(LottieTrimpath **)(local_9c + 0x1c);
            if (iVar21 != 0) {
              pLVar39 = (LottiePolyStar *)0x0;
            }
            in_stack_fffffe94 = (Matrix *)param_4;
                    /* try { // try from 00556178 to 0055617f has its CatchHandler @ 00557458 */
            _updateStar((LottieGroup *)local_a0,pLVar39,(Matrix *)local_98,(float)pLVar43,
                        (float)local_d4,(Shape *)param_4,(LottieExpressions *)in_stack_fffffe98);
          }
          else {
            local_5c = 0;
                    /* try { // try from 005552a0 to 005552a7 has its CatchHandler @ 00557458 */
            if (iVar21 != 0) {
              pLVar39 = (LottiePolyStar *)0x0;
            }
            pSVar42 = local_d4;
            _updatePolygon((LottieGroup *)local_a0,pLVar39,(Matrix *)pLVar43,(float)local_d4,
                           (Shape *)param_4,(LottieExpressions *)in_stack_fffffe94);
            pLVar43 = (LottieTrimpath *)pSVar42;
          }
          local_134 = (LottieTrimpath *)local_d4;
          local_d4 = (Scene *)0x0;
                    /* try { // try from 005552c0 to 005552c7 has its CatchHandler @ 00557400 */
          _repeat(param_1 + 0xc,&local_134,local_9c);
          if (local_134 != (LottieTrimpath *)0x0) {
            tvg::Shape::~Shape((Shape *)local_134);
          }
          pLVar14 = (LottieTrimpath *)local_d4;
          if (local_d4 == (Scene *)0x0) break;
LAB_00555110:
          tvg::Shape::~Shape((Shape *)pLVar14);
          break;
        case (LottieTrimpath)0xc:
          pLVar14 = *(LottieTrimpath **)(pLVar14 + 0x18);
          if (pLVar14 == (LottieTrimpath *)0x0) {
            tvg::Picture::gen((Picture *)&local_158);
            pLVar14 = local_158;
            tvg::TaskScheduler::async(false);
            uVar56 = *(uint *)(local_a0 + 0x14);
            if (uVar56 == 0) {
              pcVar58 = *(char **)(local_a0 + 0xc);
              local_158 = (LottieTrimpath *)&local_150;
              if (pcVar58 == (char *)0x0) goto LAB_005572e4;
              pLVar37 = (LottieTrimpath *)strlen(pcVar58);
              if (pLVar37 < (LottieTrimpath *)0x10) {
                pLVar20 = (LottieTrimpath *)&local_150;
                if (pLVar37 == (LottieTrimpath *)0x1) {
                  local_150 = (LottieTrimpath *)CONCAT31(local_150._1_3_,*pcVar58);
                }
                else if (pLVar37 != (LottieTrimpath *)0x0) goto LAB_00556858;
              }
              else {
                pLVar20 = operator_new((uint)(pLVar37 + 1));
                local_158 = pLVar20;
                local_150 = pLVar37;
LAB_00556858:
                memcpy(pLVar20,pcVar58,(size_t)pLVar37);
                pLVar20 = local_158;
              }
              pLVar20[(int)pLVar37] = (LottieTrimpath)0x0;
              local_154 = pLVar37;
              iVar21 = tvg::Picture::load((Picture *)pLVar14,(string *)&local_158);
              pLVar37 = local_158;
              if (local_158 != (LottieTrimpath *)&local_150) goto LAB_0055634c;
            }
            else {
              __s = *(char **)(local_a0 + 0x10);
              pcVar58 = *(char **)(local_a0 + 0xc);
              local_134 = (LottieTrimpath *)&local_12c;
              if (__s == (char *)0x0) {
LAB_005572e4:
                std::__throw_logic_error("basic_string::_M_construct null not valid");
                return;
              }
              fVar61 = (float)strlen(__s);
              if ((uint)fVar61 < 0x10) {
                pLVar43 = (LottieTrimpath *)&local_12c;
                if (fVar61 == 1.4013e-45) {
                  local_12c = (float)CONCAT31(local_12c._1_3_,*__s);
                }
                else if (fVar61 != 0.0) goto LAB_00556880;
              }
              else {
                pLVar43 = operator_new((int)fVar61 + 1);
                local_134 = pLVar43;
                local_12c = fVar61;
LAB_00556880:
                memcpy(pLVar43,__s,(size_t)fVar61);
                pLVar43 = local_134;
              }
              pLVar43[(int)fVar61] = (LottieTrimpath)0x0;
              pLVar43 = (LottieTrimpath *)&local_134;
              local_130 = fVar61;
              iVar21 = tvg::Picture::load((Picture *)pLVar14,pcVar58,uVar56,(string *)pLVar43,false)
              ;
              pLVar37 = local_134;
              if (local_134 != (LottieTrimpath *)&local_12c) {
LAB_0055634c:
                operator_delete(pLVar37);
              }
            }
            if (iVar21 != 0) {
              if (pLVar14 == (LottieTrimpath *)0x0) goto switchD_00553514_caseD_0;
              tvg::Picture::~Picture((Picture *)pLVar14);
              break;
            }
            tvg::TaskScheduler::async(true);
            iVar21 = *(int *)(pLVar14 + 4);
            *(LottieTrimpath **)(local_a0 + 0x18) = pLVar14;
            *(char *)(iVar21 + 0x15) = *(char *)(iVar21 + 0x15) + '\x01';
          }
          pRVar9 = local_9c;
          if (*(int *)(local_9c + 8) != 0) {
            iVar21 = *(int *)(*(int *)(local_9c + 8) + 4);
            if (*(RenderTransform **)(iVar21 + 4) != (RenderTransform *)0x0) {
              tvg::RenderTransform::update(*(RenderTransform **)(iVar21 + 4));
              if (*(Matrix **)(iVar21 + 4) == (Matrix *)0x0) {
                tvg::Paint::opacity((Paint *)pLVar14,
                                    *(uchar *)(*(int *)(*(int *)(pRVar9 + 8) + 4) + 0x14));
                goto LAB_0055443c;
              }
              tvg::Paint::transform((Paint *)pLVar14,*(Matrix **)(iVar21 + 4));
              iVar21 = *(int *)(*(int *)(local_9c + 8) + 4);
            }
            tvg::Paint::opacity((Paint *)pLVar14,*(uchar *)(iVar21 + 0x14));
          }
LAB_0055443c:
          local_a0 = *(LottieTrimpath **)(param_1 + 0xc);
          local_158 = pLVar14;
          tvg::Scene::push((Scene *)local_a0,(Picture *)&local_158);
          if (local_158 == (LottieTrimpath *)0x0) goto switchD_00553514_caseD_0;
          (**(code **)(*(int *)local_158 + 4))();
          break;
        case (LottieTrimpath)0xd:
          local_5c = 0;
          pLVar43 = (LottieTrimpath *)&local_158;
          LottieTrimpath::segment(pLVar14,fVar61,(float *)&local_134,(float *)pLVar43,param_4);
          iVar21 = *(int *)(*(int *)(local_9c + 8) + 8);
          puVar18 = *(undefined4 **)(iVar21 + 0x1c);
          if (puVar18 == (undefined4 *)0x0) {
            if (((float)local_134 == 0.0) &&
               (local_5c = 0, (float)local_158 == *(float *)(local_7c + 0x6c20)))
            goto switchD_00553514_caseD_0;
            local_5c = 0;
            LVar3 = local_a0[0x3c];
            pLVar14 = local_134;
            pLVar37 = local_158;
            puVar18 = operator_new(0x34);
            uVar63 = DAT_00585ff8;
            uVar64 = *(undefined4 *)(local_7c + 0x6c20);
            puVar18[10] = 0;
            puVar18[0xb] = uVar64;
            *puVar18 = 0;
            puVar18[1] = 0;
            puVar18[2] = 0;
            puVar18[3] = 0;
            puVar18[4] = 0;
            puVar18[5] = 0;
            puVar18[6] = 0;
            puVar18[7] = 0;
            puVar18[9] = 0;
            puVar18[0xc] = 0;
            puVar18[8] = uVar63;
            *(undefined4 **)(iVar21 + 0x1c) = puVar18;
            fVar61 = (float)puVar18[10];
          }
          else {
            fVar61 = (float)puVar18[10];
            LVar3 = pLVar14[0x3c];
            pLVar14 = (LottieTrimpath *)
                      (ABS((float)puVar18[0xb] - fVar61) * (float)local_134 + fVar61);
            pLVar37 = (LottieTrimpath *)
                      (ABS((float)puVar18[0xb] - fVar61) * (float)local_158 + fVar61);
            local_158 = pLVar37;
            local_134 = pLVar14;
          }
          if (((float)local_74[-0x856] < ABS(fVar61 - (float)pLVar14)) ||
             (local_5c = 0, (float)local_74[-0x856] < ABS((float)puVar18[0xb] - (float)pLVar37))) {
            local_5c = 0;
            puVar18[10] = pLVar14;
            *(LottieTrimpath **)(*(int *)(iVar21 + 0x1c) + 0x2c) = pLVar37;
            *(bool *)(*(int *)(iVar21 + 0x1c) + 0x30) = LVar3 == (LottieTrimpath)0x2;
            *(byte *)(iVar21 + 0x30) = *(byte *)(iVar21 + 0x30) | 8;
          }
          goto switchD_00553514_caseD_0;
        case (LottieTrimpath)0xe:
          puVar18 = *(undefined4 **)(pLVar14 + 0x14);
          if (puVar18 == (undefined4 *)0x0) {
            local_88 = pLVar14 + 0x18;
          }
          else {
            iVar21 = puVar18[1];
            pLVar37 = (LottieTrimpath *)*puVar18;
            local_88 = pLVar37;
            if ((iVar21 != 1) && (local_5c = 0, *(float *)(pLVar37 + 0x4c) < fVar61)) {
              local_5c = 0;
              local_88 = pLVar37 + iVar21 * 0x58 + -0x58;
              if (fVar61 < *(float *)(pLVar37 + iVar21 * 0x58 + -0xc)) {
                iVar21 = iVar21 + -1;
                iVar22 = 0;
                if (-1 < iVar21) {
                  do {
                    while( true ) {
                      iVar31 = (iVar21 - iVar22) / 2 + iVar22;
                      pLVar43 = pLVar37 + iVar31 * 0x58;
                      if (*(float *)(pLVar43 + 0x4c) <= fVar61) break;
                      iVar21 = iVar31 + -1;
                      if (iVar21 < iVar22) goto LAB_00553af4;
                    }
                    iVar22 = iVar31 + 1;
                  } while (iVar22 <= iVar21);
                }
LAB_00553af4:
                local_5c = 0;
                if (iVar21 < 0) {
                  iVar21 = 0;
                }
                local_88 = pLVar37 + iVar21 * 0x58;
              }
            }
          }
          local_98 = *(LottieTrimpath **)local_88;
          if (local_98 == (LottieTrimpath *)0x0) goto switchD_00553514_caseD_0;
          if (*(int *)(pLVar14 + 100) != 0) {
            local_5c = 0;
            uVar68 = 0;
            uVar69 = (ulonglong)(uint)(*(float *)(local_88 + 0x40) * DAT_0069e1c0);
            local_78 = 0.0;
            local_70 = (float)LottieGenericProperty<float>::operator()
                                        ((LottieGenericProperty<float> *)(pLVar14 + 0x68),fVar61);
            local_5c = 0;
            local_70 = local_70 / (float)uVar69;
            tvg::Scene::gen((Scene *)&local_d4);
            puVar18 = *(undefined4 **)(pLVar14 + 100);
            local_80 = 0;
            local_68 = 0x580000;
LAB_00553b90:
            LVar3 = *local_98;
            do {
              if (((byte)LVar3 < 0xe) && ((int)((0x2009U >> ((byte)LVar3 & 0x1f)) << 0x1f) < 0)) {
                fVar62 = (float)uVar69;
                fVar65 = *(float *)(local_88 + 0x18);
                fVar61 = *(float *)(local_88 + 0x24);
                if (fVar62 * (float)puVar18[6] <= *(float *)(local_88 + 0x24)) {
                  fVar61 = fVar62 * (float)puVar18[6];
                }
                if (local_88[0x48] == (LottieTrimpath)0x1) {
                  fVar62 = *(float *)(local_88 + 0x20) - fVar62 * (float)uVar68;
LAB_00553c40:
                  fVar65 = fVar65 + fVar62;
                }
                else if (local_88[0x48] == (LottieTrimpath)0x2) {
                  fVar62 = *(float *)(local_88 + 0x20) * *(float *)(local_68 + 0x5fd4) -
                           (float)uVar68 * *(float *)(local_68 + 0x5fd4) * fVar62;
                  goto LAB_00553c40;
                }
                local_5c = 0;
                tvg::Paint::translate
                          ((Paint *)local_d4,fVar65,
                           (fVar61 + *(float *)(local_88 + 0x1c)) - *(float *)(local_88 + 8));
                local_5c = 0;
                tvg::Paint::scale((Paint *)local_d4,(float)uVar69);
                local_158 = (LottieTrimpath *)local_d4;
                local_94 = *(Scene **)(param_1 + 0xc);
                local_d4 = (Scene *)0x0;
                tvg::Scene::push(local_94,(Scene *)&local_158);
                if (local_158 != (LottieTrimpath *)0x0) {
                  (**(code **)(*(int *)local_158 + 4))();
                }
                pLVar14 = local_98;
                if (*local_98 == (LottieTrimpath)0x0) {
                  if (local_d4 == (Scene *)0x0) goto switchD_00553514_caseD_0;
                  tvg::Scene::~Scene(local_d4);
                  break;
                }
                tvg::Scene::gen((Scene *)&local_158);
                pSVar42 = local_d4;
                pLVar37 = local_158;
                local_98 = pLVar14 + 1;
                local_158 = (LottieTrimpath *)0x0;
                bVar1 = local_d4 != (Scene *)0x0;
                local_d4 = (Scene *)pLVar37;
                if ((bVar1) && (tvg::Scene::~Scene(pSVar42), local_158 != (LottieTrimpath *)0x0)) {
                  tvg::Scene::~Scene((Scene *)local_158);
                }
                local_5c = 0;
                uVar68 = 0;
                local_80 = local_80 + 1;
                puVar18 = *(undefined4 **)(local_a0 + 100);
                local_78 = (*(float *)(local_88 + 4) / (float)uVar69) * (float)local_80;
              }
              puVar51 = (undefined4 *)*puVar18;
              puVar24 = puVar51 + puVar18[1];
              if (puVar51 < puVar24) goto LAB_00553d6c;
              LVar3 = *local_98;
            } while( true );
          }
          break;
        case (LottieTrimpath)0xf:
          if (*(int *)(local_9c + 0x14) == 0) {
            puVar18 = operator_new(0x28);
            *puVar18 = 0;
            puVar18[1] = 0;
            puVar18[2] = 0;
            puVar18[3] = 0;
            puVar18[4] = 0;
            puVar18[5] = 0;
            puVar18[6] = 0;
            puVar18[7] = 0;
            puVar18[8] = 0;
            *(undefined2 *)(puVar18 + 9) = 0;
            *(undefined1 *)((int)puVar18 + 0x26) = 0;
            *(undefined1 *)((int)puVar18 + 0x27) = 0;
            *(undefined4 **)(local_9c + 0x14) = puVar18;
          }
          pLVar14 = local_a0;
          local_5c = 0;
          fVar61 = (float)LottieGenericProperty<float>::operator()
                                    ((LottieGenericProperty<float> *)(local_a0 + 0xc),(float)uVar66,
                                     param_4);
          pRVar9 = local_9c;
          local_5c = 0;
          piVar47 = *(int **)(local_9c + 0x14);
          *piVar47 = (int)fVar61;
          iVar21 = LottieGenericProperty<float>::operator()
                             ((LottieGenericProperty<float> *)(pLVar14 + 0x1c),(float)uVar66,param_4
                             );
          piVar47[1] = iVar21;
          iVar21 = *(int *)(pRVar9 + 0x14);
          fVar61 = (float)uVar66;
          if (param_4 == (LottieExpressions *)0x0) {
            pAVar30 = *(Array **)(local_a0 + 0x34);
          }
          else {
            pLVar41 = *(LottieExpression **)(local_a0 + 0x30);
            pAVar30 = *(Array **)(local_a0 + 0x34);
            if (((pLVar41 != (LottieExpression *)0x0) && (pLVar41[0x15] != (LottieExpression)0x0))
               && (pLVar41[0x20] != (LottieExpression)0x0)) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieVectorFrame<tvg::Point>>>(pAVar30,fVar61,pLVar41);
              pAVar30 = *(Array **)(local_a0 + 0x34);
            }
          }
          if (pAVar30 == (Array *)0x0) {
            fVar65 = *(float *)(local_a0 + 0x38);
            fVar61 = *(float *)(local_a0 + 0x3c);
          }
          else {
            iVar22 = *(int *)(pAVar30 + 4);
            pfVar36 = *(float **)pAVar30;
            if ((iVar22 == 1) || (fVar61 <= pfVar36[2])) {
              fVar61 = pfVar36[1];
              fVar65 = *pfVar36;
            }
            else if (fVar61 < pfVar36[iVar22 * 10 + -8]) {
              iVar22 = iVar22 + -1;
              iVar31 = 0;
              if (-1 < iVar22) {
                do {
                  while( true ) {
                    iVar15 = (iVar22 - iVar31) / 2 + iVar31;
                    pLVar43 = (LottieTrimpath *)(pfVar36 + iVar15 * 10);
                    if (*(float *)(pLVar43 + 8) <= fVar61) break;
                    iVar22 = iVar15 + -1;
                    if (iVar22 < iVar31) goto LAB_005537a0;
                  }
                  iVar31 = iVar15 + 1;
                } while (iVar31 <= iVar22);
              }
LAB_005537a0:
              if (iVar22 < 0) {
                iVar22 = 0;
              }
              pfVar36 = pfVar36 + iVar22 * 10;
              fVar65 = pfVar36[2];
              if (ABS(fVar65 - fVar61) <= (float)local_74[-0x856]) {
LAB_005537e4:
                fVar61 = pfVar36[1];
                fVar65 = *pfVar36;
              }
              else {
                fVar65 = (fVar61 - fVar65) / (pfVar36[0xc] - fVar65);
                if ((LottieInterpolator *)pfVar36[3] != (LottieInterpolator *)0x0) {
                  local_5c = 0;
                  fVar65 = (float)LottieInterpolator::progress
                                            ((LottieInterpolator *)pfVar36[3],fVar65);
                }
                if (*(char *)((int)pfVar36 + 0x25) == '\0') {
                  if (*(char *)(pfVar36 + 9) == '\0') {
                    fVar61 = (pfVar36[0xb] - pfVar36[1]) * fVar65 + pfVar36[1];
                    fVar65 = (pfVar36[10] - *pfVar36) * fVar65 + *pfVar36;
                  }
                  else {
                    local_5c = 0;
                    local_158 = (LottieTrimpath *)*pfVar36;
                    local_154 = (LottieTrimpath *)pfVar36[1];
                    local_150 = (LottieTrimpath *)(*pfVar36 + pfVar36[4]);
                    local_140 = pfVar36[10];
                    local_14c[0] = (LottieTrimpath *)(pfVar36[1] + pfVar36[5]);
                    local_13c = pfVar36[0xb];
                    local_14c[1] = (LottieTrimpath *)(pfVar36[6] + pfVar36[10]);
                    local_144 = pfVar36[7] + pfVar36[0xb];
                    fVar61 = (float)tvg::bezAtApprox((tvg *)&local_158,
                                                     (Bezier *)(fVar65 * pfVar36[8]),pfVar36[8],
                                                     (float)pLVar43);
                    local_5c = 0;
                    tvg::bezPointAt((tvg *)&local_104,(Bezier *)&local_158,fVar61);
                    fVar61 = local_100;
                    fVar65 = local_104;
                  }
                }
                else {
                  if (fVar65 < *(float *)(local_7c + 0x6c20)) goto LAB_005537e4;
                  fVar61 = pfVar36[0xb];
                  fVar65 = pfVar36[10];
                }
              }
            }
            else {
              fVar61 = pfVar36[iVar22 * 10 + -9];
              fVar65 = pfVar36[iVar22 * 10 + -10];
            }
          }
          pRVar9 = local_9c;
          pLVar14 = local_a0;
          local_5c = 0;
          *(float *)(iVar21 + 8) = fVar65;
          *(float *)(iVar21 + 0xc) = fVar61;
          iVar21 = *(int *)(local_9c + 0x14);
          LottieGenericProperty<tvg::Point>::operator()
                    (in_f12,(LottieExpressions *)(local_a0 + 100));
          local_5c = 0;
          *(undefined4 *)(iVar21 + 0x10) = local_a8;
          *(undefined4 *)(iVar21 + 0x14) = local_a4;
          iVar21 = *(int *)(pRVar9 + 0x14);
          pLVar43 = (LottieTrimpath *)param_4;
          LottieGenericProperty<tvg::Point>::operator()
                    (in_f12,(LottieExpressions *)(pLVar14 + 0x50));
          local_5c = 0;
          iVar22 = *(int *)(pRVar9 + 0x14);
          *(undefined4 *)(iVar21 + 0x18) = local_a8;
          *(undefined4 *)(iVar21 + 0x1c) = local_a4;
          uVar63 = LottieGenericProperty<float>::operator()
                             ((LottieGenericProperty<float> *)(pLVar14 + 0x40),(float)uVar66,param_4
                             );
          *(undefined4 *)(iVar22 + 0x20) = uVar63;
          iVar21 = *(int *)(pRVar9 + 0x14);
          fVar61 = (float)uVar66;
          if (param_4 == (LottieExpressions *)0x0) {
            local_5c = 0;
            uVar12 = LottieGenericProperty<unsigned_char>::operator()
                               ((LottieGenericProperty<unsigned_char> *)(pLVar14 + 0x78),fVar61);
            *(undefined1 *)(iVar21 + 0x24) = uVar12;
            iVar21 = *(int *)(local_9c + 0x14);
LAB_0055591c:
            fVar61 = (float)uVar66;
          }
          else {
            pLVar41 = *(LottieExpression **)(pLVar14 + 0x7c);
            if (((pLVar41 != (LottieExpression *)0x0) && (pLVar41[0x15] != (LottieExpression)0x0))
               && (pLVar41[0x20] != (LottieExpression)0x0)) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieScalarFrame<unsigned_char>>>
                                 (*(Array **)(local_a0 + 0x80),fVar61,pLVar41);
            }
            local_5c = 0;
            uVar12 = LottieGenericProperty<unsigned_char>::operator()
                               ((LottieGenericProperty<unsigned_char> *)(pLVar14 + 0x78),fVar61);
            *(undefined1 *)(iVar21 + 0x24) = uVar12;
            pLVar41 = *(LottieExpression **)(local_a0 + 0x8c);
            iVar21 = *(int *)(local_9c + 0x14);
            if (pLVar41 == (LottieExpression *)0x0) goto LAB_0055591c;
            fVar61 = (float)uVar66;
            if ((pLVar41[0x15] != (LottieExpression)0x0) && (pLVar41[0x20] != (LottieExpression)0x0)
               ) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieScalarFrame<unsigned_char>>>
                                 (*(Array **)(local_a0 + 0x90),fVar61,pLVar41);
            }
          }
          local_5c = 0;
          uVar12 = LottieGenericProperty<unsigned_char>::operator()
                             ((LottieGenericProperty<unsigned_char> *)(pLVar14 + 0x88),fVar61);
          *(undefined1 *)(iVar21 + 0x25) = uVar12;
          iVar21 = *(int *)(local_9c + 0x14);
          *(LottieTrimpath *)(iVar21 + 0x27) = local_a0[0x98];
          *(bool *)(iVar21 + 0x26) = *(char *)(iVar21 + 0x24) != *(char *)(iVar21 + 0x25);
          *(undefined4 *)(local_9c + 0xc) = 0;
          goto switchD_00553514_caseD_0;
        case (LottieTrimpath)0x10:
          local_5c = 0;
          fVar61 = (float)LottieGenericProperty<float>::operator()
                                    ((LottieGenericProperty<float> *)(pLVar14 + 0xc),fVar61,param_4)
          ;
          local_5c = 0;
          if (*(float *)(local_9c + 0x1c) < fVar61) {
            local_5c = 0;
            *(float *)(local_9c + 0x1c) = fVar61;
          }
switchD_00553514_caseD_0:
        }
        ppLVar55 = ppLVar55 + -1;
      } while (*(LottieObject ***)(param_1 + 0x10) <= ppLVar55);
    }
    if ((local_9c[0x22] != (RenderContext)0x0) && (*(Shape **)(local_9c + 8) != (Shape *)0x0)) {
      tvg::Shape::~Shape(*(Shape **)(local_9c + 8));
    }
    pRVar9 = local_9c;
    operator_delete(*(void **)(local_9c + 0x14),0x28);
    free(*(void **)(pRVar9 + 0x18));
    operator_delete(pRVar9,0x24);
    local_9c = *(RenderContext **)param_3;
    if (local_9c == (RenderContext *)0x0) {
      return;
    }
    ppLVar55 = *(LottieObject ***)(local_9c + 0x10);
    iVar21 = *(int *)(local_9c + 4);
    ppLVar13 = *(LottieObject ***)(param_1 + 0x10);
    *(int *)param_3 = iVar21;
  } while( true );
LAB_00553d6c:
  local_94 = (Scene *)*puVar51;
  iVar21 = strncmp(*(char **)(local_94 + 0x10),(char *)local_98,(uint)(byte)local_94[0x1e]);
  puVar51 = puVar51 + 1;
  if (iVar21 != 0) {
    if (puVar24 <= puVar51) goto LAB_00553b90;
    goto LAB_00553d6c;
  }
  tvg::Shape::gen((Shape *)&local_134);
  fVar61 = (float)uVar68;
  iVar21 = *(int *)(local_94 + 4);
  pPVar25 = *(Point **)local_94;
  pLVar14 = local_134;
  local_90 = pPVar25;
  if (pPVar25 < pPVar25 + iVar21 * 4) {
    do {
      iVar22 = *(int *)local_90;
      piVar47 = *(int **)(iVar22 + 0x10);
      if (piVar47 < piVar47 + *(int *)(iVar22 + 0x14)) {
        do {
          iVar21 = *piVar47;
          puVar18 = *(undefined4 **)(pLVar14 + 8);
          pAVar30 = *(Array **)(iVar21 + 0x14);
          fVar61 = (float)uVar66;
          if ((param_4 == (LottieExpressions *)0x0) ||
             (pLVar41 = *(LottieExpression **)(iVar21 + 0x10), pLVar41 == (LottieExpression *)0x0))
          {
            local_5c = 0;
          }
          else {
            local_5c = 0;
            if ((pLVar41[0x15] != (LottieExpression)0x0) && (pLVar41[0x20] != (LottieExpression)0x0)
               ) {
              local_5c = 0;
              fVar61 = _loop<tvg::Array<LottieScalarFrame<PathSet>>>(pAVar30,fVar61,pLVar41);
              pAVar30 = *(Array **)(iVar21 + 0x14);
            }
          }
          pEVar26 = (EVP_PKEY_CTX *)(iVar21 + 0x18);
          if (pAVar30 == (Array *)0x0) {
LAB_00553e84:
            uVar56 = (uint)*(ushort *)(pEVar26 + 10);
            pvVar57 = *(void **)(pEVar26 + 4);
            if (uVar56 != 0) {
              iVar21 = puVar18[1];
              uVar38 = uVar56 + iVar21;
              pvVar32 = (void *)*puVar18;
              if ((uint)puVar18[2] < uVar38) {
                puVar18[2] = uVar38;
                pvVar32 = realloc(pvVar32,uVar38 * 4);
                iVar21 = puVar18[1];
                *puVar18 = pvVar32;
              }
              memcpy((void *)((int)pvVar32 + iVar21 * 4),pvVar57,uVar56 << 2);
              puVar18[1] = puVar18[1] + uVar56;
            }
                    /* try { // try from 00553ed4 to 00553edb has its CatchHandler @ 005573d0 */
            _copy(pEVar26,pEVar26 + 8);
          }
          else {
            iVar21 = *(int *)(pAVar30 + 4);
            pEVar52 = *(EVP_PKEY_CTX **)pAVar30;
            pEVar26 = pEVar52;
            if ((iVar21 == 1) || (local_5c = 0, fVar61 <= *(float *)(pEVar52 + 0xc)))
            goto LAB_00553e84;
            local_5c = 0;
            pEVar26 = pEVar52 + iVar21 * 0x18 + -0x18;
            if (*(float *)(pEVar52 + iVar21 * 0x18 + -0xc) <= fVar61) goto LAB_00553e84;
            iVar21 = iVar21 + -1;
            iVar31 = 0;
            if (-1 < iVar21) {
              do {
                while (iVar15 = (iVar21 - iVar31) / 2 + iVar31,
                      *(float *)(pEVar52 + iVar15 * 0x18 + 0xc) <= fVar61) {
                  iVar31 = iVar15 + 1;
                  if (iVar21 < iVar31) goto LAB_00554d04;
                }
                iVar21 = iVar15 + -1;
              } while (iVar31 <= iVar21);
            }
LAB_00554d04:
            local_5c = 0;
            if (iVar21 < 0) {
              iVar21 = 0;
            }
            pEVar26 = pEVar52 + iVar21 * 0x18;
            fVar65 = *(float *)(pEVar26 + 0xc);
            if (ABS(fVar65 - fVar61) <= local_84) goto LAB_00553e84;
            fVar61 = (fVar61 - fVar65) / (*(float *)(pEVar26 + 0x24) - fVar65);
            if (*(LottieInterpolator **)(pEVar26 + 0x10) != (LottieInterpolator *)0x0) {
              local_5c = 0;
                    /* try { // try from 00554d80 to 00554d87 has its CatchHandler @ 005573d0 */
              fVar61 = (float)LottieInterpolator::progress
                                        (*(LottieInterpolator **)(pEVar26 + 0x10),fVar61);
            }
            uVar71 = (ulonglong)(uint)fVar61;
            if (pEVar26[0x14] != (EVP_PKEY_CTX)0x0) {
              local_5c = 0;
              iVar21 = 0x18;
              if (fVar61 < local_6c) {
                iVar21 = 0;
              }
              pEVar26 = pEVar26 + iVar21;
              goto LAB_00553e84;
            }
            uVar56 = (uint)*(ushort *)(pEVar26 + 8);
            pfVar59 = *(float **)pEVar26;
            pfVar36 = *(float **)(pEVar26 + 0x18);
            if (uVar56 != 0) {
              pvVar57 = (void *)puVar18[3];
              iVar21 = 0;
              uVar38 = puVar18[4];
              do {
                while( true ) {
                  local_5c = 0;
                  uVar46 = uVar38 + 1;
                  fVar65 = (*pfVar36 - *pfVar59) * (float)uVar71 + *pfVar59;
                  fVar61 = (pfVar36[1] - pfVar59[1]) * (float)uVar71 + pfVar59[1];
                  if (uVar46 <= (uint)puVar18[5]) break;
                  iVar31 = (uVar38 + 2 >> 1) + uVar38;
                  puVar18[5] = iVar31;
                  pvVar57 = realloc(pvVar57,iVar31 * 8);
                  uVar56 = (uint)*(ushort *)(pEVar26 + 8);
                  iVar21 = iVar21 + 1;
                  uVar38 = puVar18[4] + 1;
                  pfVar27 = (float *)((int)pvVar57 + puVar18[4] * 8);
                  puVar18[3] = pvVar57;
                  puVar18[4] = uVar38;
                  pfVar59 = pfVar59 + 2;
                  *pfVar27 = fVar65;
                  pfVar27[1] = fVar61;
                  pfVar36 = pfVar36 + 2;
                  if ((int)uVar56 <= iVar21) goto LAB_00554ee4;
                }
                iVar21 = iVar21 + 1;
                pfVar27 = (float *)((int)pvVar57 + uVar38 * 8);
                puVar18[4] = uVar46;
                pfVar59 = pfVar59 + 2;
                *pfVar27 = fVar65;
                pfVar27[1] = fVar61;
                pfVar36 = pfVar36 + 2;
                uVar38 = uVar46;
              } while (iVar21 < (int)uVar56);
            }
LAB_00554ee4:
            local_5c = 0;
            uVar56 = (uint)*(ushort *)(pEVar26 + 10);
            pvVar57 = *(void **)(pEVar26 + 4);
            if (uVar56 != 0) {
              iVar21 = puVar18[1];
              uVar38 = uVar56 + iVar21;
              pvVar32 = (void *)*puVar18;
              local_8c = uVar56;
              if ((uint)puVar18[2] < uVar38) {
                puVar18[2] = uVar38;
                pvVar32 = realloc(pvVar32,uVar38 * 4);
                iVar21 = puVar18[1];
                *puVar18 = pvVar32;
              }
              memcpy((void *)((int)pvVar32 + iVar21 * 4),pvVar57,local_8c << 2);
              puVar18[1] = puVar18[1] + local_8c;
            }
          }
          piVar47 = piVar47 + 1;
          *(byte *)(*(int *)(local_134 + 8) + 0x30) = *(byte *)(*(int *)(local_134 + 8) + 0x30) | 1;
          pLVar14 = local_134;
        } while (piVar47 < (int *)(*(int *)(iVar22 + 0x10) + *(int *)(iVar22 + 0x14) * 4));
        pPVar25 = *(Point **)local_94;
        iVar21 = *(int *)(local_94 + 4);
      }
      fVar61 = (float)uVar68;
      local_90 = local_90 + 4;
    } while (local_90 < pPVar25 + iVar21 * 4);
  }
  pLVar37 = local_88;
  pLVar43 = (LottieTrimpath *)(uint)(byte)local_88[0x14];
  tvg::Shape::fill((Shape *)pLVar14,(uchar)local_88[0xc],(uchar)local_88[0x10],(uchar)local_88[0x14]
                   ,0xff);
  local_5c = 0;
  tvg::Paint::translate((Paint *)local_134,fVar61,local_78);
  pLVar14 = local_134;
  if (pLVar37[0x38] != (LottieTrimpath)0x0) {
    tvg::Shape::stroke((Shape *)local_134,1);
    pLVar14 = local_88;
    local_5c = 0;
    tvg::Shape::stroke((Shape *)local_134,*(float *)(local_88 + 0x34) / (float)uVar69);
    pLVar43 = (LottieTrimpath *)(uint)(byte)pLVar14[0x30];
    tvg::Shape::stroke((Shape *)local_134,(uchar)pLVar14[0x28],(uchar)pLVar14[0x2c],
                       (uchar)pLVar14[0x30],0xff);
    pLVar14 = local_134;
  }
  local_134 = (LottieTrimpath *)0x0;
  local_158 = pLVar14;
  tvg::Scene::push(local_d4,&local_158);
  if (local_158 != (LottieTrimpath *)0x0) {
    (**(code **)(*(int *)local_158 + 4))();
  }
  local_5c = 0;
  local_98 = local_98 + (byte)local_94[0x1e];
  uVar68 = (ulonglong)
           (uint)(fVar61 + local_70 + *(float *)(local_94 + 0xc) + *(float *)(local_88 + 0x44));
  if (local_134 != (LottieTrimpath *)0x0) {
    tvg::Shape::~Shape((Shape *)local_134);
  }
  puVar18 = *(undefined4 **)(local_a0 + 100);
  goto LAB_00553b90;
}



// === _updateLayer @ 00557460 ===

/* WARNING: Removing unreachable block (ram,0x0055775c) */
/* WARNING: Removing unreachable block (ram,0x00557bfc) */
/* _updateLayer(LottieLayer*, LottieLayer*, float, LottieExpressions*) */

void _updateLayer(LottieLayer *param_1,LottieLayer *param_2,float param_3,LottieExpressions *param_4
                 )

{
  Paint *this;
  byte bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  uint uVar7;
  Paint *pPVar8;
  Array *pAVar9;
  void *pvVar10;
  int iVar11;
  EVP_PKEY_CTX *pEVar12;
  LottieExpression *pLVar13;
  byte *pbVar14;
  float *pfVar15;
  void *pvVar16;
  EVP_PKEY_CTX *pEVar17;
  uint uVar18;
  LottieLayer *pLVar19;
  int iVar20;
  int *piVar21;
  Matrix *pMVar22;
  EVP_PKEY_CTX *pEVar23;
  ulonglong uVar24;
  ulonglong uVar25;
  ulonglong uVar26;
  float fVar27;
  float fVar28;
  Paint *local_90;
  Paint *local_8c;
  Shape *local_88 [2];
  EVP_PKEY_CTX *local_80;
  EVP_PKEY_CTX *local_7c;
  EVP_PKEY_CTX *local_78;
  float *local_74;
  LottieLayer *local_70;
  int local_6c;
  undefined **local_68;
  int local_64;
  undefined4 local_5c;
  ulonglong uVar29;
  
  *(undefined4 *)(param_2 + 0xc) = 0;
  if (param_3 < *(float *)(param_2 + 0x6c)) {
    return;
  }
  if (*(float *)(param_2 + 0x70) <= param_3) {
    return;
  }
  local_5c = 0;
  uVar24 = (ulonglong)(uint)param_3;
  local_70 = param_1;
  _updateTransform(param_2,param_3,param_4);
  if ((param_2[0xac] != (LottieLayer)0x3) && (param_2[0xa8] == (LottieLayer)0x0)) {
    return;
  }
  tvg::Scene::gen((Scene *)&local_90);
  *(Paint **)(param_2 + 0xc) = local_90;
  pPVar8 = local_90;
  if (param_2[0xac] != (LottieLayer)0x3) {
    tvg::Paint::opacity(local_90,(uchar)param_2[0xa8]);
    pPVar8 = *(Paint **)(param_2 + 0xc);
  }
  pMVar22 = (Matrix *)(param_2 + 0x84);
  tvg::Paint::transform(pPVar8,pMVar22);
  pLVar19 = *(LottieLayer **)(param_2 + 0x24);
  if (pLVar19 != (LottieLayer *)0x0) {
    local_5c = 0;
    _updateLayer(local_70,pLVar19,(float)uVar24,param_4);
    if (*(Paint **)(pLVar19 + 0xc) == (Paint *)0x0) {
      if ((*(int *)(param_2 + 0x20) - 2U & 0xfffffffd) == 0) {
        if (*(Scene **)(param_2 + 0xc) != (Scene *)0x0) {
          tvg::Scene::~Scene(*(Scene **)(param_2 + 0xc));
        }
        *(undefined4 *)(param_2 + 0xc) = 0;
        return;
      }
    }
    else {
      local_90 = *(Paint **)(pLVar19 + 0xc);
      tvg::Paint::composite(*(Paint **)(param_2 + 0xc),&local_90,*(undefined4 *)(param_2 + 0x20));
      if (local_90 != (Paint *)0x0) {
        (**(code **)(*(int *)local_90 + 4))();
      }
    }
  }
  fVar28 = (float)uVar24;
  if ((*(int *)(param_2 + 0x4c) != 0) &&
     (piVar21 = *(int **)(param_2 + 0x48), piVar21 < piVar21 + *(int *)(param_2 + 0x4c))) {
    local_5c = 0;
    local_68 = &PTR__handleLinearX1Attr_006a0000;
    uVar25 = (ulonglong)DAT_0069dea8;
    uVar26 = (ulonglong)DAT_0069e1bc;
    local_6c = 2;
    local_64 = 0x580000;
    pPVar8 = (Paint *)0x0;
    do {
      iVar20 = *piVar21;
      tvg::Shape::gen((Shape *)&local_90);
      this = local_90;
      puVar2 = *(undefined4 **)(iVar20 + 0x20);
      if (puVar2 == (undefined4 *)0x0) {
        bVar1 = *(byte *)(iVar20 + 0x24);
        goto LAB_005577c0;
      }
      iVar4 = puVar2[1];
      pbVar14 = (byte *)*puVar2;
      if (iVar4 == 1) {
LAB_005577bc:
        bVar1 = *pbVar14;
      }
      else {
        local_5c = 0;
        fVar28 = (float)uVar24;
        if (fVar28 <= *(float *)(pbVar14 + 4)) goto LAB_005577bc;
        local_5c = 0;
        iVar11 = iVar4 + -1;
        if (fVar28 < *(float *)(pbVar14 + iVar4 * 0x10 + -0x10 + 4)) {
          iVar4 = 0;
          if (-1 < iVar11) {
            do {
              iVar3 = (iVar11 - iVar4) / 2 + iVar4;
              if (*(float *)(pbVar14 + iVar3 * 0x10 + 4) <= fVar28) {
                iVar4 = iVar3 + 1;
              }
              else {
                iVar11 = iVar3 + -1;
              }
            } while (iVar4 <= iVar11);
          }
          if (iVar11 < 0) {
            iVar11 = 0;
          }
          pbVar14 = pbVar14 + iVar11 * 0x10;
          fVar27 = *(float *)(pbVar14 + 4);
          if (ABS(fVar27 - fVar28) <= (float)uVar25) {
LAB_00557b34:
            local_5c = 0;
            bVar1 = *pbVar14;
          }
          else {
            fVar28 = (fVar28 - fVar27) / (*(float *)(pbVar14 + 0x14) - fVar27);
            if (*(LottieInterpolator **)(pbVar14 + 8) != (LottieInterpolator *)0x0) {
              local_5c = 0;
              fVar28 = (float)LottieInterpolator::progress
                                        (*(LottieInterpolator **)(pbVar14 + 8),fVar28);
            }
            if (pbVar14[0xc] == 0) {
              fVar28 = (float)(int)((uint)pbVar14[0x10] - (uint)*pbVar14) * fVar28 + (float)*pbVar14
              ;
              if (fVar28 < (float)uVar26) {
                local_5c = 0;
                bVar1 = (byte)(int)fVar28;
              }
              else {
                local_5c = 0;
                bVar1 = (byte)(int)(fVar28 - (float)uVar26);
              }
            }
            else {
              local_5c = 0;
              if (fVar28 < *(float *)(local_64 + 0x6c20)) goto LAB_00557b34;
              bVar1 = pbVar14[0x10];
            }
          }
        }
        else {
          bVar1 = pbVar14[iVar4 * 0x10 + -0x10];
        }
      }
LAB_005577c0:
      tvg::Shape::fill((Shape *)this,0xff,0xff,0xff,bVar1);
      tvg::Paint::transform(this,pMVar22);
      puVar2 = *(undefined4 **)(this + 8);
      fVar28 = (float)uVar24;
      if (param_4 == (LottieExpressions *)0x0) {
        local_5c = 0;
        pAVar9 = *(Array **)(iVar20 + 8);
      }
      else {
        pLVar13 = *(LottieExpression **)(iVar20 + 4);
        pAVar9 = *(Array **)(iVar20 + 8);
        if (pLVar13 == (LottieExpression *)0x0) {
          local_5c = 0;
        }
        else {
          local_5c = 0;
          if ((pLVar13[0x15] != (LottieExpression)0x0) && (pLVar13[0x20] != (LottieExpression)0x0))
          {
            local_5c = 0;
            fVar28 = _loop<tvg::Array<LottieScalarFrame<PathSet>>>(pAVar9,fVar28,pLVar13);
            pAVar9 = *(Array **)(iVar20 + 8);
          }
        }
      }
      pEVar23 = (EVP_PKEY_CTX *)(iVar20 + 0xc);
      if (pAVar9 == (Array *)0x0) {
LAB_00557888:
        pEVar17 = (EVP_PKEY_CTX *)(uint)*(ushort *)(pEVar23 + 10);
        pvVar16 = *(void **)(pEVar23 + 4);
        if (pEVar17 != (EVP_PKEY_CTX *)0x0) {
          iVar4 = puVar2[1];
          pEVar12 = pEVar17 + iVar4;
          pvVar10 = (void *)*puVar2;
          local_7c = pvVar16;
          local_80 = pEVar23;
          if ((EVP_PKEY_CTX *)puVar2[2] < pEVar12) {
            puVar2[2] = pEVar12;
            local_78 = pEVar17;
            pvVar10 = realloc(pvVar10,(int)pEVar12 * 4);
            iVar4 = puVar2[1];
            *puVar2 = pvVar10;
            pEVar17 = local_78;
          }
          pEVar23 = local_80;
          local_80 = pEVar17;
          pvVar16 = local_7c;
          local_7c = pEVar23;
          memcpy((void *)((int)pvVar10 + iVar4 * 4),pvVar16,(int)pEVar17 << 2);
          puVar2[1] = local_80 + puVar2[1];
          pEVar23 = local_7c;
        }
        _copy(pEVar23,pEVar23 + 8);
      }
      else {
        uVar5 = *(uint *)(pAVar9 + 4);
        pEVar17 = *(EVP_PKEY_CTX **)pAVar9;
        pEVar23 = pEVar17;
        if ((uVar5 == 1) || (local_5c = 0, fVar28 <= *(float *)(pEVar17 + 0xc))) goto LAB_00557888;
        local_5c = 0;
        pEVar23 = pEVar17 + uVar5 * 0x18 + -0x18;
        if (*(float *)(pEVar17 + uVar5 * 0x18 + -0xc) <= fVar28) goto LAB_00557888;
        iVar4 = uVar5 - 1;
        iVar11 = 0;
        if (-1 < iVar4) {
          do {
            iVar3 = (iVar4 - iVar11) / 2 + iVar11;
            if (*(float *)(pEVar17 + iVar3 * 0x18 + 0xc) <= fVar28) {
              iVar11 = iVar3 + 1;
            }
            else {
              iVar4 = iVar3 + -1;
            }
          } while (iVar11 <= iVar4);
        }
        local_5c = 0;
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        pEVar23 = pEVar17 + iVar4 * 0x18;
        fVar27 = *(float *)(pEVar23 + 0xc);
        if (ABS(fVar27 - fVar28) <= (float)local_68[-0x856]) goto LAB_00557888;
        fVar28 = (fVar28 - fVar27) / (*(float *)(pEVar23 + 0x24) - fVar27);
        if (*(LottieInterpolator **)(pEVar23 + 0x10) != (LottieInterpolator *)0x0) {
          local_5c = 0;
          local_80 = pEVar23;
          fVar28 = (float)LottieInterpolator::progress
                                    (*(LottieInterpolator **)(pEVar23 + 0x10),fVar28);
          pEVar23 = local_80;
        }
        uVar29 = (ulonglong)(uint)fVar28;
        if (pEVar23[0x14] != (EVP_PKEY_CTX)0x0) {
          local_5c = 0;
          iVar4 = 0x18;
          if (fVar28 < *(float *)(local_64 + 0x6c20)) {
            iVar4 = 0;
          }
          pEVar23 = pEVar23 + iVar4;
          goto LAB_00557888;
        }
        uVar5 = (uint)*(ushort *)(pEVar23 + 8);
        pfVar15 = *(float **)pEVar23;
        pEVar17 = *(EVP_PKEY_CTX **)(pEVar23 + 0x18);
        if (uVar5 != 0) {
          pvVar16 = (void *)puVar2[3];
          pEVar12 = (EVP_PKEY_CTX *)0x0;
          uVar7 = puVar2[4];
          do {
            local_5c = 0;
            uVar18 = uVar7 + 1;
            fVar27 = (*(float *)pEVar17 - *pfVar15) * (float)uVar29 + *pfVar15;
            fVar28 = (*(float *)(pEVar17 + 4) - pfVar15[1]) * (float)uVar29 + pfVar15[1];
            if ((uint)puVar2[5] < uVar18) {
              iVar4 = (uVar7 + 2 >> 1) + uVar7;
              puVar2[5] = iVar4;
              local_80 = pEVar23;
              local_7c = pEVar12;
              local_78 = pEVar17;
              local_74 = pfVar15;
              pvVar16 = realloc(pvVar16,iVar4 * 8);
              uVar7 = puVar2[4];
              puVar2[3] = pvVar16;
              uVar18 = uVar7 + 1;
              uVar5 = (uint)*(ushort *)(local_80 + 8);
              pEVar17 = local_78;
              pfVar15 = local_74;
              pEVar12 = local_7c;
              pEVar23 = local_80;
            }
            pEVar12 = pEVar12 + 1;
            pfVar6 = (float *)((int)pvVar16 + uVar7 * 8);
            puVar2[4] = uVar18;
            pfVar15 = pfVar15 + 2;
            *pfVar6 = fVar27;
            pfVar6[1] = fVar28;
            pEVar17 = pEVar17 + 8;
            uVar7 = uVar18;
          } while ((int)pEVar12 < (int)uVar5);
        }
        local_5c = 0;
        pEVar17 = (EVP_PKEY_CTX *)(uint)*(ushort *)(pEVar23 + 10);
        pvVar16 = *(void **)(pEVar23 + 4);
        if (pEVar17 != (EVP_PKEY_CTX *)0x0) {
          iVar4 = puVar2[1];
          pEVar23 = pEVar17 + iVar4;
          pvVar10 = (void *)*puVar2;
          local_80 = pvVar16;
          if ((EVP_PKEY_CTX *)puVar2[2] < pEVar23) {
            puVar2[2] = pEVar23;
            local_7c = pEVar17;
            pvVar10 = realloc(pvVar10,(int)pEVar23 * 4);
            iVar4 = puVar2[1];
            *puVar2 = pvVar10;
            pEVar17 = local_7c;
          }
          pvVar16 = local_80;
          local_80 = pEVar17;
          memcpy((void *)((int)pvVar10 + iVar4 * 4),pvVar16,(int)pEVar17 << 2);
          puVar2[1] = local_80 + puVar2[1];
        }
      }
      *(byte *)(*(int *)(this + 8) + 0x30) = *(byte *)(*(int *)(this + 8) + 0x30) | 1;
      iVar4 = *(int *)(iVar20 + 0x28);
      if (pPVar8 == (Paint *)0x0) {
        if (iVar4 == 7) {
          iVar4 = 3;
          pPVar8 = *(Paint **)(param_2 + 0xc);
        }
        else if (iVar4 == 6) {
          iVar4 = 2;
          pPVar8 = *(Paint **)(param_2 + 0xc);
        }
        else {
          if (iVar4 - 8U < 2) {
            iVar4 = 2;
          }
          pPVar8 = *(Paint **)(param_2 + 0xc);
        }
      }
      else if (iVar4 == 7) {
        if (local_6c == 7) {
          iVar4 = 6;
        }
      }
      else if ((local_6c == 9) && (iVar4 == 9)) {
        iVar4 = 8;
      }
      local_90 = this;
      tvg::Paint::composite(pPVar8,&local_90,iVar4);
      if (local_90 != (Paint *)0x0) {
        (**(code **)(*(int *)local_90 + 4))();
      }
      fVar28 = (float)uVar24;
      piVar21 = piVar21 + 1;
      local_6c = *(int *)(iVar20 + 0x28);
      pPVar8 = this;
    } while (piVar21 < (int *)(*(int *)(param_2 + 0x48) + *(int *)(param_2 + 0x4c) * 4));
  }
  if (param_2[0xac] == (LottieLayer)0x0) {
    if (*(int *)(param_2 + 0x14) != 0) {
      local_5c = 0;
      pEVar23 = (EVP_PKEY_CTX *)LottieLayer::remap(param_2,fVar28,param_4);
      puVar2 = *(undefined4 **)(param_2 + 0x10) + *(int *)(param_2 + 0x14) + -1;
      if (*(undefined4 **)(param_2 + 0x10) <= puVar2) {
        do {
          local_5c = 0;
          local_80 = pEVar23;
          _updateLayer(param_2,(LottieLayer *)*puVar2,(float)pEVar23,param_4);
          puVar2 = puVar2 + -1;
          pEVar23 = local_80;
        } while (*(undefined4 **)(param_2 + 0x10) <= puVar2);
      }
      local_5c = 0;
      fVar28 = 0.0;
      if ((0.0 < *(float *)(param_2 + 100)) && (local_5c = 0, 0.0 < *(float *)(param_2 + 0x68))) {
        tvg::Shape::gen((Shape *)&local_90);
        pPVar8 = local_90;
        local_5c = 0;
        tvg::Shape::appendRect
                  ((Shape *)local_90,fVar28,fVar28,*(float *)(param_2 + 100),
                   *(float *)(param_2 + 0x68),fVar28,fVar28);
        tvg::Paint::transform(pPVar8,pMVar22);
        tvg::Scene::gen((Scene *)local_88);
        local_90 = pPVar8;
        tvg::Paint::composite((Paint *)local_88[0],&local_90,1);
        if (local_90 != (Paint *)0x0) {
          (**(code **)(*(int *)local_90 + 4))();
        }
        local_90 = *(Paint **)(param_2 + 0xc);
        tvg::Scene::push((Scene *)local_88[0],&local_90);
        if (local_90 != (Paint *)0x0) {
          (**(code **)(*(int *)local_90 + 4))();
        }
        *(Shape **)(param_2 + 0xc) = local_88[0];
        pPVar8 = (Paint *)local_88[0];
        goto LAB_00557a2c;
      }
    }
  }
  else if (param_2[0xac] == (LottieLayer)0x1) {
    tvg::Shape::gen((Shape *)local_88);
    local_5c = 0;
    tvg::Shape::appendRect
              (local_88[0],0.0,0.0,*(float *)(param_2 + 100),*(float *)(param_2 + 0x68),0.0,0.0);
    tvg::Shape::fill(local_88[0],(uchar)param_2[0x54],(uchar)param_2[0x58],(uchar)param_2[0x5c],
                     (uchar)param_2[0xa8]);
    local_90 = (Paint *)local_88[0];
    local_88[0] = (Shape *)0x0;
    tvg::Scene::push(*(Scene **)(param_2 + 0xc),&local_90);
    if (local_90 != (Paint *)0x0) {
      (**(code **)(*(int *)local_90 + 4))();
    }
    if (local_88[0] != (Shape *)0x0) {
      tvg::Shape::~Shape(local_88[0]);
    }
  }
  else if (*(int *)(param_2 + 0x14) != 0) {
    local_90 = (Paint *)0x0;
    local_8c = (Paint *)0x0;
    pPVar8 = operator_new(0x24);
    local_5c = 0;
    *(int *)(pPVar8 + 8) = 0;
    *(int *)(pPVar8 + 0xc) = 0;
    *(int *)(pPVar8 + 0x10) = 0;
    *(int *)(pPVar8 + 0x14) = 0;
    *(int *)(pPVar8 + 0x18) = 0;
    *(int *)(pPVar8 + 0x1c) = 0;
    pPVar8[0x20] = (Paint)0x0;
    pPVar8[0x21] = (Paint)0x0;
    pPVar8[0x22] = (Paint)0x1;
    tvg::Shape::gen((Shape *)local_88);
    *(Shape **)(pPVar8 + 8) = local_88[0];
    if (local_8c == (Paint *)0x0) {
      *(int *)pPVar8 = 0;
      *(int *)(pPVar8 + 4) = 0;
      local_90 = pPVar8;
    }
    else {
      *(Paint **)((int)local_8c + 4) = pPVar8;
      *(Paint **)pPVar8 = local_8c;
      *(int *)(pPVar8 + 4) = 0;
    }
    local_5c = 0;
    local_8c = pPVar8;
    _updateChildren((LottieGroup *)param_2,fVar28,(Inlist *)&local_90,param_4);
    pPVar8 = local_90;
    if (local_90 != (Paint *)0x0) {
      do {
        local_90 = *(Paint **)(pPVar8 + 4);
        if ((pPVar8[0x22] != (Paint)0x0) && (*(Shape **)(pPVar8 + 8) != (Shape *)0x0)) {
          tvg::Shape::~Shape(*(Shape **)(pPVar8 + 8));
        }
        operator_delete(*(void **)(pPVar8 + 0x14),0x28);
        free(*(void **)(pPVar8 + 0x18));
        operator_delete(pPVar8,0x24);
        pPVar8 = local_90;
      } while (local_90 != (Paint *)0x0);
      pPVar8 = *(Paint **)(param_2 + 0xc);
      goto LAB_00557a2c;
    }
  }
  pPVar8 = *(Paint **)(param_2 + 0xc);
LAB_00557a2c:
  tvg::Paint::blend(pPVar8,param_2[0x28]);
  if (param_2[0xae] == (LottieLayer)0x0) {
    local_90 = *(Paint **)(param_2 + 0xc);
    tvg::Scene::push(*(Scene **)(local_70 + 0xc),&local_90);
    if (local_90 != (Paint *)0x0) {
      (**(code **)(*(int *)local_90 + 4))();
    }
  }
  return;
}



// === update @ 00558228 ===

/* LottieBuilder::update(LottieComposition*, float) */

undefined4 __thiscall
LottieBuilder::update(LottieBuilder *this,LottieComposition *param_1,float param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  LottieLayer *pLVar3;
  float fVar4;
  ulonglong uVar5;
  
  pLVar3 = *(LottieLayer **)param_1;
  uVar1 = 0;
  if (*(int *)(pLVar3 + 0x14) != 0) {
    fVar4 = *(float *)(param_1 + 0x14);
    if (fVar4 <= fVar4 + param_2) {
      fVar4 = fVar4 + param_2;
    }
    if (*(float *)(param_1 + 0x18) <= fVar4) {
      fVar4 = *(float *)(param_1 + 0x18) - DAT_00586c20;
    }
    uVar5 = (ulonglong)(uint)fVar4;
    tvg::Scene::clear(*(Scene **)(pLVar3 + 0xc),true);
    puVar2 = *(undefined4 **)(pLVar3 + 0x10) + *(int *)(pLVar3 + 0x14) + -1;
    uVar1 = 1;
    if (*(undefined4 **)(pLVar3 + 0x10) <= puVar2) {
      do {
        _updateLayer(pLVar3,(LottieLayer *)*puVar2,(float)uVar5,*(LottieExpressions **)this);
        puVar2 = puVar2 + -1;
        uVar1 = 1;
      } while (*(undefined4 **)(pLVar3 + 0x10) <= puVar2);
    }
  }
  return uVar1;
}



// === _loop<tvg::Array<LottieScalarFrame<unsigned_char>>> @ 00559838 ===

/* float _loop<tvg::Array<LottieScalarFrame<unsigned char> > >(tvg::Array<LottieScalarFrame<unsigned
   char> >*, float, LottieExpression*) */

float _loop<tvg::Array<LottieScalarFrame<unsigned_char>>>
                (Array *param_1,float param_2,LottieExpression *param_3)

{
  int iVar1;
  float fVar2;
  float fVar3;
  
  if (param_2 < *(float *)(param_3 + 0x1c)) {
    iVar1 = *(int *)param_1;
    fVar2 = *(float *)(iVar1 + 4);
    if (fVar2 <= param_2) {
      fVar3 = *(float *)(iVar1 + *(int *)(param_1 + 4) * 0x10 + -0xc);
      if (fVar3 <= param_2) {
        if (param_3[0x20] == (LottieExpression)0x1) {
          fVar2 = fmodf(param_2 - fVar2,fVar3 - fVar2);
          param_2 = fVar2 + *(float *)(*(int *)param_1 + *(int *)(param_3 + 0x18) * 0x10 + 4);
        }
        else if (param_3[0x20] == (LottieExpression)0x5) {
          fVar2 = fmodf(param_2 - fVar2,
                        *(float *)(iVar1 + ((*(int *)(param_1 + 4) + -1) - *(int *)(param_3 + 0x18))
                                           * 0x10 + 4) - fVar2);
          param_2 = fVar2 + *(float *)(*(int *)param_1 + 4);
        }
      }
    }
  }
  return param_2;
}



// === mathRotate @ 0055a20c ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* mathRotate(tvg::Matrix*, float) */

void mathRotate(Matrix *param_1,float param_2)

{
  float local_18;
  float local_14 [2];
  
  if (param_2 != 0.0) {
    local_14[1] = 0.0;
    sincosf((param_2 / DAT_00585fe4) * _DAT_005901e0,&local_18,local_14);
    *(float *)(param_1 + 0xc) = *(float *)(param_1 + 0x10) * local_18;
    *(float *)(param_1 + 4) = -local_18 * *(float *)param_1;
    *(float *)(param_1 + 0x10) = *(float *)(param_1 + 0x10) * local_14[0];
    *(float *)param_1 = *(float *)param_1 * local_14[0];
  }
  return;
}



// === cssUpdateStyle @ 0055b130 ===

/* cssUpdateStyle(SvgNode*, SvgNode*) */

void cssUpdateStyle(SvgNode *param_1,SvgNode *param_2)

{
  SvgNode *pSVar1;
  SvgNode *pSVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  if (*(int *)(param_1 + 0xc) != 0) {
    puVar3 = *(undefined4 **)(param_1 + 8);
    uVar4 = 0;
    do {
      pSVar2 = (SvgNode *)*puVar3;
      uVar4 = uVar4 + 1;
      pSVar1 = (SvgNode *)cssFindStyleNode(param_2,0,*(undefined4 *)pSVar2);
      if (pSVar1 != (SvgNode *)0x0) {
        cssCopyStyleAttr(pSVar2,pSVar1);
        pSVar2 = (SvgNode *)*puVar3;
      }
      cssUpdateStyle(pSVar2,param_2);
      puVar3 = puVar3 + 1;
    } while (uVar4 < *(uint *)(param_1 + 0xc));
    return;
  }
  return;
}



// === mathRotate @ 00563138 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* mathRotate(SwPoint&, long long) */

void mathRotate(SwPoint *param_1,longlong param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float local_40;
  float local_3c [2];
  
  if (param_2 != 0) {
    if ((*(int *)param_1 != 0) || (*(int *)(param_1 + 4) != 0)) {
      local_3c[1] = 0.0;
      fVar4 = (float)*(int *)(param_1 + 4) * DAT_006a11ac;
      fVar3 = (float)*(int *)param_1 * DAT_006a11ac;
      sincosf((float)param_2 * DAT_006a11b0 * DAT_00590e4c,&local_40,local_3c);
      local_3c[1] = 0.0;
      fVar2 = _DAT_006a0d34;
      fVar1 = roundf((local_3c[0] * fVar3 - local_40 * fVar4) * _DAT_006a0d34);
      local_3c[1] = 0.0;
      *(int *)param_1 = (int)fVar1;
      fVar2 = roundf((local_40 * fVar3 + local_3c[0] * fVar4) * fVar2);
      *(int *)(param_1 + 4) = (int)fVar2;
    }
  }
  return;
}



// === mathUpdateOutlineBBox @ 00563fa4 ===

/* mathUpdateOutlineBBox(SwOutline const*, SwBBox const&, SwBBox&, bool) */

undefined4 mathUpdateOutlineBBox(SwOutline *param_1,SwBBox *param_2,SwBBox *param_3,bool param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined3 in_register_0000001d;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  
  if (param_1 != (SwOutline *)0x0) {
    if ((*(int *)(param_1 + 4) != 0) && (*(int *)(param_1 + 0x10) != 0)) {
      piVar5 = *(int **)param_1;
      iVar8 = *piVar5;
      iVar10 = piVar5[1];
      iVar9 = iVar8;
      iVar1 = iVar10;
      piVar3 = piVar5;
      while (piVar2 = piVar3 + 2, piVar2 < piVar5 + *(int *)(param_1 + 4) * 2) {
        iVar7 = *piVar2;
        iVar6 = piVar3[3];
        if (iVar7 < iVar8) {
          iVar8 = iVar7;
        }
        if (iVar9 < iVar7) {
          iVar9 = iVar7;
        }
        if (iVar6 < iVar10) {
          iVar10 = iVar6;
        }
        piVar3 = piVar2;
        if (iVar1 < iVar6) {
          iVar1 = iVar6;
        }
      }
      if (CONCAT31(in_register_0000001d,param_4) == 0) {
        *(int *)param_3 = iVar8 >> 6;
        *(int *)(param_3 + 8) = iVar9 + 0x3f >> 6;
        *(int *)(param_3 + 4) = iVar10 >> 6;
        *(int *)(param_3 + 0xc) = iVar1 + 0x3f >> 6;
      }
      else {
        fVar12 = DAT_006a11ac;
        fVar11 = roundf((float)iVar8 * DAT_006a11ac);
        *(int *)param_3 = (int)fVar11;
        fVar11 = roundf((float)iVar9 * fVar12);
        *(int *)(param_3 + 8) = (int)fVar11;
        fVar11 = roundf((float)iVar10 * fVar12);
        *(int *)(param_3 + 4) = (int)fVar11;
        fVar12 = roundf((float)iVar1 * fVar12);
        *(int *)(param_3 + 0xc) = (int)fVar12;
      }
      uVar4 = mathClipBBox(param_2,param_3);
      return uVar4;
    }
    *(undefined4 *)(param_3 + 0xc) = 0;
    *(undefined4 *)(param_3 + 8) = 0;
    *(undefined4 *)(param_3 + 4) = 0;
    *(undefined4 *)param_3 = 0;
  }
  return 0;
}



// === update_offset @ 0056ed58 ===

void update_offset(int *param_1)

{
  size_t sVar1;
  int iVar2;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    iVar2 = param_1[2];
    sVar1 = strlen((char *)(*param_1 + iVar2));
    param_1[2] = iVar2 + sVar1;
    return;
  }
  return;
}



// === update_eth_infor @ 00572bf0 ===

undefined4 update_eth_infor(void)

{
  byte bVar1;
  int iVar2;
  pthread_t __th;
  int iVar3;
  FILE *pFVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  char *pcVar10;
  byte bVar11;
  char acStack_170 [256];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  uint local_60;
  in_addr local_5c;
  undefined4 local_58;
  undefined4 local_54;
  char local_50 [16];
  in_addr local_40;
  undefined1 auStack_3c [4];
  int local_38;
  int local_34;
  char *local_30;
  
  iVar2 = getodin();
  local_34 = iVar2;
  memset(acStack_170,0,0x100);
  local_50[0] = '\0';
  local_50[1] = '\0';
  local_50[2] = '\0';
  local_50[3] = '\0';
  local_50[4] = '\0';
  local_50[5] = '\0';
  local_50[6] = '\0';
  local_50[7] = '\0';
  local_50[8] = '\0';
  local_50[9] = '\0';
  local_50[10] = '\0';
  local_50[0xb] = '\0';
  local_50[0xc] = '\0';
  local_50[0xd] = '\0';
  local_50[0xe] = '\0';
  local_50[0xf] = '\0';
  __th = pthread_self();
  pthread_detach(__th);
  usleep(100000);
  iVar3 = socket(2,1,0);
  if (iVar3 < 0) {
    bVar11 = 0;
  }
  else {
    local_70 = 0x30687465;
    local_6c = 0;
    local_68 = 0;
    local_64 = 0;
    local_60 = 0;
    local_5c.s_addr = 0;
    local_58 = 0;
    local_54 = 0;
    memset((void *)(iVar2 + 0x3710),0,0x68);
    iVar6 = ioctl(iVar3,0x8913,&local_70);
    if (iVar6 == 0) {
      bVar11 = (local_60 & 1) != 0;
      if ((bool)bVar11) {
        pcVar5 = "1:up";
      }
      else {
        pcVar5 = "0:down";
      }
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                 ,0x178,"update_eth_infor","%s-------->%s \n",&local_70,pcVar5);
    }
    else {
      piVar8 = __errno_location();
      pcVar5 = strerror(*piVar8);
      bVar11 = false;
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                 ,0x17c,"update_eth_infor","get SIOCGIFFLAGS error:%s\n",pcVar5);
    }
    iVar6 = ioctl(iVar3,0x8927,&local_70);
    if (iVar6 == 0) {
      pcVar5 = (char *)(local_34 + 0x3764);
      snprintf(pcVar5,0x12,"%02X:%02X:%02X:%02X:%02X:%02X",local_60 >> 0x10 & 0xff,local_60 >> 0x18,
               local_5c.s_addr & 0xff,local_5c.s_addr >> 8 & 0xff,local_5c.s_addr >> 0x10 & 0xff,
               local_5c.s_addr >> 0x18);
      pcVar10 = "mac ==== %s.\n";
      uVar9 = 0x184;
    }
    else {
      piVar8 = __errno_location();
      pcVar5 = strerror(*piVar8);
      pcVar10 = "ioctl  GET_MAC error:%s\n";
      uVar9 = 0x189;
    }
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
               ,uVar9,"update_eth_infor",pcVar10,pcVar5);
    iVar6 = ioctl(iVar3,0x8915,&local_70);
    if (iVar6 == 0) {
      pcVar10 = inet_ntoa(local_5c);
      if (pcVar10 == (char *)0x0) {
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                   ,0x197,"update_eth_infor","not valid inet addr\n",pcVar5);
      }
      else {
        pcVar5 = strncpy((char *)(local_34 + 0x3714),pcVar10,0x10);
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                   ,0x193,"update_eth_infor","inet addr: %s\n",pcVar5);
      }
      bVar11 = bVar11 | 2;
    }
    else {
      piVar8 = __errno_location();
      pcVar5 = strerror(*piVar8);
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                 ,0x19d,"update_eth_infor","ioctl  GET_IPADDR error:%s\n",pcVar5);
    }
    iVar6 = ioctl(iVar3,0x891b,&local_70);
    if (iVar6 == 0) {
      pcVar10 = inet_ntoa(local_5c);
      if (pcVar10 == (char *)0x0) {
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                   ,0x1ac,"update_eth_infor","not valid inet Mask\n",pcVar5);
        bVar11 = bVar11 | 4;
      }
      else {
        pcVar5 = strncpy((char *)(local_34 + 0x3724),pcVar10,0x10);
        lv_log_add(2,4,
                   "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                   ,0x1a8,"update_eth_infor","Mask: %s\n",pcVar5);
        bVar11 = bVar11 | 4;
      }
    }
    else {
      piVar8 = __errno_location();
      pcVar5 = strerror(*piVar8);
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                 ,0x1b2,"update_eth_infor","ioctl  GET_MASK error:%s\n",pcVar5);
    }
    close(iVar3);
  }
  pFVar4 = fopen("/proc/net/route","r");
  if (pFVar4 == (FILE *)0x0) {
    piVar8 = __errno_location();
    pcVar5 = strerror(*piVar8);
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
               ,0x1cf,"update_eth_infor","GET_route error:%s\n",pcVar5);
  }
  else {
    fgets(acStack_170,0x100,pFVar4);
    do {
      pcVar5 = fgets(acStack_170,0x100,pFVar4);
      if (pcVar5 == (char *)0x0) goto LAB_00572d70;
      iVar3 = __isoc99_sscanf(acStack_170,"%s\t%lX\t%lX",local_50,auStack_3c,&local_40);
    } while (((iVar3 == -1) || (iVar3 = strcmp(local_50,"eth0"), iVar3 != 0)) ||
            (local_40.s_addr == 0));
    pcVar5 = inet_ntoa(local_40);
    pcVar10 = (char *)(local_34 + 0x3734);
    snprintf(pcVar10,0x10,"%s",pcVar5);
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
               ,0x1c4,"update_eth_infor","gateway : %s\n",pcVar10);
LAB_00572d70:
    bVar11 = bVar11 | 8;
    fclose(pFVar4);
  }
  pFVar4 = fopen("/etc/resolv.conf","r");
  iVar3 = 0;
  if (pFVar4 == (FILE *)0x0) {
    perror("Failed to open /etc/resolv.conf");
    bVar1 = bVar11 & 7;
  }
  else {
    local_30 = " DNS nameserver - %s\n";
    while( true ) {
      pcVar5 = fgets(acStack_170,0x100,pFVar4);
      if (pcVar5 == (char *)0x0) break;
      iVar6 = strncmp(acStack_170,"nameserver",10);
      if (iVar6 == 0) {
        pcVar5 = strstr(acStack_170,"eth");
        local_38 = iVar2 + 0x3710 + (iVar3 + 3) * 0x10 + 4;
        if ((pcVar5 != (char *)0x0) &&
           (iVar7 = __isoc99_sscanf(acStack_170,"nameserver %16s",local_38), iVar6 = local_38,
           iVar7 == 1)) {
          local_38 = iVar7;
          lv_log_add(2,4,
                     "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                     ,0x1e0,"update_eth_infor",local_30,iVar6);
          if (iVar3 == local_38) {
            fclose(pFVar4);
            bVar1 = bVar11 & 7;
            bVar11 = bVar11 | 0x10;
            goto LAB_00572ea4;
          }
          iVar3 = 1;
          bVar11 = bVar11 | 0x10;
        }
      }
    }
    fclose(pFVar4);
    bVar1 = bVar11 & 7;
    if (iVar3 == 0) {
      lv_log_add(2,4,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
                 ,0x1eb,"update_eth_infor","No DNS servers found.\n");
      bVar1 = bVar11 & 7;
    }
  }
LAB_00572ea4:
  if (bVar1 == 7) {
    *(undefined4 *)(local_34 + 0x3710) = 1;
  }
  else {
    *(undefined4 *)(local_34 + 0x3710) = 0;
  }
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
             ,0x1f7,"update_eth_infor","ether_infor->connected:0x%x\n",bVar1 == 7);
  lv_log_add(2,4,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/commonutil.c"
             ,0x1f8,"update_eth_infor","ret:0x%x\n",bVar11);
  service_gui_request(0x26,0,0);
  return 0;
}



// === rotate_compress_log_thread_func @ 00574690 ===

undefined4 rotate_compress_log_thread_func(int param_1)

{
  pthread_t __target_thread;
  int iVar1;
  char acStack_298 [256];
  char acStack_198 [256];
  char acStack_98 [128];
  void *local_18 [3];
  
  __target_thread = pthread_self();
  pthread_setname_np(__target_thread,"rotate_c_l");
  pthread_detach(__target_thread);
  memset(acStack_98,0,0x80);
  snprintf(acStack_98,0x80,"gzip -f %s",param_1 + 0x100);
  system(acStack_98);
  lv_free(param_1);
  append_vectorp_log_tmp_file(param_1 + 0x100);
  local_18[0] = (void *)0x0;
  iVar1 = get_vectorp_tmp_file_line_count();
  if ((0x14 < iVar1) && (iVar1 = shift_vectorp_log_tmp_file(local_18), iVar1 == 0)) {
    memset(acStack_198,0,0x100);
    snprintf(acStack_198,0x100,"%s.gz",local_18[0]);
    lv_log_add(2,4,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/utilities/fileutil.c"
               ,0x1f6,"rotate_compress_log_thread_func","first_line====target_log_src==%s",
               acStack_198);
    iVar1 = access(acStack_198,0);
    if (iVar1 == 0) {
      memset(acStack_298,0,0x100);
      snprintf(acStack_298,0x100,"rm -f %s",acStack_198);
      system(acStack_298);
    }
    if (local_18[0] != (void *)0x0) {
      free(local_18[0]);
    }
  }
  return 0;
}



// === rotate_log_file @ 00574808 ===

bool rotate_log_file(void *param_1)

{
  int iVar1;
  pthread_t apStack_10 [2];
  
  iVar1 = pthread_create(apStack_10,(pthread_attr_t *)0x0,rotate_compress_log_thread_func,param_1);
  if (iVar1 != 0) {
    perror("Error creating backup log thread");
    lv_free(param_1);
  }
  return iVar1 != 0;
}



// === utilUpdatePrintProgress @ 00577294 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

double utilUpdatePrintProgress(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  
  iVar1 = getodin();
  iVar2 = *(int *)(iVar1 + 0x670);
  iVar1 = getodin();
  iVar4 = *(int *)(iVar1 + 0x674);
  iVar1 = getodin();
  iVar3 = *(int *)(iVar1 + 0x2378);
  iVar1 = getodin();
  if (((0 < iVar2) && (0 < iVar4)) && (0 < iVar3)) {
    if (iVar3 <= iVar2) {
      return 0.0;
    }
    if (iVar4 <= iVar3) {
      return _DAT_006131a0;
    }
    if ((0 < iVar3 - iVar2) && (0 < iVar4 - iVar2)) {
      dVar5 = (double)(iVar3 - iVar2);
      return dVar5 / (double)(int)((ulonglong)dVar5 >> 0x20);
    }
  }
  if (0.0 <= *(double *)(iVar1 + 0x2370)) {
    return *(double *)(iVar1 + 0x2370);
  }
  return 0.0;
}



// === utilUpdateCurrentPrintInfo @ 0057741c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void utilUpdateCurrentPrintInfo(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  double in_f0_1;
  uint uVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double local_38;
  
  utilUpdatePrintProgress();
  iVar1 = getodin();
  dVar11 = *(double *)(iVar1 + 0x20b0);
  iVar1 = getodin();
  dVar10 = *(double *)(iVar1 + 0x2358);
  iVar1 = getodin();
  iVar1 = *(int *)(iVar1 + 0x640);
  if ((in_f0_1 <= 0.0) || (dVar11 <= 0.0)) {
    iVar2 = getodin();
    uVar5 = 0;
    iVar6 = 0;
    local_38 = in_f0_1;
    if (*(int *)(iVar2 + 0x898) == 0) goto LAB_005777d4;
LAB_00577590:
    iVar2 = getodin();
    iVar2 = *(int *)(iVar2 + 0x898);
    in_f0_1 = local_38;
    if ((double)iVar2 < dVar11) goto LAB_005777d4;
    dVar8 = ((double)iVar2 - dVar11) / dVar10;
    if (dVar8 < DAT_00614a18) {
      uVar4 = (uint)dVar8;
      uVar7 = uVar4;
    }
    else {
      uVar4 = (int)(dVar8 - DAT_00614a18) | 0x80000000;
      uVar7 = (int)(dVar8 - DAT_00614a18);
    }
    in_f0_1 = (double)CONCAT44(uVar7,SUB84(local_38,0));
    if ((0 < iVar1) &&
       (in_f0_1 = (double)CONCAT44(iVar1,SUB84(local_38,0)), dVar11 <= (double)iVar1))
    goto LAB_00577804;
  }
  else {
    dVar9 = dVar11 / in_f0_1;
    dVar8 = (dVar9 - dVar11) / dVar10;
    if (dVar8 < DAT_00614a18) {
      uVar5 = (uint)dVar8;
    }
    else {
      uVar5 = (int)(dVar8 - DAT_00614a18) | 0x80000000;
    }
    iVar6 = (int)dVar9;
    in_f0_1 = (double)CONCAT44((int)dVar9,SUB84(in_f0_1,0));
    iVar2 = getodin();
    local_38 = in_f0_1;
    if (*(int *)(iVar2 + 0x898) != 0) goto LAB_00577590;
LAB_005777d4:
    iVar2 = iVar6;
    if (iVar1 < 1) goto LAB_00577640;
    in_f0_1 = (double)CONCAT44(iVar1,SUB84(in_f0_1,0));
    uVar4 = 0;
    if ((double)iVar1 < dVar11) goto LAB_00577640;
LAB_00577804:
    dVar10 = ((double)iVar1 - dVar11) / dVar10;
    if (dVar10 < DAT_00614a18) {
      uVar3 = (uint)dVar10;
      uVar7 = uVar3;
    }
    else {
      uVar3 = (int)(dVar10 - DAT_00614a18) | 0x80000000;
      uVar7 = (int)(dVar10 - DAT_00614a18);
    }
    in_f0_1 = (double)CONCAT44(uVar7,SUB84(in_f0_1,0));
    iVar2 = iVar1;
    if (uVar3 != 0) {
      uVar5 = uVar3;
      if (uVar4 != 0) {
        uVar5 = uVar4;
      }
      goto LAB_00577640;
    }
  }
  if (uVar4 != 0) {
    uVar5 = uVar4;
  }
LAB_00577640:
  iVar1 = getodin();
  *(double *)(iVar1 + 0x888) = in_f0_1;
  iVar1 = getodin();
  *(int *)(iVar1 + 0x890) = iVar2;
  iVar1 = getodin();
  *(uint *)(iVar1 + 0x894) = uVar5;
  if (DAT_00696658 < dVar11) {
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === utilUpdateSpeedMode @ 00577b90 ===

undefined4 utilUpdateSpeedMode(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_18 [2];
  undefined4 local_10;
  
  local_10 = 0;
  iVar2 = 3;
  iVar1 = getodin();
  if (*(char *)(iVar1 + 0x236a) == '\0') {
    iVar1 = getodin();
    local_10 = 0;
    iVar1 = (int)(*(double *)(iVar1 + 0x2358) * DAT_00613d68 + 0.0);
    if (iVar1 == 100) {
      iVar2 = 1;
    }
    else if (iVar1 == 0x7d) {
      iVar2 = 0;
    }
    else {
      iVar2 = 4;
      if (iVar1 == 0x32) {
        iVar2 = 2;
      }
    }
  }
  iVar1 = getodin();
  if (*(int *)(iVar1 + 0xf6c) != iVar2) {
    iVar1 = getodin();
    *(int *)(iVar1 + 0xf6c) = iVar2;
    local_18[0] = 10;
    service_gui_request(0xd,local_18,4);
  }
  return 0;
}



// === utilUpdateCurrentFileLayer @ 00577c90 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void utilUpdateCurrentFileLayer(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  iVar1 = getodin();
  if (*(int *)(iVar1 + 0x270c) != 5) {
    iVar1 = getodin();
    iVar2 = getodin();
    if (*(char *)(iVar2 + 0x678) != '\0') {
      iVar2 = getodin();
      dVar4 = 0.0;
      if ((((0.0 < *(double *)(iVar2 + 0x20b0)) &&
           (iVar2 = getodin(), dVar4 < *(double *)(iVar2 + 0x618))) &&
          (iVar2 = getodin(), dVar4 < *(double *)(iVar2 + 0x610))) &&
         ((iVar1 != -0x22f0 && (dVar5 = *(double *)(iVar1 + 0x2300), dVar4 <= dVar5)))) {
        iVar1 = getodin();
        dVar5 = dVar5 - *(double *)(iVar1 + 0x618);
        iVar1 = getodin();
        dVar4 = ceil(dVar5 / *(double *)(iVar1 + 0x610) + _DAT_006131a0);
        uVar3 = (uint)dVar4;
        if (0 < (int)uVar3) {
          if ((DAT_0084c880 != 0) && (DAT_0084c880 < uVar3)) {
            uVar3 = DAT_0084c880;
          }
          printf("currentLayer = %d\n",uVar3);
          iVar1 = getodin();
          *(uint *)(iVar1 + 0x89c) = uVar3;
          return;
        }
        printf("currentLayer = %d\n",uVar3);
      }
    }
    iVar1 = getodin();
    *(undefined4 *)(iVar1 + 0x89c) = 0;
  }
  return;
}



// === verify_ota_result @ 0057bf10 ===

undefined4 verify_ota_result(void)

{
  return 0;
}



// === update_log_switch @ 0057c3c4 ===

void update_log_switch(void)

{
  system("mkdir -p /usr/data/creality/debug");
  DAT_006d3b0d = DAT_006d3b0c;
  init_module_log_level(log_switch,&DAT_006d3b0d);
  DAT_006d3b15 = DAT_006d3b14;
  init_module_log_level(PTR_s_extcom_006d3b10,&DAT_006d3b15);
  return;
}



// === ws_cmd_cache_add @ 0057c624 ===

undefined4 ws_cmd_cache_add(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  void *pvVar3;
  void *pvVar4;
  size_t __size;
  int local_20 [2];
  
  puVar2 = (undefined4 *)lv_ll_ins_head();
  *puVar2 = param_3;
  *(undefined1 *)(puVar2 + 3) = 0;
  pvVar3 = (void *)lws_json_simple_find(param_2,0x1000,"\"method\":",local_20);
  iVar1 = local_20[0];
  __size = local_20[0] + 1;
  pvVar4 = malloc(__size);
  puVar2[2] = pvVar4;
  memcpy(pvVar4,pvVar3,__size);
  *(undefined1 *)(puVar2[2] + iVar1) = 0;
  pvVar3 = (void *)lws_json_simple_find(param_2,0x1000,"\"cxname\":",local_20);
  pvVar4 = malloc(local_20[0] + 1U);
  puVar2[1] = pvVar4;
  memcpy(pvVar4,pvVar3,local_20[0] + 1U);
  *(undefined1 *)(puVar2[1] + local_20[0]) = 0;
  return 0;
}



// === ws_cmd_cache_find @ 0057c798 ===

int * ws_cmd_cache_find(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)lv_ll_get_head();
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*piVar1 == param_2) break;
    piVar1 = (int *)lv_ll_get_next(param_1,piVar1);
  }
  return piVar1;
}



// === ws_init_cmd_cache @ 0057cb34 ===

undefined4 ws_init_cmd_cache(undefined4 param_1)

{
  lv_ll_init(param_1,0x10);
  return 1;
}



// === AesEncryptToBase64 @ 0057cd20 ===

void * AesEncryptToBase64(uchar *param_1,uint param_2)

{
  uchar *out;
  EVP_CIPHER_CTX *ctx;
  EVP_CIPHER *cipher;
  int iVar1;
  void *__s;
  char *__s_00;
  size_t __n;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  char local_3c [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  char local_2c [4];
  int iStack_28;
  int local_24 [2];
  
  if ((int)param_2 < 1) {
    return (void *)0x0;
  }
  if ((param_2 & 0xf) == 0) {
    out = malloc(param_2);
    memset(out,0,param_2);
LAB_0057cd70:
    local_38 = DAT_006a3598;
    local_34 = DAT_006a359c;
    local_30 = DAT_006a35a0;
    local_2c[0] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[0];
    local_2c[1] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[1];
    local_2c[2] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[2];
    local_2c[3] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[3];
    local_48 = DAT_006a35dc;
    local_44 = DAT_006a35e0;
    local_40 = DAT_006a35e4;
    local_3c[0] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[0];
    local_3c[1] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[1];
    local_3c[2] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[2];
    local_3c[3] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[3];
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == (EVP_CIPHER_CTX *)0x0) {
      puts("Failed to create EVP_CIPHER_CTX");
    }
    else {
      printf("[AES_CBC256_Encrypt] in address: %p, out address: %p\n",param_1,out);
      cipher = EVP_aes_128_cbc();
      iVar1 = EVP_EncryptInit_ex(ctx,cipher,(ENGINE *)0x0,(uchar *)&local_38,(uchar *)&local_48);
      if (iVar1 == 1) {
        iVar1 = EVP_CIPHER_CTX_set_padding(ctx,0);
        if (iVar1 == 1) {
          iVar1 = EVP_EncryptUpdate(ctx,out,local_24,param_1,param_2);
          if (iVar1 != 1) {
            fwrite("Error: EVP_EncryptUpdate failed\n",1,0x20,stderr);
            ERR_print_errors_fp(stderr);
            EVP_CIPHER_CTX_free(ctx);
            goto LAB_0057ce6c;
          }
          iVar1 = EVP_EncryptFinal_ex(ctx,out + local_24[0],&iStack_28);
          if (iVar1 == 1) {
            EVP_CIPHER_CTX_free(ctx);
            goto LAB_0057ce78;
          }
          __s_00 = "EVP_EncryptFinal_ex failed";
        }
        else {
          __s_00 = "Failed to disable padding";
        }
      }
      else {
        __s_00 = "EVP_EncryptInit_ex failed";
      }
      puts(__s_00);
      EVP_CIPHER_CTX_free(ctx);
    }
  }
  else {
    param_2 = (param_2 - (param_2 & 0xf)) + 0x10;
    out = malloc(param_2);
    memset(out,0,param_2);
    if ((param_2 & 0xf) == 0) goto LAB_0057cd70;
    puts("length is not a multiple of 16 bytes");
  }
LAB_0057ce6c:
  puts("encrypt error!");
LAB_0057ce78:
  __n = param_2 << 3;
  __s = (void *)lv_malloc(__n);
  memset(__s,0,__n);
  Base64_encode(__s,__n,out,param_2);
  free(out);
  return __s;
}



// === AesDecryptFromBase64 @ 0057cfa0 ===

uchar * AesDecryptFromBase64(undefined4 param_1,size_t param_2)

{
  uchar *in;
  uint __n;
  uchar *out;
  EVP_CIPHER_CTX *ctx;
  EVP_CIPHER *cipher;
  int iVar1;
  char *__s;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  char local_3c [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  char local_2c [4];
  int iStack_28;
  int local_24 [2];
  
  if ((int)param_2 < 1) {
    return (uchar *)0x0;
  }
  in = (uchar *)lv_malloc(param_2);
  memset(in,0,param_2);
  __n = Base64_decode(in,param_2,param_1,param_2);
  printf("decodeLen: %d\n",__n);
  out = (uchar *)lv_malloc(__n + 1);
  memset(out,0,__n);
  if ((__n & 0xf) == 0) {
    local_38 = DAT_006a3598;
    local_34 = DAT_006a359c;
    local_30 = DAT_006a35a0;
    local_2c[0] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[0];
    local_2c[1] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[1];
    local_2c[2] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[2];
    local_2c[3] = s_rc4Vgjm5AGn5g8mWkWjDvX38RMyZ7wbC_006a35a4[3];
    local_48 = DAT_006a35dc;
    local_44 = DAT_006a35e0;
    local_40 = DAT_006a35e4;
    local_3c[0] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[0];
    local_3c[1] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[1];
    local_3c[2] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[2];
    local_3c[3] = s_z6GmV9y4qG3FjEt6CxChz_006a35e8[3];
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == (EVP_CIPHER_CTX *)0x0) {
      puts("Failed to create EVP_CIPHER_CTX");
    }
    else {
      cipher = EVP_aes_128_cbc();
      iVar1 = EVP_DecryptInit_ex(ctx,cipher,(ENGINE *)0x0,(uchar *)&local_38,(uchar *)&local_48);
      if (iVar1 == 1) {
        iVar1 = EVP_CIPHER_CTX_set_padding(ctx,0);
        if (iVar1 == 1) {
          iVar1 = EVP_DecryptUpdate(ctx,out,local_24,in,__n);
          if (iVar1 == 1) {
            iVar1 = EVP_DecryptFinal_ex(ctx,out + local_24[0],&iStack_28);
            if (iVar1 == 1) {
              EVP_CIPHER_CTX_free(ctx);
              goto LAB_0057d0e4;
            }
            __s = "EVP_DecryptFinal_ex failed";
          }
          else {
            __s = "EVP_DecryptUpdate failed";
          }
        }
        else {
          __s = "Failed to disable padding";
        }
      }
      else {
        __s = "EVP_DecryptInit_ex failed";
      }
      puts(__s);
      EVP_CIPHER_CTX_free(ctx);
    }
  }
  else {
    puts("length is not a multiple of 16 bytes");
  }
  puts("decrypt error!");
LAB_0057d0e4:
  lv_free(in);
  return out;
}



// === AesEncryptToFile @ 0057d1e8 ===

undefined4 AesEncryptToFile(char *param_1,undefined4 param_2,undefined4 param_3)

{
  char *__s;
  FILE *__stream;
  int iVar1;
  undefined4 uVar2;
  
  __s = (char *)AesEncryptToBase64(param_2,param_3);
  if (__s == (char *)0x0) {
    uVar2 = 0xffffffff;
  }
  else {
    __stream = fopen(param_1,"w");
    if (__stream == (FILE *)0x0) {
      perror("Failed to open file");
      uVar2 = 0xffffffff;
      lv_free(__s);
    }
    else {
      iVar1 = fputs(__s,__stream);
      if (iVar1 == -1) {
        perror("Failed to write to file");
        fclose(__stream);
        lv_free(__s);
        uVar2 = 0xffffffff;
      }
      else {
        fclose(__stream);
        uVar2 = 0;
        lv_free(__s);
      }
    }
  }
  return uVar2;
}



// === AesDecryptFromFile @ 0057d2c4 ===

undefined4 AesDecryptFromFile(char *param_1)

{
  FILE *__stream;
  void *__s;
  stat sStack_a8;
  undefined4 local_18;
  
  __stream = fopen(param_1,"r");
  if (__stream == (FILE *)0x0) {
    puts("open file failed");
    local_18 = 0;
  }
  else {
    __xstat(3,param_1,&sStack_a8);
    __s = (void *)lv_malloc(sStack_a8.st_blksize);
    memset(__s,0,sStack_a8.st_blksize);
    fread(__s,sStack_a8.st_blksize,1,__stream);
    fclose(__stream);
    local_18 = AesDecryptFromBase64(__s,sStack_a8.st_blksize);
    lv_free(__s);
  }
  return local_18;
}



// === lv_qrcode_update @ 0057e868 ===

undefined4 lv_qrcode_update(int param_1,undefined4 param_2,uint param_3)

{
  ushort uVar1;
  code *pcVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *in_zero;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  byte bVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  char *pcVar17;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68 [2];
  int local_60;
  uint local_5c;
  int local_58;
  int local_54;
  int local_50;
  uint local_4c;
  int local_48;
  int local_44;
  uint local_40;
  int local_3c;
  int local_38;
  uint local_34;
  int local_30;
  int local_2c;
  
  iVar5 = lv_canvas_get_draw_buf();
  if (iVar5 == 0) {
    lv_log_add(2,3,
               "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/libs/qrcode/lv_qrcode.c"
               ,100,"lv_qrcode_update","canvas draw buffer is NULL");
    return 0;
  }
  lv_draw_buf_clear(iVar5,0);
  lv_color_to_32(&local_6c,(uint)*(uint3 *)(param_1 + 0x7f),0xff);
  lv_canvas_set_palette(param_1,0,local_6c);
  lv_color_to_32(&local_70,*(undefined4 *)(param_1 + 0x7c),0xff);
  lv_canvas_set_palette(param_1,1,local_70);
  lv_image_cache_drop(iVar5);
  lv_obj_invalidate(param_1);
  if (((param_3 < 0xf4f) && (iVar6 = qrcodegen_getMinFitVersion(1,param_3), 0 < iVar6)) &&
     (iVar7 = qrcodegen_version2size(iVar6), 0 < iVar7)) {
    iVar16 = (int)(uint)*(ushort *)(iVar5 + 4) / iVar7;
    if (iVar7 == 0) {
      trap(7);
    }
    iVar7 = iVar6 + 1;
    if (iVar16 != 0) {
      if (iVar7 < 0x28) {
        do {
          iVar8 = qrcodegen_version2size(iVar7);
          iVar6 = iVar7 + -1;
          if ((int)(uint)*(ushort *)(iVar5 + 4) < iVar8 * iVar16) goto LAB_0057e9d4;
          iVar7 = iVar7 + 1;
        } while (iVar7 != 0x28);
        iVar6 = 0x27;
      }
LAB_0057e9d4:
      qrcodegen_version2size(iVar6);
      iVar7 = iVar6 * 4 + 0x11;
      iVar7 = (iVar7 * iVar7 + 7 >> 3) + 1;
      local_54 = lv_malloc(iVar7);
      if (local_54 == 0) {
        pcVar17 = "qr0 != NULL";
        uVar9 = 0x82;
      }
      else {
        iVar7 = lv_malloc(iVar7);
        if (iVar7 != 0) {
          local_30 = iVar7;
          lv_memcpy(iVar7,param_2,param_3);
          iVar16 = local_54;
          local_60 = qrcodegen_encodeBinary(iVar7,param_3,local_54,1,iVar6,iVar6,0xffffffff,1);
          if (local_60 == 0) {
            lv_free(iVar16);
            lv_free(iVar7);
            return 0;
          }
          uVar9 = lv_obj_get_display(param_1);
          lv_display_enable_invalidation(uVar9,0);
          uVar1 = *(ushort *)(iVar5 + 4);
          iVar6 = qrcodegen_getSize(local_54);
          iVar7 = (int)(uint)uVar1 / iVar6;
          if (iVar6 == 0) {
            trap(7);
          }
          iVar8 = *(int *)(iVar5 + 0x10);
          iVar16 = iVar8 + 8;
          uVar13 = (int)(uint)uVar1 % iVar6 >> 1;
          local_48 = iVar16;
          lv_color_hex(local_68,1);
          uVar12 = (uint)*(ushort *)(iVar5 + 8);
          local_40 = iVar6 * iVar7 + uVar13;
          if ((int)uVar13 < (int)local_40) {
            local_3c = iVar7 * uVar12;
            local_2c = (int)local_40 >> 3;
            local_34 = (uint)(iVar7 < 2);
            local_38 = -8 - iVar8;
            iVar16 = uVar13 * uVar12 + iVar16;
            local_5c = uVar13;
            do {
              uVar3 = local_40;
              iVar5 = local_54;
              local_44 = local_38 + iVar16;
              uVar14 = 0;
              iVar6 = local_5c - uVar13;
              if (iVar7 == 0) {
                trap(7);
              }
              local_58 = local_48 + local_44;
              uVar11 = 0;
              iVar8 = 0;
              uVar4 = uVar13;
              local_50 = iVar16;
              local_4c = uVar12;
              do {
                while( true ) {
                  uVar15 = uVar4;
                  if (iVar7 == 0) {
                    trap(7);
                  }
                  iVar16 = qrcodegen_getModule(iVar5,(int)(uVar15 - uVar13) / iVar7,iVar6 / iVar7);
                  if ((iVar8 != 0) || ((uVar15 & 7) == 0)) break;
                  if (iVar16 != 0) {
                    lv_canvas_set_px(param_1,uVar15,local_5c,local_68[0],0xff);
                  }
LAB_0057eb68:
                  bVar10 = (byte)uVar11;
                  uVar4 = uVar15 + 1;
                  if (uVar3 == uVar15 + 1) goto LAB_0057ebec;
                }
                if (iVar16 == 0) {
                  uVar11 = 1 << (7 - uVar14 & 0x1f) & 0xffU | uVar11;
                }
                uVar14 = uVar14 + 1 & 0xff;
                iVar8 = local_60;
                if (uVar14 != 8) goto LAB_0057eb68;
                *(byte *)(local_58 + ((int)uVar15 >> 3)) = ~(byte)uVar11;
                uVar14 = 0;
                uVar11 = 0;
                bVar10 = 0;
                uVar4 = uVar15 + 1;
              } while (uVar3 != uVar15 + 1);
LAB_0057ebec:
              uVar12 = local_4c;
              iVar16 = local_50;
              if (uVar14 != 0) {
                *(byte *)(local_48 + local_2c + local_44) =
                     ~((char)(1 << (8 - uVar14 & 0x1f)) - 1U | bVar10);
              }
              if (local_34 == 0) {
                iVar6 = 1;
                iVar5 = local_50;
                do {
                  iVar5 = iVar5 + uVar12;
                  iVar6 = iVar6 + 1;
                  lv_memcpy(iVar5,iVar16,uVar12);
                } while (iVar7 != iVar6);
              }
              local_5c = local_5c + iVar7;
              iVar16 = iVar16 + local_3c;
            } while ((int)local_5c < (int)(uVar15 + 1));
          }
          uVar9 = lv_obj_get_display(param_1);
          lv_display_enable_invalidation(uVar9,1);
          lv_free(local_54);
          lv_free(local_30);
          return 1;
        }
        pcVar17 = "data_tmp != NULL";
        uVar9 = 0x84;
        local_30 = 0;
      }
      lv_log_add(2,3,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/libs/qrcode/lv_qrcode.c"
                 ,uVar9,"lv_qrcode_update","Asserted at expression: %s (%s)",pcVar17,"Out of memory"
                );
      *in_zero = 0;
                    /* WARNING: Does not return */
      pcVar2 = (code *)trap(0);
      (*pcVar2)();
    }
  }
  return 0;
}



// === getTotalBits @ 0057f784 ===

int getTotalBits(undefined4 *param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined4 *in_zero;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  
  if (param_1 == (undefined4 *)0x0) {
    iVar4 = 0;
    if (param_2 != 0) {
      pcVar8 = "segs != NULL || len == 0";
      uVar3 = 0x411;
LAB_0057f85c:
      lv_log_add(2,3,
                 "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/libs/qrcode/qrcodegen.c"
                 ,uVar3,"getTotalBits","Asserted at expression: %s",pcVar8);
      *in_zero = 0;
                    /* WARNING: Does not return */
      pcVar1 = (code *)trap(0);
      (*pcVar1)();
    }
  }
  else if (param_2 == 0) {
    iVar4 = 0;
  }
  else {
    iVar7 = 0;
    iVar4 = 0;
    do {
      uVar5 = param_1[1];
      uVar6 = param_1[3];
      if (0x7fff < uVar5) {
        pcVar8 = "0 <= numChars && numChars <= INT16_MAX";
        uVar3 = 0x416;
        goto LAB_0057f85c;
      }
      if (0x7fff < uVar6) {
        pcVar8 = "0 <= bitLength && bitLength <= INT16_MAX";
        uVar3 = 0x417;
        goto LAB_0057f85c;
      }
      uVar2 = numCharCountBits(*param_1,param_3);
      if (0x10 < uVar2) {
        pcVar8 = "0 <= ccbits && ccbits <= 16";
        uVar3 = 0x419;
        goto LAB_0057f85c;
      }
      if (1 << (uVar2 & 0x1f) <= (int)uVar5) {
        return -1;
      }
      iVar4 = iVar4 + uVar2 + 4 + uVar6;
      iVar7 = iVar7 + 1;
      if (0x7fff < iVar4) {
        return -1;
      }
      param_1 = param_1 + 4;
    } while (param_2 != iVar7);
  }
  return iVar4;
}



// === update_src_info @ 0058474c ===

void update_src_info(int *param_1,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    lv_memset(param_1,0,0x10);
    return;
  }
  iVar1 = lv_image_decoder_get_info(param_2,param_1 + 1);
  if (iVar1 == 1) {
    *param_1 = param_2;
    return;
  }
  lv_log_add(2,2,
             "/var/jenkins_home/workspace/IngenicX2600-security-build/vectorprime/localgui/lvgl/src/widgets/imagebutton/lv_imagebutton.c"
             ,0x14d,"update_src_info","can\'t get info");
  return;
}



// === lws_hdr_total_length @ 006b2ba0 ===

void lws_hdr_total_length(void)

{
  (*(code *)PTR_lws_hdr_total_length_006c4048)();
  return;
}



// === EVP_EncryptInit_ex @ 006b2bc0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,EVP_CIPHER *cipher,ENGINE *impl,uchar *key,uchar *iv)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_EncryptInit_ex_006c4050)();
  return iVar1;
}



// === EVP_DecryptInit_ex @ 006b2d70 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_DecryptInit_ex(EVP_CIPHER_CTX *ctx,EVP_CIPHER *cipher,ENGINE *impl,uchar *key,uchar *iv)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_DecryptInit_ex_006c40bc)();
  return iVar1;
}



// === lws_ring_update_oldest_tail @ 006b2f30 ===

void lws_ring_update_oldest_tail(void)

{
  (*(code *)PTR_lws_ring_update_oldest_tail_006c412c)();
  return;
}



// === strsignal @ 006b2fa0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strsignal(int __sig)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_strsignal_006c4148)();
  return pcVar1;
}



// === EVP_EncryptUpdate @ 006b3550 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx,uchar *out,int *outl,uchar *in,int inl)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_EncryptUpdate_006c42b4)();
  return iVar1;
}



// === pthread_cond_signal @ 006b35d0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_cond_signal_006c42d4)();
  return iVar1;
}



// === EVP_EncryptFinal_ex @ 006b3630 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx,uchar *out,int *outl)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_EncryptFinal_ex_006c42ec)();
  return iVar1;
}



// === pthread_mutex_unlock @ 006b38c0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_mutex_unlock_006c4390)();
  return iVar1;
}



// === EVP_DecryptFinal_ex @ 006b38d0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_DecryptFinal_ex(EVP_CIPHER_CTX *ctx,uchar *outm,int *outl)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_DecryptFinal_ex_006c4394)();
  return iVar1;
}



// === lws_add_http_header_by_token @ 006b3900 ===

void lws_add_http_header_by_token(void)

{
  (*(code *)PTR_lws_add_http_header_by_token_006c43a0)();
  return;
}



// === signal @ 006b3a20 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;
  
  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_006c43e8)();
  return p_Var1;
}



// === EVP_DecryptUpdate @ 006b3b70 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_DecryptUpdate(EVP_CIPHER_CTX *ctx,uchar *out,int *outl,uchar *in,int inl)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_DecryptUpdate_006c443c)();
  return iVar1;
}



// === lws_hdr_total_length @ 0084f034 ===

/* WARNING: Control flow encountered bad instruction data */

void lws_hdr_total_length(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === EVP_EncryptInit_ex @ 0084f03c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,EVP_CIPHER *cipher,ENGINE *impl,uchar *key,uchar *iv)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_EncryptInit_ex@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_DecryptInit_ex @ 0084f0a8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_DecryptInit_ex(EVP_CIPHER_CTX *ctx,EVP_CIPHER *cipher,ENGINE *impl,uchar *key,uchar *iv)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_DecryptInit_ex@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === lws_ring_update_oldest_tail @ 0084f118 ===

/* WARNING: Control flow encountered bad instruction data */

void lws_ring_update_oldest_tail(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === strsignal @ 0084f134 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strsignal(int __sig)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* strsignal@@GLIBC_2.0 */
  halt_baddata();
}



// === EVP_EncryptUpdate @ 0084f2a0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx,uchar *out,int *outl,uchar *in,int inl)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_EncryptUpdate@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_cond_signal @ 0084f2c0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_cond_signal@@GLIBC_2.3.2 */
  halt_baddata();
}



// === EVP_EncryptFinal_ex @ 0084f2d8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx,uchar *out,int *outl)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_EncryptFinal_ex@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_mutex_unlock @ 0084f37c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_mutex_unlock@@GLIBC_2.0 */
  halt_baddata();
}



// === EVP_DecryptFinal_ex @ 0084f380 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_DecryptFinal_ex(EVP_CIPHER_CTX *ctx,uchar *outm,int *outl)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_DecryptFinal_ex@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === lws_add_http_header_by_token @ 0084f38c ===

/* WARNING: Control flow encountered bad instruction data */

void lws_add_http_header_by_token(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === signal @ 0084f3d0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* signal@@GLIBC_2.0 */
  halt_baddata();
}



// === EVP_DecryptUpdate @ 0084f428 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_DecryptUpdate(EVP_CIPHER_CTX *ctx,uchar *out,int *outl,uchar *in,int inl)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_DecryptUpdate@@OPENSSL_1_1_0 */
  halt_baddata();
}


