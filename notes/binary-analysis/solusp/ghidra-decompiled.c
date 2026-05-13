
// === _M_assign_unique<std::pair<AIMode_const,HS_AI_RESULT_TYPE>const*> @ 0040c450 ===

/* void std::_Rb_tree<AIMode, std::pair<AIMode const, HS_AI_RESULT_TYPE>,
   std::_Select1st<std::pair<AIMode const, HS_AI_RESULT_TYPE> >, std::less<AIMode>,
   std::allocator<std::pair<AIMode const, HS_AI_RESULT_TYPE> > >::_M_assign_unique<std::pair<AIMode
   const, HS_AI_RESULT_TYPE> const*>(std::pair<AIMode const, HS_AI_RESULT_TYPE> const*,
   std::pair<AIMode const, HS_AI_RESULT_TYPE> const*) */

void __thiscall
std::
_Rb_tree<AIMode,std::pair<AIMode_const,HS_AI_RESULT_TYPE>,std::_Select1st<std::pair<AIMode_const,HS_AI_RESULT_TYPE>>,std::less<AIMode>,std::allocator<std::pair<AIMode_const,HS_AI_RESULT_TYPE>>>
::_M_assign_unique<std::pair<AIMode_const,HS_AI_RESULT_TYPE>const*>
          (_Rb_tree<AIMode,std::pair<AIMode_const,HS_AI_RESULT_TYPE>,std::_Select1st<std::pair<AIMode_const,HS_AI_RESULT_TYPE>>,std::less<AIMode>,std::allocator<std::pair<AIMode_const,HS_AI_RESULT_TYPE>>>
           *this,pair *param_1,pair *param_2)

{
  _Rb_tree_node_base *p_Var1;
  int iVar2;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree_node_base *p_Var4;
  _Rb_tree_node_base *p_Var5;
  _Rb_tree_node_base *p_Var6;
  _Rb_tree_node *p_Var7;
  bool bVar8;
  int local_30;
  _Rb_tree_node_base *local_2c;
  
  p_Var7 = *(_Rb_tree_node **)(this + 8);
  if (p_Var7 == (_Rb_tree_node *)0x0) {
    p_Var5 = (_Rb_tree_node_base *)0x0;
  }
  else {
    p_Var1 = *(_Rb_tree_node_base **)(this + 0x10);
    *(undefined4 *)(p_Var7 + 4) = 0;
    p_Var5 = *(_Rb_tree_node_base **)(p_Var1 + 8);
    if (p_Var5 == (_Rb_tree_node_base *)0x0) {
      p_Var5 = p_Var1;
    }
  }
  p_Var1 = (_Rb_tree_node_base *)(this + 4);
  *(undefined4 *)(this + 8) = 0;
  *(_Rb_tree_node_base **)(this + 0xc) = p_Var1;
  *(_Rb_tree_node_base **)(this + 0x10) = p_Var1;
  *(undefined4 *)(this + 0x14) = 0;
  if (param_1 == param_2) {
LAB_0040c5a4:
    _M_erase(this,p_Var7);
    return;
  }
  iVar2 = 0;
  do {
    p_Var4 = p_Var5;
    if ((iVar2 == 0) ||
       (p_Var6 = *(_Rb_tree_node_base **)(this + 0x10), *(int *)param_1 <= *(int *)(p_Var6 + 0x10)))
    {
      _M_get_insert_unique_pos((AIMode *)&local_30);
      if (local_2c != (_Rb_tree_node_base *)0x0) {
        bVar8 = true;
        p_Var6 = local_2c;
        if (local_30 == 0) goto LAB_0040c4d4;
        if (p_Var5 != (_Rb_tree_node_base *)0x0) goto LAB_0040c4f0;
        goto LAB_0040c580;
      }
    }
    else {
LAB_0040c4d4:
      bVar8 = true;
      if (p_Var1 != p_Var6) {
        bVar8 = *(int *)param_1 < *(int *)(p_Var6 + 0x10);
      }
      if (p_Var5 == (_Rb_tree_node_base *)0x0) {
LAB_0040c580:
                    /* try { // try from 0040c580 to 0040c587 has its CatchHandler @ 0040c62c */
        p_Var5 = operator_new(0x18);
        iVar2 = *(int *)(param_1 + 4);
        *(int *)(p_Var5 + 0x10) = *(int *)param_1;
        *(int *)(p_Var5 + 0x14) = iVar2;
      }
      else {
LAB_0040c4f0:
        p_Var4 = *(_Rb_tree_node_base **)(p_Var5 + 4);
        if (p_Var4 == (_Rb_tree_node_base *)0x0) {
          p_Var7 = (_Rb_tree_node *)0x0;
        }
        else if (*(_Rb_tree_node_base **)(p_Var4 + 0xc) == p_Var5) {
          p_Var3 = *(_Rb_tree_node_base **)(p_Var4 + 8);
          *(undefined4 *)(p_Var4 + 0xc) = 0;
          if (p_Var3 != (_Rb_tree_node_base *)0x0) {
            p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 0xc);
            if (*(_Rb_tree_node_base **)(p_Var3 + 0xc) == (_Rb_tree_node_base *)0x0) {
              p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 8);
              if (*(_Rb_tree_node_base **)(p_Var3 + 8) == (_Rb_tree_node_base *)0x0) {
                p_Var4 = p_Var3;
              }
            }
            else {
              do {
                p_Var3 = p_Var4;
                p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 0xc);
              } while (*(_Rb_tree_node_base **)(p_Var3 + 0xc) != (_Rb_tree_node_base *)0x0);
              p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 8);
              if (*(_Rb_tree_node_base **)(p_Var3 + 8) == (_Rb_tree_node_base *)0x0) {
                p_Var4 = p_Var3;
              }
            }
          }
        }
        else {
          *(undefined4 *)(p_Var4 + 8) = 0;
        }
        iVar2 = *(int *)(param_1 + 4);
        *(int *)(p_Var5 + 0x10) = *(int *)param_1;
        *(int *)(p_Var5 + 0x14) = iVar2;
      }
      std::_Rb_tree_insert_and_rebalance(bVar8,p_Var5,p_Var6,p_Var1);
      *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
    }
    param_1 = param_1 + 8;
    if (param_2 == param_1) goto LAB_0040c5a4;
    iVar2 = *(int *)(this + 0x14);
    p_Var5 = p_Var4;
  } while( true );
}



// === _M_assign_unique<std::pair<AIDetectState_const,bool>const*> @ 0040c73c ===

/* void std::_Rb_tree<AIDetectState, std::pair<AIDetectState const, bool>,
   std::_Select1st<std::pair<AIDetectState const, bool> >, std::less<AIDetectState>,
   std::allocator<std::pair<AIDetectState const, bool> > >::_M_assign_unique<std::pair<AIDetectState
   const, bool> const*>(std::pair<AIDetectState const, bool> const*, std::pair<AIDetectState const,
   bool> const*) */

void __thiscall
std::
_Rb_tree<AIDetectState,std::pair<AIDetectState_const,bool>,std::_Select1st<std::pair<AIDetectState_const,bool>>,std::less<AIDetectState>,std::allocator<std::pair<AIDetectState_const,bool>>>
::_M_assign_unique<std::pair<AIDetectState_const,bool>const*>
          (_Rb_tree<AIDetectState,std::pair<AIDetectState_const,bool>,std::_Select1st<std::pair<AIDetectState_const,bool>>,std::less<AIDetectState>,std::allocator<std::pair<AIDetectState_const,bool>>>
           *this,pair *param_1,pair *param_2)

{
  _Rb_tree_node_base *p_Var1;
  int iVar2;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree_node_base *p_Var4;
  _Rb_tree_node_base *p_Var5;
  _Rb_tree_node_base *p_Var6;
  _Rb_tree_node *p_Var7;
  bool bVar8;
  int local_30;
  _Rb_tree_node_base *local_2c;
  
  p_Var7 = *(_Rb_tree_node **)(this + 8);
  if (p_Var7 == (_Rb_tree_node *)0x0) {
    p_Var5 = (_Rb_tree_node_base *)0x0;
  }
  else {
    p_Var1 = *(_Rb_tree_node_base **)(this + 0x10);
    *(undefined4 *)(p_Var7 + 4) = 0;
    p_Var5 = *(_Rb_tree_node_base **)(p_Var1 + 8);
    if (p_Var5 == (_Rb_tree_node_base *)0x0) {
      p_Var5 = p_Var1;
    }
  }
  p_Var1 = (_Rb_tree_node_base *)(this + 4);
  *(undefined4 *)(this + 8) = 0;
  *(_Rb_tree_node_base **)(this + 0xc) = p_Var1;
  *(_Rb_tree_node_base **)(this + 0x10) = p_Var1;
  *(undefined4 *)(this + 0x14) = 0;
  if (param_1 == param_2) {
LAB_0040c890:
    _M_erase(this,p_Var7);
    return;
  }
  iVar2 = 0;
  do {
    p_Var4 = p_Var5;
    if ((iVar2 == 0) ||
       (p_Var6 = *(_Rb_tree_node_base **)(this + 0x10), *(int *)param_1 <= *(int *)(p_Var6 + 0x10)))
    {
      _M_get_insert_unique_pos((AIDetectState *)&local_30);
      if (local_2c != (_Rb_tree_node_base *)0x0) {
        bVar8 = true;
        p_Var6 = local_2c;
        if (local_30 == 0) goto LAB_0040c7c0;
        if (p_Var5 != (_Rb_tree_node_base *)0x0) goto LAB_0040c7dc;
        goto LAB_0040c86c;
      }
    }
    else {
LAB_0040c7c0:
      bVar8 = true;
      if (p_Var1 != p_Var6) {
        bVar8 = *(int *)param_1 < *(int *)(p_Var6 + 0x10);
      }
      if (p_Var5 == (_Rb_tree_node_base *)0x0) {
LAB_0040c86c:
                    /* try { // try from 0040c86c to 0040c873 has its CatchHandler @ 0040c918 */
        p_Var5 = operator_new(0x18);
        iVar2 = *(int *)(param_1 + 4);
        *(int *)(p_Var5 + 0x10) = *(int *)param_1;
        *(int *)(p_Var5 + 0x14) = iVar2;
      }
      else {
LAB_0040c7dc:
        p_Var4 = *(_Rb_tree_node_base **)(p_Var5 + 4);
        if (p_Var4 == (_Rb_tree_node_base *)0x0) {
          p_Var7 = (_Rb_tree_node *)0x0;
        }
        else if (*(_Rb_tree_node_base **)(p_Var4 + 0xc) == p_Var5) {
          p_Var3 = *(_Rb_tree_node_base **)(p_Var4 + 8);
          *(undefined4 *)(p_Var4 + 0xc) = 0;
          if (p_Var3 != (_Rb_tree_node_base *)0x0) {
            p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 0xc);
            if (*(_Rb_tree_node_base **)(p_Var3 + 0xc) == (_Rb_tree_node_base *)0x0) {
              p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 8);
              if (*(_Rb_tree_node_base **)(p_Var3 + 8) == (_Rb_tree_node_base *)0x0) {
                p_Var4 = p_Var3;
              }
            }
            else {
              do {
                p_Var3 = p_Var4;
                p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 0xc);
              } while (*(_Rb_tree_node_base **)(p_Var3 + 0xc) != (_Rb_tree_node_base *)0x0);
              p_Var4 = *(_Rb_tree_node_base **)(p_Var3 + 8);
              if (*(_Rb_tree_node_base **)(p_Var3 + 8) == (_Rb_tree_node_base *)0x0) {
                p_Var4 = p_Var3;
              }
            }
          }
        }
        else {
          *(undefined4 *)(p_Var4 + 8) = 0;
        }
        iVar2 = *(int *)(param_1 + 4);
        *(int *)(p_Var5 + 0x10) = *(int *)param_1;
        *(int *)(p_Var5 + 0x14) = iVar2;
      }
      std::_Rb_tree_insert_and_rebalance(bVar8,p_Var5,p_Var6,p_Var1);
      *(int *)(this + 0x14) = *(int *)(this + 0x14) + 1;
    }
    param_1 = param_1 + 8;
    if (param_2 == param_1) goto LAB_0040c890;
    iVar2 = *(int *)(this + 0x14);
    p_Var5 = p_Var4;
  } while( true );
}



// === updateAIConfigata @ 00412e00 ===

/* ai_engine_app::updateAIConfigata(std::__cxx11::string const&, std::__cxx11::string const&,
   std::__cxx11::string const&, std::__cxx11::string const&) */

void ai_engine_app::updateAIConfigata
               (string *param_1,string *param_2,string *param_3,string *param_4)

{
  undefined1 *local_208 [2];
  undefined1 auStack_200 [312];
  undefined1 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined1 local_b0;
  undefined1 *local_ac;
  undefined4 local_a8;
  undefined1 local_a4 [16];
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined1 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_68;
  undefined4 local_64;
  undefined1 local_60;
  undefined1 *local_5c;
  undefined4 local_58;
  undefined1 local_54 [16];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  
  local_28 = 0;
  local_208[0] = auStack_200;
  local_74 = 6;
  local_5c = local_54;
  local_c4 = 6;
  local_ac = local_a4;
  local_78 = 0;
  local_70 = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_58 = 0;
  local_54[0] = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_c8 = 0;
  local_c0 = 0;
  local_b8 = 0;
  local_b4 = 0;
  local_b0 = 0;
  local_a8 = 0;
  local_a4[0] = 0;
  local_94 = 0;
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00412ef4 to 00412efb has its CatchHandler @ 004131a8 */
  std::__cxx11::string::_M_construct<char_const*>(local_208,"SystemPath","");
}



// === get_total_time @ 0042087c ===

/* WARNING: Removing unreachable block (ram,0x004208a0) */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* get_total_time() */

int get_total_time(void)

{
  timespec local_10;
  
  clock_gettime(1,&local_10);
  return local_10.tv_sec * 1000 + local_10.tv_nsec / 1000000;
}



// === _M_realloc_insert<std::pair<unsigned_int,unsigned_int>> @ 00426f7c ===

/* void std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int,
   unsigned int> > >::_M_realloc_insert<std::pair<unsigned int, unsigned int>
   >(__gnu_cxx::__normal_iterator<std::pair<unsigned int, unsigned int>*,
   std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int,
   unsigned int> > > >, std::pair<unsigned int, unsigned int>&&) */

void __thiscall
std::
vector<std::pair<unsigned_int,unsigned_int>,std::allocator<std::pair<unsigned_int,unsigned_int>>>::
_M_realloc_insert<std::pair<unsigned_int,unsigned_int>>
          (vector<std::pair<unsigned_int,unsigned_int>,std::allocator<std::pair<unsigned_int,unsigned_int>>>
           *this,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  
  puVar1 = *(undefined4 **)(this + 4);
  puVar5 = *(undefined4 **)this;
  uVar3 = (int)puVar1 - (int)puVar5 >> 3;
  iVar12 = (int)param_2 - (int)puVar5;
  if (uVar3 == 0) {
    uVar6 = 1;
LAB_004270e8:
    uVar10 = uVar6 << 3;
  }
  else {
    uVar6 = uVar3 << 1;
    uVar10 = 0xfffffff8;
    if ((uVar3 <= uVar6) && (uVar6 < 0x20000000)) {
      puVar9 = (undefined4 *)0x8;
      if (uVar6 == 0) {
        iVar11 = 0;
        puVar2 = (undefined4 *)0x0;
        goto LAB_00426ff0;
      }
      goto LAB_004270e8;
    }
  }
  puVar2 = operator_new(uVar10);
  puVar5 = *(undefined4 **)this;
  puVar1 = *(undefined4 **)(this + 4);
  iVar11 = (int)puVar2 + uVar10;
  puVar9 = puVar2 + 2;
LAB_00426ff0:
  puVar4 = (undefined4 *)((int)puVar2 + iVar12);
  if (puVar4 != (undefined4 *)0x0) {
    uVar7 = param_3[1];
    *puVar4 = *param_3;
    puVar4[1] = uVar7;
  }
  puVar4 = puVar5;
  puVar8 = puVar2;
  if (puVar5 != param_2) {
    do {
      if (puVar8 != (undefined4 *)0x0) {
        uVar7 = puVar4[1];
        *puVar8 = *puVar4;
        puVar8[1] = uVar7;
      }
      puVar4 = puVar4 + 2;
      puVar8 = puVar8 + 2;
    } while (puVar4 != param_2);
    puVar9 = (undefined4 *)((int)puVar2 + ((int)param_2 - (int)(puVar5 + 2) & 0xfffffff8U) + 0x10);
  }
  puVar4 = param_2;
  puVar8 = puVar9;
  if (puVar1 != param_2) {
    do {
      if (puVar8 != (undefined4 *)0x0) {
        uVar7 = puVar4[1];
        *puVar8 = *puVar4;
        puVar8[1] = uVar7;
      }
      puVar4 = puVar4 + 2;
      puVar8 = puVar8 + 2;
    } while (puVar4 != puVar1);
    puVar9 = puVar9 + (((uint)((int)puVar4 - (int)(param_2 + 2)) >> 3) + 1) * 2;
  }
  if (puVar5 != (undefined4 *)0x0) {
    operator_delete(puVar5);
  }
  *(undefined4 **)this = puVar2;
  *(undefined4 **)(this + 4) = puVar9;
  *(int *)(this + 8) = iVar11;
  return;
}



// === emplace_back<std::pair<unsigned_int,unsigned_int>> @ 00427114 ===

/* void std::vector<std::pair<unsigned int, unsigned int>, std::allocator<std::pair<unsigned int,
   unsigned int> > >::emplace_back<std::pair<unsigned int, unsigned int> >(std::pair<unsigned int,
   unsigned int>&&) */

void __thiscall
std::
vector<std::pair<unsigned_int,unsigned_int>,std::allocator<std::pair<unsigned_int,unsigned_int>>>::
emplace_back<std::pair<unsigned_int,unsigned_int>>
          (vector<std::pair<unsigned_int,unsigned_int>,std::allocator<std::pair<unsigned_int,unsigned_int>>>
           *this,pair *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  puVar1 = *(undefined4 **)(this + 4);
  if (puVar1 != *(undefined4 **)(this + 8)) {
    if (puVar1 != (undefined4 *)0x0) {
      uVar2 = *(undefined4 *)(param_1 + 4);
      *puVar1 = *(undefined4 *)param_1;
      puVar1[1] = uVar2;
    }
    *(undefined4 **)(this + 4) = puVar1 + 2;
    return;
  }
  _M_realloc_insert<std::pair<unsigned_int,unsigned_int>>(this,puVar1,param_1);
  return;
}



// === _M_realloc_insert<unsigned_int_const&> @ 00428990 ===

/* void std::vector<unsigned int, std::allocator<unsigned int> >::_M_realloc_insert<unsigned int
   const&>(__gnu_cxx::__normal_iterator<unsigned int*, std::vector<unsigned int,
   std::allocator<unsigned int> > >, unsigned int const&) */

void __thiscall
std::vector<unsigned_int,std::allocator<unsigned_int>>::_M_realloc_insert<unsigned_int_const&>
          (vector<unsigned_int,std::allocator<unsigned_int>> *this,void *param_2,undefined4 *param_3
          )

{
  uint uVar1;
  void *__dest;
  undefined4 *puVar2;
  uint uVar3;
  void *__dest_00;
  size_t __n;
  void *__src;
  uint uVar4;
  int iVar5;
  void *pvVar6;
  size_t sVar7;
  
  pvVar6 = *(void **)(this + 4);
  __src = *(void **)this;
  uVar1 = (int)pvVar6 - (int)__src >> 2;
  sVar7 = (int)param_2 - (int)__src;
  if (uVar1 == 0) {
    uVar3 = 1;
LAB_00428aac:
    uVar4 = uVar3 << 2;
  }
  else {
    uVar3 = uVar1 << 1;
    uVar4 = 0xfffffffc;
    if ((uVar1 <= uVar3) && (uVar3 < 0x40000000)) {
      if (uVar3 == 0) {
        iVar5 = 0;
        __dest = (void *)0x0;
        __n = sVar7;
        goto LAB_00428a0c;
      }
      goto LAB_00428aac;
    }
  }
  __dest = operator_new(uVar4);
  __src = *(void **)this;
  pvVar6 = *(void **)(this + 4);
  iVar5 = (int)__dest + uVar4;
  __n = (int)param_2 - (int)__src;
LAB_00428a0c:
  puVar2 = (undefined4 *)((int)__dest + sVar7);
  if (puVar2 != (undefined4 *)0x0) {
    *puVar2 = *param_3;
  }
  if (__src != param_2) {
    memmove(__dest,__src,__n);
  }
  __dest_00 = (void *)((int)__dest + __n + 4);
  if (pvVar6 != param_2) {
    __dest_00 = memcpy(__dest_00,param_2,(int)pvVar6 - (int)param_2);
  }
  if (__src != (void *)0x0) {
    operator_delete(__src);
  }
  *(void **)this = __dest;
  *(int *)(this + 4) = (int)__dest_00 + ((int)pvVar6 - (int)param_2);
  *(int *)(this + 8) = iVar5;
  return;
}



// === updateCurrentSubState @ 00438ab4 ===

/* wsKlipper::updateCurrentSubState(Json::Value const&) */

void __thiscall wsKlipper::updateCurrentSubState(wsKlipper *this,Value *param_1)

{
  int iVar1;
  char *pcVar2;
  wsKlipper *pwVar3;
  undefined4 uVar4;
  undefined8 in_f0_1;
  wsKlipper *local_70;
  undefined4 local_6c;
  undefined4 local_68 [4];
  wsKlipper *local_58;
  undefined4 local_54;
  undefined4 local_50 [4];
  wsKlipper *local_40;
  undefined4 local_3c;
  undefined4 local_38 [5];
  undefined4 local_24;
  
  local_24 = 0;
  iVar1 = pthread_mutex_lock((pthread_mutex_t *)(this + 0xd0));
  if (iVar1 != 0) {
    std::__throw_system_error(iVar1);
    return;
  }
                    /* try { // try from 00438b20 to 00438e77 has its CatchHandler @ 00438f64 */
  iVar1 = Json::Value::isMember((char *)param_1);
  if (iVar1 != 0) {
    pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
    iVar1 = Json::Value::isMember(pcVar2);
    if (iVar1 != 0) {
      pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
      Json::Value::operator[](pcVar2);
      Json::Value::asString_abi_cxx11_();
      pwVar3 = *(wsKlipper **)(this + 0x70);
      if (local_40 == (wsKlipper *)local_38) {
        std::__cxx11::string::_M_assign((string *)(this + 0x70));
        uVar4 = local_38[0];
      }
      else {
        if (pwVar3 == this + 0x78) {
          *(wsKlipper **)(this + 0x70) = local_40;
          *(undefined4 *)(this + 0x74) = local_3c;
          *(undefined4 *)(this + 0x78) = local_38[0];
        }
        else {
          uVar4 = *(undefined4 *)(this + 0x78);
          *(wsKlipper **)(this + 0x70) = local_40;
          *(undefined4 *)(this + 0x74) = local_3c;
          *(undefined4 *)(this + 0x78) = local_38[0];
          local_40 = pwVar3;
          if (pwVar3 != (wsKlipper *)0x0) goto LAB_00438d8c;
        }
        local_40 = (wsKlipper *)local_38;
        uVar4 = local_38[0];
      }
LAB_00438d8c:
      local_38[0] = uVar4;
      local_3c = 0;
      *local_40 = (wsKlipper)0x0;
      if (local_40 != (wsKlipper *)local_38) {
        operator_delete(local_40);
      }
    }
  }
  iVar1 = Json::Value::isMember((char *)param_1);
  if (iVar1 != 0) {
    pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
    iVar1 = Json::Value::isMember(pcVar2);
    if (iVar1 != 0) {
      pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
      Json::Value::operator[](pcVar2);
      uVar4 = Json::Value::asInt();
      *(undefined4 *)(this + 0xb8) = uVar4;
    }
  }
  iVar1 = Json::Value::isMember((char *)param_1);
  if (iVar1 != 0) {
    pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
    iVar1 = Json::Value::isMember(pcVar2);
    if (iVar1 != 0) {
      pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
      Json::Value::operator[](pcVar2);
      Json::Value::asString_abi_cxx11_();
      pwVar3 = *(wsKlipper **)(this + 0x88);
      if (local_58 == (wsKlipper *)local_50) {
        std::__cxx11::string::_M_assign((string *)(this + 0x88));
        uVar4 = local_50[0];
      }
      else {
        if (pwVar3 == this + 0x90) {
          *(wsKlipper **)(this + 0x88) = local_58;
          *(undefined4 *)(this + 0x8c) = local_54;
          *(undefined4 *)(this + 0x90) = local_50[0];
        }
        else {
          uVar4 = *(undefined4 *)(this + 0x90);
          *(wsKlipper **)(this + 0x88) = local_58;
          *(undefined4 *)(this + 0x8c) = local_54;
          *(undefined4 *)(this + 0x90) = local_50[0];
          local_58 = pwVar3;
          if (pwVar3 != (wsKlipper *)0x0) goto LAB_00438e34;
        }
        local_58 = (wsKlipper *)local_50;
        uVar4 = local_50[0];
      }
LAB_00438e34:
      local_50[0] = uVar4;
      local_54 = 0;
      *local_58 = (wsKlipper)0x0;
      if (local_58 != (wsKlipper *)local_50) {
        operator_delete(local_58);
      }
    }
  }
  iVar1 = Json::Value::isMember((char *)param_1);
  if (iVar1 == 0) goto LAB_00438c00;
  pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
  iVar1 = Json::Value::isMember(pcVar2);
  if (iVar1 == 0) goto LAB_00438c00;
  pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
  Json::Value::operator[](pcVar2);
  Json::Value::asString_abi_cxx11_();
  pwVar3 = *(wsKlipper **)(this + 0xa0);
  if (local_70 == (wsKlipper *)local_68) {
    std::__cxx11::string::_M_assign((string *)(this + 0xa0));
    uVar4 = local_68[0];
  }
  else {
    if (pwVar3 == this + 0xa8) {
      *(wsKlipper **)(this + 0xa0) = local_70;
      *(undefined4 *)(this + 0xa4) = local_6c;
      *(undefined4 *)(this + 0xa8) = local_68[0];
    }
    else {
      uVar4 = *(undefined4 *)(this + 0xa8);
      *(wsKlipper **)(this + 0xa0) = local_70;
      *(undefined4 *)(this + 0xa4) = local_6c;
      *(undefined4 *)(this + 0xa8) = local_68[0];
      local_70 = pwVar3;
      if (pwVar3 != (wsKlipper *)0x0) goto LAB_00438eb8;
    }
    local_70 = (wsKlipper *)local_68;
    uVar4 = local_68[0];
  }
LAB_00438eb8:
  local_68[0] = uVar4;
  *local_70 = (wsKlipper)0x0;
  if (local_70 != (wsKlipper *)local_68) {
    operator_delete(local_70);
  }
LAB_00438c00:
  iVar1 = Json::Value::isMember((char *)param_1);
  if (iVar1 != 0) {
    pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
    iVar1 = Json::Value::isMember(pcVar2);
    if (iVar1 != 0) {
      pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
      Json::Value::operator[](pcVar2);
      local_24 = 0;
      Json::Value::asDouble();
      local_24 = 0;
      *(undefined8 *)(this + 0xc0) = in_f0_1;
    }
  }
  iVar1 = Json::Value::isMember((char *)param_1);
  if (iVar1 != 0) {
    pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
    iVar1 = Json::Value::isMember(pcVar2);
    if (iVar1 != 0) {
      pcVar2 = (char *)Json::Value::operator[]((char *)param_1);
      Json::Value::operator[](pcVar2);
      local_24 = 0;
      Json::Value::asDouble();
      local_24 = 0;
      *(undefined8 *)(this + 200) = in_f0_1;
    }
  }
  pthread_mutex_unlock((pthread_mutex_t *)(this + 0xd0));
  return;
}



// === unlock @ 0043cb2c ===

/* std::unique_lock<std::mutex>::unlock() */

void __thiscall std::unique_lock<std::mutex>::unlock(unique_lock<std::mutex> *this)

{
  if (this[4] == (unique_lock<std::mutex>)0x0) {
    std::__throw_system_error(1);
    return;
  }
  if (*(pthread_mutex_t **)this != (pthread_mutex_t *)0x0) {
    pthread_mutex_unlock(*(pthread_mutex_t **)this);
    this[4] = (unique_lock<std::mutex>)0x0;
  }
  return;
}



// === get_authorize_key @ 0043db04 ===

/* ObbrecLidar::get_authorize_key(std::vector<unsigned char, std::allocator<unsigned char> >&) */

undefined4 __thiscall ObbrecLidar::get_authorize_key(ObbrecLidar *this,vector *param_1)

{
  byte bVar1;
  uint uVar2;
  void *__dest;
  char *pcVar3;
  char *pcVar4;
  EVP_PKEY_CTX *pEVar5;
  int iVar6;
  ostream *poVar7;
  void *__dest_00;
  undefined4 *puVar8;
  uint uVar9;
  uint *puVar10;
  uint *puVar11;
  size_t sVar12;
  int iVar13;
  void *__src;
  undefined *puVar14;
  byte *pbVar15;
  undefined4 uVar16;
  int *piVar17;
  void *__src_00;
  undefined *local_310 [4];
  uint local_300;
  undefined4 local_2fc;
  uint local_2f8;
  undefined4 local_2f4;
  locale alStack_2f0 [4];
  undefined4 local_2ec;
  undefined1 *local_2e8;
  undefined4 local_2e4;
  undefined1 local_2e0 [16];
  undefined *local_2d0 [28];
  undefined4 local_260;
  undefined1 local_25c;
  undefined1 local_25b;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined *local_248 [3];
  uint local_23c [5];
  locale alStack_228 [4];
  undefined4 local_224;
  undefined1 *local_220;
  undefined4 local_21c;
  undefined1 local_218 [16];
  undefined *local_208 [13];
  byte abStack_1d4 [8];
  undefined4 auStack_1cc [13];
  undefined4 local_198;
  undefined1 local_194;
  undefined1 local_193;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  SHA256_CTX local_180;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  uint *local_f0;
  size_t local_ec;
  uint local_e8 [4];
  uint *local_d8;
  size_t local_d4;
  uint local_d0 [4];
  uint *local_c0;
  uint local_bc;
  uint local_b8 [4];
  uint *local_a8;
  uint local_a4;
  uint local_a0 [4];
  uint *local_90;
  size_t local_8c;
  uint local_88 [4];
  uchar *local_78;
  size_t local_74;
  uchar auStack_70 [16];
  byte local_60 [16];
  undefined4 local_50;
  undefined4 local_4c;
  undefined *local_48;
  undefined *local_44;
  undefined4 local_40;
  code *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 *local_30;
  
  if ((uint)(*(int *)(this + 8) - *(int *)(this + 4)) < 0x11) {
    Log::Error("/var/jenkins_home/workspace/IngenicX2600-security-build/solus_prime/creality/obbrecLidar/obbrecLidar.cpp"
               ,0xce,"get_authorize_key failed, receive data size is not 17.");
    return 0xfffffff8;
  }
  __dest = operator_new(*(int *)(this + 8) - *(int *)(this + 4));
  sVar12 = *(int *)(this + 8) - (int)*(void **)(this + 4);
  if (sVar12 != 0) {
    memmove(__dest,*(void **)(this + 4),sVar12);
  }
  pcVar3 = (char *)((int)__dest + 7);
  do {
    pcVar4 = pcVar3 + 1;
    *pcVar3 = -*pcVar3;
    pcVar3 = pcVar4;
  } while ((char *)((int)__dest + 0xf) != pcVar4);
  local_34 = *(undefined4 *)((int)__dest + 7);
  local_78 = auStack_70;
                    /* try { // try from 0043db98 to 0043db9f has its CatchHandler @ 0043e444 */
  std::__cxx11::string::_M_construct<char_const*>(&local_78,(int)__dest + 0xb);
  local_60[0] = 0;
  local_60[1] = 0;
  local_60[2] = 0;
  local_60[3] = 0;
  local_60[4] = 0;
  local_60[5] = 0;
  local_60[6] = 0;
  local_60[7] = 0;
  local_60[8] = 0;
  local_60[9] = 0;
  local_60[10] = 0;
  local_60[0xb] = 0;
  local_60[0xc] = 0;
  local_60[0xd] = 0;
  local_60[0xe] = 0;
  local_60[0xf] = 0;
                    /* try { // try from 0043dbb8 to 0043dbbf has its CatchHandler @ 0043e43c */
  MD5(local_78,local_74,local_60);
  std::ios_base::ios_base((ios_base *)local_208);
  uVar16 = std::__cxx11::ostringstream::VTT._4_4_;
  local_194 = 0;
  local_30 = std::__cxx11::ostringstream::VTT;
  pEVar5 = (EVP_PKEY_CTX *)
           ((int)local_248 + *(int *)(std::__cxx11::ostringstream::VTT._4_4_ + -0xc));
  local_208[0] = (undefined *)0x4815b8;
  local_198 = 0;
  local_193 = 0;
  local_190 = 0;
  local_18c = 0;
  local_188 = 0;
  local_184 = 0;
  local_248[0] = (undefined *)std::__cxx11::ostringstream::VTT._4_4_;
  *(undefined4 *)pEVar5 = std::__cxx11::ostringstream::VTT._8_4_;
  local_38 = std::__cxx11::ostringstream::VTT._8_4_;
                    /* try { // try from 0043dc24 to 0043dc2b has its CatchHandler @ 0043e4f4 */
  local_50 = 0x4815b8;
  std::ios::init(pEVar5);
  local_44 = &DAT_004813a8;
  local_4c = 0x481534;
  local_208[0] = &DAT_004813a8;
  local_248[1] = (undefined *)0x481534;
  local_48 = &DAT_00481394;
  local_248[0] = &DAT_00481394;
  local_248[2] = (undefined *)0x0;
  local_23c[0] = 0;
  local_23c[1] = 0;
  local_23c[2] = 0;
  local_23c[3] = 0;
  local_23c[4] = 0;
  std::locale::locale(alStack_228);
  local_40 = 0x481324;
  local_248[1] = (undefined *)0x481324;
  local_224 = 0x10;
  local_220 = local_218;
  local_21c = 0;
                    /* try { // try from 0043dca8 to 0043dcaf has its CatchHandler @ 0043e490 */
  local_218[0] = 0;
  std::ios::init((EVP_PKEY_CTX *)local_208);
  pbVar15 = local_60;
  local_3c = std::ctype<char>::do_widen;
  do {
    iVar6 = *(int *)(local_248[0] + -0xc);
    *(undefined4 *)((int)local_248 + iVar6 + 8) = 2;
    iVar13 = *(int *)(local_248[0] + -0xc);
    uVar9 = (uint)abStack_1d4[iVar13 + 1];
    *(uint *)((int)local_23c + iVar6) = *(uint *)((int)local_23c + iVar6) & 0xffffffb5 | 8;
    if (uVar9 == 0) {
      piVar17 = *(int **)((int)auStack_1cc + iVar13);
      if (piVar17 == (int *)0x0) {
                    /* try { // try from 0043e3dc to 0043e3e3 has its CatchHandler @ 0043e3e4 */
        std::__throw_bad_cast();
                    /* catch() { ... } // from try @ 0043dcdc with catch @ 0043e3e4
                       catch() { ... } // from try @ 0043e3dc with catch @ 0043e3e4 */
        std::__cxx11::ostringstream::~ostringstream((ostringstream *)local_248);
        if (local_78 != auStack_70) {
          operator_delete(local_78);
        }
        operator_delete(__dest);
                    /* WARNING: Subroutine does not return */
        _Unwind_Resume(uVar9);
      }
      if ((char)piVar17[7] == '\0') {
        std::ctype<char>::_M_widen_init();
        if (*(code **)(*piVar17 + 0x18) != local_3c) {
          (**(code **)(*piVar17 + 0x18))(piVar17,0x20);
          abStack_1d4[iVar13 + 1] = 1;
          goto LAB_0043dcd0;
        }
      }
      abStack_1d4[iVar13 + 1] = 1;
    }
LAB_0043dcd0:
    bVar1 = *pbVar15;
                    /* try { // try from 0043dcdc to 0043dd6b has its CatchHandler @ 0043e3e4 */
    abStack_1d4[iVar13] = 0x30;
    std::ostream::operator<<((ostream *)local_248,(uint)bVar1);
    pbVar15 = pbVar15 + 1;
  } while (pbVar15 != (byte *)&local_50);
  std::ios_base::ios_base((ios_base *)local_2d0);
  local_25c = 0;
  local_260 = 0;
  pEVar5 = (EVP_PKEY_CTX *)((int)local_310 + *(int *)(uVar16 + -0xc));
  local_25b = 0;
  local_258 = 0;
  local_2d0[0] = (undefined *)local_50;
  local_254 = 0;
  local_250 = 0;
  local_24c = 0;
  local_310[0] = (undefined *)uVar16;
                    /* try { // try from 0043ddc0 to 0043ddc7 has its CatchHandler @ 0043e488 */
  *(undefined4 *)pEVar5 = local_38;
  std::ios::init(pEVar5);
  local_310[2] = (undefined *)0x0;
  local_310[0] = local_48;
  local_310[3] = (undefined *)0x0;
  local_300 = 0;
  local_2d0[0] = local_44;
  local_2fc = 0;
  local_2f8 = 0;
  local_310[1] = (undefined *)local_4c;
  local_2f4 = 0;
  std::locale::locale(alStack_2f0);
  local_310[1] = (undefined *)local_40;
  local_2ec = 0x10;
  local_2e4 = 0;
                    /* try { // try from 0043de24 to 0043de2b has its CatchHandler @ 0043e44c */
  local_2e0[0] = 0;
  local_2e8 = local_2e0;
  std::ios::init((EVP_PKEY_CTX *)local_2d0);
                    /* try { // try from 0043de30 to 0043de37 has its CatchHandler @ 0043e4e4 */
  poVar7 = std::ostream::_M_insert<unsigned_long>((ulong)local_310);
  puVar11 = local_180.h + 2;
  local_180.h[1] = 0;
  local_180.h[2] = local_180.h[2] & 0xffffff00;
  local_180.h[0] = (uint)puVar11;
  if (local_23c[3] == 0) {
                    /* try { // try from 0043e2bc to 0043e2c3 has its CatchHandler @ 0043e418 */
    std::__cxx11::string::_M_assign((string *)&local_180);
  }
  else if (local_23c[1] < local_23c[3]) {
    local_c0 = local_b8;
                    /* try { // try from 0043e12c to 0043e133 has its CatchHandler @ 0043e418 */
    std::__cxx11::string::_M_construct<char_const*>(&local_c0,local_23c[2],local_23c[3]);
    uVar2 = local_180.h[2];
    uVar9 = local_180.h[0];
    if (local_c0 == local_b8) {
      std::__cxx11::string::_M_assign((string *)&local_180);
    }
    else {
      if ((uint *)local_180.h[0] != puVar11) {
        local_180.h[0] = (uint)local_c0;
        local_180.h[1] = local_bc;
        local_180.h[2] = local_b8[0];
        if ((uint *)uVar9 != (uint *)0x0) {
          local_c0 = (uint *)uVar9;
          local_b8[0] = uVar2;
          goto LAB_0043e168;
        }
      }
      local_180.h[2] = local_b8[0];
      local_180.h[1] = local_bc;
      local_180.h[0] = (uint)local_c0;
      local_c0 = local_b8;
    }
LAB_0043e168:
    local_bc = 0;
    *(undefined1 *)local_c0 = 0;
    puVar10 = local_c0;
    if (local_c0 != local_b8) {
LAB_0043debc:
      operator_delete(puVar10);
    }
  }
  else {
    local_a8 = local_a0;
                    /* try { // try from 0043de6c to 0043de73 has its CatchHandler @ 0043e418 */
    std::__cxx11::string::_M_construct<char_const*>(&local_a8,local_23c[2]);
    uVar2 = local_180.h[2];
    uVar9 = local_180.h[0];
    if (local_a8 == local_a0) {
      std::__cxx11::string::_M_assign((string *)&local_180);
    }
    else {
      if ((uint *)local_180.h[0] != puVar11) {
        local_180.h[0] = (uint)local_a8;
        local_180.h[1] = local_a4;
        local_180.h[2] = local_a0[0];
        if ((uint *)uVar9 != (uint *)0x0) {
          local_a8 = (uint *)uVar9;
          local_a0[0] = uVar2;
          goto LAB_0043dea8;
        }
      }
      local_180.h[2] = local_a0[0];
      local_180.h[1] = local_a4;
      local_180.h[0] = (uint)local_a8;
      local_a8 = local_a0;
    }
LAB_0043dea8:
    local_a4 = 0;
    *(undefined1 *)local_a8 = 0;
    puVar10 = local_a8;
    if (local_a8 != local_a0) goto LAB_0043debc;
  }
                    /* try { // try from 0043decc to 0043ded3 has its CatchHandler @ 0043e4dc */
  std::__ostream_insert<char,std::char_traits<char>>(poVar7,(char *)local_180.h[0],local_180.h[1]);
  if ((uint *)local_180.h[0] != puVar11) {
    operator_delete((void *)local_180.h[0]);
  }
  local_8c = 0;
  local_88[0] = local_88[0] & 0xffffff00;
  local_90 = local_88;
  if (local_2f8 == 0) {
                    /* try { // try from 0043e2a8 to 0043e2af has its CatchHandler @ 0043e4ec */
    std::__cxx11::string::_M_assign((string *)&local_90);
    goto LAB_0043df78;
  }
  if (local_300 < local_2f8) {
    local_f0 = local_e8;
                    /* try { // try from 0043df1c to 0043df23 has its CatchHandler @ 0043e4ec */
    std::__cxx11::string::_M_construct<char_const*>(&local_f0,local_2fc,local_2f8);
    uVar9 = local_88[0];
    puVar11 = local_90;
    if (local_f0 == local_e8) {
      std::__cxx11::string::_M_assign((string *)&local_90);
    }
    else {
      if (local_90 != local_88) {
        local_90 = local_f0;
        local_8c = local_ec;
        local_88[0] = local_e8[0];
        if (puVar11 != (uint *)0x0) {
          local_f0 = puVar11;
          local_e8[0] = uVar9;
          goto LAB_0043df58;
        }
      }
      local_88[0] = local_e8[0];
      local_8c = local_ec;
      local_90 = local_f0;
      local_f0 = local_e8;
    }
LAB_0043df58:
    local_ec = 0;
    *(undefined1 *)local_f0 = 0;
    puVar11 = local_f0;
    if (local_f0 == local_e8) goto LAB_0043df78;
  }
  else {
    local_d8 = local_d0;
                    /* try { // try from 0043e19c to 0043e1a3 has its CatchHandler @ 0043e4ec */
    std::__cxx11::string::_M_construct<char_const*>(&local_d8,local_2fc);
    uVar9 = local_88[0];
    puVar11 = local_90;
    if (local_d8 == local_d0) {
      std::__cxx11::string::_M_assign((string *)&local_90);
    }
    else {
      if (local_90 != local_88) {
        local_90 = local_d8;
        local_8c = local_d4;
        local_88[0] = local_d0[0];
        if (puVar11 != (uint *)0x0) {
          local_d8 = puVar11;
          local_d0[0] = uVar9;
          goto LAB_0043e1d8;
        }
      }
      local_88[0] = local_d0[0];
      local_8c = local_d4;
      local_90 = local_d8;
      local_d8 = local_d0;
    }
LAB_0043e1d8:
    local_d4 = 0;
    *(undefined1 *)local_d8 = 0;
    puVar11 = local_d8;
    if (local_d8 == local_d0) goto LAB_0043df78;
  }
  operator_delete(puVar11);
LAB_0043df78:
  local_110 = 0;
  local_10c = 0;
  local_108 = 0;
  local_104 = 0;
  local_100 = 0;
  local_fc = 0;
  local_f8 = 0;
                    /* try { // try from 0043df94 to 0043dfb7 has its CatchHandler @ 0043e4c8 */
  local_f4 = 0;
  SHA256_Init(&local_180);
  SHA256_Update(&local_180,local_90,local_8c);
  SHA256_Final((uchar *)&local_110,&local_180);
  __src = *(void **)param_1;
  *(void **)(param_1 + 4) = __src;
  if ((uint)(*(int *)(param_1 + 8) - (int)__src) < 0x20) {
                    /* try { // try from 0043e1f4 to 0043e1fb has its CatchHandler @ 0043e4c8 */
    __dest_00 = operator_new(0x20);
    __src_00 = *(void **)param_1;
    sVar12 = (int)__src - (int)__src_00;
    if (sVar12 != 0) {
      memmove(__dest_00,__src_00,sVar12);
    }
    puVar8 = (undefined4 *)((int)__dest_00 + sVar12);
    *puVar8 = local_110;
    puVar8[1] = local_10c;
    puVar8[2] = local_108;
    puVar8[3] = local_104;
    puVar8[4] = local_100;
    puVar8[5] = local_fc;
    iVar6 = *(int *)(param_1 + 4);
    puVar8[6] = local_f8;
    sVar12 = iVar6 - (int)__src;
    puVar8[7] = local_f4;
    puVar8 = puVar8 + 8;
    if (sVar12 != 0) {
      puVar8 = memcpy(puVar8,__src,sVar12);
    }
    if (__src_00 != (void *)0x0) {
      operator_delete(__src_00);
    }
    *(void **)param_1 = __dest_00;
    *(size_t *)(param_1 + 4) = (int)puVar8 + sVar12;
    *(int *)(param_1 + 8) = (int)__dest_00 + 0x20;
  }
  else {
    memmove(__src,&local_110,0x20);
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 0x20;
  }
  if (local_90 != local_88) {
    operator_delete(local_90);
  }
  local_310[0] = local_48;
  local_2d0[0] = local_44;
  local_310[1] = (undefined *)local_40;
  if (local_2e8 != local_2e0) {
    operator_delete(local_2e8);
  }
  local_310[1] = (undefined *)local_4c;
  std::locale::~locale(alStack_2f0);
  puVar14 = *(undefined **)(local_30 + 4);
  uVar16 = *(undefined4 *)(local_30 + 8);
  local_310[0] = puVar14;
  *(undefined4 *)((int)local_310 + *(int *)(puVar14 + -0xc)) = uVar16;
  local_2d0[0] = (undefined *)local_50;
  std::ios_base::~ios_base((ios_base *)local_2d0);
  local_248[0] = local_48;
  local_208[0] = local_44;
  local_248[1] = (undefined *)local_40;
  if (local_220 != local_218) {
    operator_delete(local_220);
  }
  local_248[1] = (undefined *)local_4c;
  std::locale::~locale(alStack_228);
  local_248[0] = puVar14;
  *(undefined4 *)((int)local_248 + *(int *)(puVar14 + -0xc)) = uVar16;
  local_208[0] = (undefined *)local_50;
  std::ios_base::~ios_base((ios_base *)local_208);
  if (local_78 != auStack_70) {
    operator_delete(local_78);
  }
  operator_delete(__dest);
  return 0;
}



// === _M_range_insert<__gnu_cxx::__normal_iterator<unsigned_char*,std::vector<unsigned_char,std::allocator<unsigned_char>>>> @ 0043f740 ===

/* void std::vector<unsigned char, std::allocator<unsigned char>
   >::_M_range_insert<__gnu_cxx::__normal_iterator<unsigned char*, std::vector<unsigned char,
   std::allocator<unsigned char> > > >(__gnu_cxx::__normal_iterator<unsigned char*,
   std::vector<unsigned char, std::allocator<unsigned char> > >,
   __gnu_cxx::__normal_iterator<unsigned char*, std::vector<unsigned char, std::allocator<unsigned
   char> > >, __gnu_cxx::__normal_iterator<unsigned char*, std::vector<unsigned char,
   std::allocator<unsigned char> > >, std::forward_iterator_tag) */

void std::vector<unsigned_char,std::allocator<unsigned_char>>::
     _M_range_insert<__gnu_cxx::__normal_iterator<unsigned_char*,std::vector<unsigned_char,std::allocator<unsigned_char>>>>
               (int *param_1,void *param_2,void *param_3,void *param_4)

{
  void *pvVar1;
  size_t __n;
  uint uVar2;
  size_t sVar3;
  uint uVar4;
  int iVar5;
  size_t __n_00;
  void *pvVar6;
  void *__dest;
  
  if (param_4 == param_3) {
    return;
  }
  pvVar1 = (void *)param_1[1];
  __n = (int)param_4 - (int)param_3;
  if (__n <= (uint)(param_1[2] - (int)pvVar1)) {
    uVar2 = (int)pvVar1 - (int)param_2;
    pvVar6 = param_2;
    if (__n < uVar2) {
      sVar3 = (int)((int)pvVar1 - __n) - (int)param_2;
      if (__n == 0) {
        if (sVar3 == 0) {
          return;
        }
        pvVar6 = (void *)((int)pvVar1 - sVar3);
        param_3 = param_2;
        __n = sVar3;
      }
      else {
        memmove(pvVar1,(void *)((int)pvVar1 - __n),__n);
        param_1[1] = param_1[1] + __n;
        if (sVar3 != 0) {
          memmove((void *)((int)pvVar1 - sVar3),param_2,sVar3);
        }
      }
    }
    else {
      sVar3 = (int)param_4 - (int)((int)param_3 + uVar2);
      if (sVar3 != 0) {
        memmove(pvVar1,(void *)((int)param_3 + uVar2),sVar3);
        pvVar1 = (void *)param_1[1];
      }
      pvVar1 = (void *)((int)pvVar1 + (__n - uVar2));
      param_1[1] = (int)pvVar1;
      if (uVar2 == 0) {
        return;
      }
      memmove(pvVar1,param_2,uVar2);
      param_1[1] = param_1[1] + uVar2;
      __n = uVar2;
    }
    memmove(pvVar6,param_3,__n);
    return;
  }
  pvVar6 = (void *)*param_1;
  uVar2 = (int)pvVar1 - (int)pvVar6;
  if (~uVar2 < __n) {
    std::__throw_length_error("vector::_M_range_insert");
    return;
  }
  uVar4 = uVar2;
  if (uVar2 <= __n) {
    uVar4 = __n;
  }
  uVar4 = uVar4 + uVar2;
  if (uVar4 < uVar2) {
    uVar4 = 0xffffffff;
  }
  else {
    iVar5 = 0;
    __dest = (void *)0x0;
    if (uVar4 == 0) goto LAB_0043f828;
  }
  __dest = operator_new(uVar4);
  pvVar6 = (void *)*param_1;
  pvVar1 = (void *)param_1[1];
  iVar5 = (int)__dest + uVar4;
LAB_0043f828:
  sVar3 = (int)param_2 - (int)pvVar6;
  if (sVar3 != 0) {
    memmove(__dest,pvVar6,sVar3);
  }
  if (__n != 0) {
    memcpy((void *)((int)__dest + sVar3),param_3,__n);
  }
  __n_00 = (int)pvVar1 - (int)param_2;
  pvVar1 = (void *)((int)((int)__dest + sVar3) + __n);
  if (__n_00 != 0) {
    memcpy(pvVar1,param_2,__n_00);
  }
  if (pvVar6 != (void *)0x0) {
    operator_delete(pvVar6);
  }
  *param_1 = (int)__dest;
  param_1[1] = (int)pvVar1 + __n_00;
  param_1[2] = iVar5;
  return;
}



// === lws_ring_update_oldest_tail @ 0046f950 ===

void lws_ring_update_oldest_tail(void)

{
  (*(code *)PTR_lws_ring_update_oldest_tail_00480964)();
  return;
}



// === updateFlowPAFile @ 0046fbc0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AI_Engine::updateFlowPAFile(FlowParameters *param_1,string *param_2,string *param_3)

{
  (*(code *)PTR_updateFlowPAFile_00480a00)();
  return;
}



// === _M_insert<unsigned_long> @ 0046fc50 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ostream * std::ostream::_M_insert<unsigned_long>(ulong param_1)

{
  ostream *poVar1;
  
  poVar1 = (ostream *)(*(code *)PTR__M_insert<unsigned_long>_00480a24)();
  return poVar1;
}



// === __pthread_key_create @ 0046fd00 ===

void __pthread_key_create(void)

{
                    /* WARNING: Could not recover jumptable at 0x0046fd08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR___pthread_key_create_00480a50)();
  return;
}



// === update @ 0046fd90 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void JsonValue::update(string *param_1)

{
  (*(code *)PTR_update_00480a74)();
  return;
}



// === updateFlowEmFile @ 0046fe20 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AI_Engine::updateFlowEmFile(FlowEmParameters *param_1,string *param_2,string *param_3)

{
  (*(code *)PTR_updateFlowEmFile_00480a98)();
  return;
}



// === pthread_mutex_unlock @ 004702c0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_mutex_unlock_00480bc0)();
  return iVar1;
}



// === signal @ 00470420 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;
  
  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_00480c18)();
  return p_Var1;
}



// === SHA256_Update @ 00470510 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SHA256_Update(SHA256_CTX *c,void *data,size_t len)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SHA256_Update_00480c54)();
  return iVar1;
}



// === _M_assign @ 004706d0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__cxx11::string::_M_assign(string *param_1)

{
  (*(code *)PTR__M_assign_00480cc4)();
  return;
}



// === lws_ring_update_oldest_tail @ 004820e8 ===

/* WARNING: Control flow encountered bad instruction data */

void lws_ring_update_oldest_tail(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === updateFlowPAFile @ 00482180 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AI_Engine::updateFlowPAFile(FlowParameters *param_1,string *param_2,string *param_3)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === _M_insert<unsigned_long> @ 004821a4 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ostream * std::ostream::_M_insert<unsigned_long>(ulong param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* _ZNSo9_M_insertImEERSoT_@@GLIBCXX_3.4.9 */
  halt_baddata();
}



// === update @ 004821ec ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void JsonValue::update(string *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === updateFlowEmFile @ 00482210 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AI_Engine::updateFlowEmFile(FlowEmParameters *param_1,string *param_2,string *param_3)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === pthread_mutex_unlock @ 00482324 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_mutex_unlock@@GLIBC_2.0 */
  halt_baddata();
}



// === signal @ 00482378 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* signal@@GLIBC_2.0 */
  halt_baddata();
}



// === SHA256_Update @ 004823b8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SHA256_Update(SHA256_CTX *c,void *data,size_t len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SHA256_Update@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === _M_assign @ 00482424 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__cxx11::string::_M_assign(string *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_assignERKS4_@@GLIBCXX_3.4.21
                        */
  halt_baddata();
}


