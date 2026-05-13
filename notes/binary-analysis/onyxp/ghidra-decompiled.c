
// === cb_dtls_verify @ 00403930 ===

bool cb_dtls_verify(undefined4 param_1,X509_STORE_CTX *param_2)

{
  int iVar1;
  
  iVar1 = X509_STORE_CTX_get_error(param_2);
  return iVar1 != 10;
}



// === generate_self_certificate @ 00403954 ===

void generate_self_certificate(int param_1)

{
  EVP_PKEY *pEVar1;
  BIGNUM *a;
  int iVar2;
  RSA *rsa;
  X509 *pXVar3;
  ASN1_TIME *pAVar4;
  X509_NAME *name;
  EVP_MD *md;
  
  pEVar1 = EVP_PKEY_new();
  *(EVP_PKEY **)(param_1 + 0xc) = pEVar1;
  if (pEVar1 == (EVP_PKEY *)0x0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x3c);
    a = BN_new();
  }
  else {
    a = BN_new();
  }
  if (a == (BIGNUM *)0x0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x41);
  }
  iVar2 = BN_set_word(a,0x10001);
  if (iVar2 == 0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x46);
    rsa = RSA_new();
  }
  else {
    rsa = RSA_new();
  }
  if (rsa == (RSA *)0x0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x4c);
  }
  iVar2 = RSA_generate_key_ex(rsa,0x800,a,(BN_GENCB *)0x0);
  if (iVar2 == 0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x51);
    pEVar1 = *(EVP_PKEY **)(param_1 + 0xc);
  }
  else {
    pEVar1 = *(EVP_PKEY **)(param_1 + 0xc);
  }
  iVar2 = EVP_PKEY_assign(pEVar1,6,rsa);
  if (iVar2 == 0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x56);
    pXVar3 = X509_new();
    *(X509 **)(param_1 + 8) = pXVar3;
  }
  else {
    pXVar3 = X509_new();
    *(X509 **)(param_1 + 8) = pXVar3;
  }
  if (pXVar3 == (X509 *)0x0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x5e);
    pXVar3 = *(X509 **)(param_1 + 8);
  }
  X509_set_version(pXVar3,2);
  pAVar4 = (ASN1_TIME *)X509_getm_notBefore(*(undefined4 *)(param_1 + 8));
  X509_gmtime_adj(pAVar4,-0x1e13380);
  pAVar4 = (ASN1_TIME *)X509_getm_notAfter(*(undefined4 *)(param_1 + 8));
  X509_gmtime_adj(pAVar4,0x1e13380);
  iVar2 = X509_set_pubkey(*(X509 **)(param_1 + 8),*(EVP_PKEY **)(param_1 + 0xc));
  if (iVar2 == 0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x68);
    name = X509_get_subject_name(*(X509 **)(param_1 + 8));
  }
  else {
    name = X509_get_subject_name(*(X509 **)(param_1 + 8));
  }
  if (name == (X509_NAME *)0x0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x6e);
  }
  X509_NAME_add_entry_by_txt(name,"O",0x1001,"Test",-1,-1,0);
  X509_NAME_add_entry_by_txt(name,"CN",0x1001,"Test",-1,-1,0);
  iVar2 = X509_set_issuer_name(*(X509 **)(param_1 + 8),name);
  if (iVar2 == 0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x76);
    pXVar3 = *(X509 **)(param_1 + 8);
  }
  else {
    pXVar3 = *(X509 **)(param_1 + 8);
  }
  pEVar1 = *(EVP_PKEY **)(param_1 + 0xc);
  md = EVP_sha1();
  iVar2 = X509_sign(pXVar3,pEVar1,md);
  if (iVar2 == 0) {
    fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x7b);
  }
  BN_free(a);
  return;
}



// === dtls_transport_init @ 00403d48 ===

undefined4 dtls_transport_init(undefined4 *param_1,undefined4 param_2)

{
  SSL_METHOD *meth;
  SSL_CTX *ctx;
  int iVar1;
  EVP_MD *type;
  SSL *pSVar2;
  BIO_METHOD *type_00;
  BIO *bp;
  EC_KEY *key;
  undefined4 uVar3;
  uchar *puVar4;
  X509 *data;
  uchar *puVar5;
  undefined4 *puVar6;
  uchar local_68 [64];
  uchar *local_28 [3];
  
  meth = (SSL_METHOD *)DTLS_method();
  ctx = SSL_CTX_new(meth);
  param_1[1] = ctx;
  SSL_CTX_set_verify(ctx,3,cb_dtls_verify);
  SSL_CTX_set_tlsext_use_srtp((SSL_CTX *)param_1[1],"SRTP_AES128_CM_SHA1_80");
  generate_self_certificate(param_1);
  iVar1 = SSL_CTX_use_certificate((SSL_CTX *)param_1[1],(X509 *)param_1[2]);
  if (iVar1 == 0) {
    fprintf(stdout,"[%s %s:%d] use certificate failed\n","ERROR","src/dtls_transport.c",0x8c);
    uVar3 = 0xffffffff;
  }
  else {
    iVar1 = SSL_CTX_use_PrivateKey((SSL_CTX *)param_1[1],(EVP_PKEY *)param_1[3]);
    if (iVar1 == 0) {
      fprintf(stdout,"[%s %s:%d] use private key failed\n","ERROR","src/dtls_transport.c",0x92);
      uVar3 = 0xffffffff;
    }
    else {
      iVar1 = SSL_CTX_check_private_key((SSL_CTX *)param_1[1]);
      if (iVar1 == 0) {
        fprintf(stdout,"[%s %s:%d] check preverify key failed\n","ERROR","src/dtls_transport.c",0x97
               );
        uVar3 = 0xffffffff;
      }
      else {
        SSL_CTX_ctrl((SSL_CTX *)param_1[1],0x29,1,(void *)0x0);
        data = (X509 *)param_1[2];
        type = EVP_sha256();
        iVar1 = X509_digest(data,type,local_68,(uint *)local_28);
        if (iVar1 == 0) {
          fprintf(stdout,"[%s %s:%d] generate fingerprint failed\n","ERROR","src/dtls_transport.c",
                  0xa0);
          uVar3 = 0xffffffff;
        }
        else {
          puVar6 = param_1 + 0x36;
          if (local_28[0] != (uchar *)0x0) {
            puVar5 = local_68;
            iVar1 = 1 - (int)puVar5;
            do {
              g_snprintf(puVar6,4,&DAT_00412660,*puVar5);
              puVar4 = puVar5 + iVar1;
              puVar6 = (undefined4 *)((int)puVar6 + 3);
              puVar5 = puVar5 + 1;
            } while (puVar4 < local_28[0]);
          }
          *(undefined1 *)((int)puVar6 + -1) = 0;
          pSVar2 = SSL_new((SSL_CTX *)param_1[1]);
          *param_1 = pSVar2;
          type_00 = BIO_s_mem();
          bp = BIO_new(type_00);
          param_1[4] = bp;
          param_1[5] = param_2;
          BIO_ctrl(bp,0x82,-1,(void *)0x0);
          SSL_set_bio((SSL *)*param_1,(BIO *)param_1[4],(BIO *)param_1[5]);
          key = EC_KEY_new_by_curve_name(0x19f);
          if (key == (EC_KEY *)0x0) {
            fprintf(stdout,"[%s %s:%d] New ecdh curve by name failed\n","ERROR",
                    "src/dtls_transport.c",0xb7);
            uVar3 = 0xffffffff;
          }
          else {
            SSL_set_options(*param_1,0x2020000);
            SSL_ctrl((SSL *)*param_1,4,0,key);
            EC_KEY_free(key);
            param_1[0x5e] = 0;
            param_1[0x5f] = 0;
            srtp_init();
            uVar3 = 0;
          }
        }
      }
    }
  }
  return uVar3;
}



// === dtls_transport_create @ 00404010 ===

void * dtls_transport_create(undefined4 param_1)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,0x180);
  if (pvVar1 != (void *)0x0) {
    dtls_transport_init(pvVar1,param_1);
  }
  return pvVar1;
}



// === dtls_transport_destroy @ 0040405c ===

void dtls_transport_destroy(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    SSL_CTX_free((SSL_CTX *)param_1[1]);
    SSL_free((SSL *)*param_1);
    X509_free((X509 *)param_1[2]);
    EVP_PKEY_free((EVP_PKEY *)param_1[3]);
    if (param_1[0x34] != 0) {
      srtp_dealloc();
    }
    if (param_1[0x35] != 0) {
      srtp_dealloc();
    }
    free(param_1);
    return;
  }
  return;
}



// === dtls_transport_do_handshake @ 004040dc ===

void dtls_transport_do_handshake(undefined4 *param_1)

{
  SSL_set_accept_state((SSL *)*param_1);
  SSL_do_handshake((SSL *)*param_1);
  param_1[0x5e] = 1;
  return;
}



// === dtls_transport_validate @ 00404118 ===

bool dtls_transport_validate(byte *param_1)

{
  if (param_1 != (byte *)0x0) {
    return *param_1 - 0x13 < 0x2e;
  }
  return false;
}



// === dtls_transport_get_srtp_initialized @ 00404138 ===

undefined4 dtls_transport_get_srtp_initialized(int param_1)

{
  if (param_1 != 0) {
    return *(undefined4 *)(param_1 + 0x17c);
  }
  return 0;
}



// === dtls_transport_incomming_msg @ 00404150 ===

void dtls_transport_incomming_msg(undefined4 *param_1,void *param_2,int param_3)

{
  FILE *__stream;
  int iVar1;
  X509 *data;
  EVP_MD *type;
  ulong uVar2;
  char *pcVar3;
  uchar *puVar4;
  uchar *md;
  uchar **ppuVar5;
  undefined1 auStack_d10 [3000];
  uchar *local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined2 local_12c;
  undefined4 local_12a;
  undefined4 local_126;
  undefined4 local_122;
  undefined2 local_11e;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined2 local_74;
  uchar *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined2 local_34;
  FILE *local_30;
  
  if (param_1[0x5f] == 0) {
    iVar1 = BIO_write((BIO *)param_1[4],param_2,param_3);
    if (param_3 == iVar1) {
      iVar1 = param_1[0x5e];
    }
    else {
      fprintf(stdout,"[%s %s:%d] \n","ERROR","src/dtls_transport.c",0x10f);
      iVar1 = param_1[0x5e];
    }
    if (iVar1 != 0) {
      memset(auStack_d10,0,3000);
      iVar1 = SSL_read((SSL *)*param_1,auStack_d10,3000);
      if ((iVar1 < 0) && (iVar1 = SSL_get_error((SSL *)*param_1,iVar1), iVar1 == 1)) {
        uVar2 = ERR_get_error();
        ERR_error_string_n(uVar2,(char *)&local_158,200);
        fprintf(stdout,"[%s %s:%d] %s\n","ERROR","src/dtls_transport.c",0x122,&local_158);
      }
      iVar1 = SSL_is_init_finished(*param_1);
      if (iVar1 != 0) {
        data = SSL_get_peer_certificate((SSL *)*param_1);
        __stream = stdout;
        if (data == (X509 *)0x0) {
          uVar2 = ERR_get_error();
          pcVar3 = ERR_reason_error_string(uVar2);
          fprintf(__stream,"[%s %s:%d] %s\n","ERROR","src/dtls_transport.c",0x12e,pcVar3);
        }
        else {
          type = EVP_sha256();
          md = (uchar *)&local_90;
          X509_digest(data,type,md,(uint *)&local_50);
          X509_free(data);
          ppuVar5 = &local_158;
          if (local_50 != (uchar *)0x0) {
            iVar1 = 1 - (int)md;
            do {
              g_snprintf(ppuVar5,4,&DAT_00412660,*md);
              puVar4 = md + iVar1;
              ppuVar5 = (uchar **)((int)ppuVar5 + 3);
              md = md + 1;
            } while (puVar4 < local_50);
          }
          local_30 = stdout;
          *(undefined1 *)((int)ppuVar5 + -1) = 0;
          fprintf(stdout,"[%s %s:%d] Remote fingerprint %s\n",&DAT_004126a4,"src/dtls_transport.c",
                  0x141,&local_158);
          local_30 = stdout;
          fprintf(stdout,"[%s %s:%d] Local fingerprint %s\n",&DAT_004126a4,"src/dtls_transport.c",
                  0x142,param_1 + 0x36);
        }
        memset(param_1 + 6,0,0x5c);
        memset(param_1 + 0x1d,0,0x5c);
        iVar1 = SSL_export_keying_material
                          ((SSL *)*param_1,(uchar *)&local_158,0x3c,"EXTRACTOR-dtls_srtp",0x13,
                           (uchar *)0x0,0,0);
        if (iVar1 == 0) {
          local_30 = stdout;
          uVar2 = ERR_get_error();
          pcVar3 = ERR_reason_error_string(uVar2);
          fprintf(local_30,"[%s %s:%d] Couldn\'t extract SRTP keying material(%s)\n","ERROR",
                  "src/dtls_transport.c",0x14c,pcVar3);
        }
        srtp_crypto_policy_set_rtp_default(param_1 + 8);
        srtp_crypto_policy_set_rtcp_default(param_1 + 0xe);
        local_50 = local_158;
        local_44 = local_14c;
        param_1[6] = 2;
        param_1[0x14] = &local_50;
        param_1[0x1c] = 0;
        local_4c = local_154;
        local_48 = local_150;
        local_40 = local_138;
        local_3c = local_134;
        local_38 = local_130;
        local_34 = local_12c;
        srtp_crypto_policy_set_rtp_default(param_1 + 0x1f);
        srtp_crypto_policy_set_rtcp_default(param_1 + 0x25);
        local_90 = local_148;
        local_8c = local_144;
        local_88 = local_140;
        local_84 = local_13c;
        param_1[0x1d] = 3;
        param_1[0x2b] = &local_90;
        param_1[0x33] = 0;
        local_80 = local_12a;
        local_7c = local_126;
        local_78 = local_122;
        local_74 = local_11e;
        iVar1 = srtp_create(param_1 + 0x34,param_1 + 6);
        if (iVar1 != 0) {
          local_30 = stdout;
          fprintf(stdout,"[%s %s:%d] Error creating inbound SRTP session for component\n","ERROR",
                  "src/dtls_transport.c",0x168);
        }
        local_30 = stdout;
        fprintf(stdout,"[%s %s:%d] Created inbound SRTP session\n",&DAT_004126a4,
                "src/dtls_transport.c",0x16a);
        iVar1 = srtp_create(param_1 + 0x35,param_1 + 0x1d);
        if (iVar1 != 0) {
          local_30 = stdout;
          fprintf(stdout,"[%s %s:%d] Error creating outbound SRTP session\n","ERROR",
                  "src/dtls_transport.c",0x16f);
        }
        fprintf(stdout,"[%s %s:%d] Created outbound SRTP session\n",&DAT_004126a4,
                "src/dtls_transport.c",0x171);
        param_1[0x5f] = 1;
      }
    }
    return;
  }
  return;
}



// === dtls_transport_decrypt_rtp_packet @ 00404648 ===

void dtls_transport_decrypt_rtp_packet(int param_1)

{
  (*(code *)PTR_srtp_unprotect_004271cc)(*(undefined4 *)(param_1 + 0xd0));
  return;
}



// === dtls_transport_decrypt_rtcp_packet @ 00404650 ===

void dtls_transport_decrypt_rtcp_packet(int param_1)

{
  (*(code *)PTR_srtp_unprotect_rtcp_0042706c)(*(undefined4 *)(param_1 + 0xd0));
  return;
}



// === dtls_transport_encrypt_rtp_packet @ 00404658 ===

void dtls_transport_encrypt_rtp_packet(int param_1)

{
  (*(code *)PTR_srtp_protect_0042730c)(*(undefined4 *)(param_1 + 0xd4));
  return;
}



// === dtls_transport_encrypt_rctp_packet @ 00404660 ===

void dtls_transport_encrypt_rctp_packet(int param_1)

{
  (*(code *)PTR_srtp_protect_rtcp_00427204)(*(undefined4 *)(param_1 + 0xd4));
  return;
}



// === dtls_transport_get_fingerprint @ 00404668 ===

int dtls_transport_get_fingerprint(int param_1)

{
  return param_1 + 0xd8;
}



// === peer_connection_enable_mdns @ 0040553c ===

void peer_connection_enable_mdns(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x5c) = param_2;
  return;
}



// === session_description_update_mdns_of_candidate @ 004063b8 ===

undefined4 session_description_update_mdns_of_candidate(char *param_1,char *param_2,size_t param_3)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  char acStack_118 [128];
  char acStack_98 [64];
  undefined1 auStack_58 [64];
  
  memset(acStack_118,0,0x80);
  memset(auStack_58,0,0x40);
  iVar4 = 4;
  memset(acStack_98,0,0x40);
  pcVar1 = param_1;
  do {
    pcVar1 = strchr(pcVar1,0x20);
    iVar4 = iVar4 + -1;
    pcVar1 = pcVar1 + 1;
  } while (iVar4 != 0);
  pcVar2 = strchr(pcVar1,0x20);
  strncpy(acStack_118,pcVar1,(int)pcVar2 - (int)pcVar1);
  iVar4 = utils_get_ipv4addr(acStack_118,auStack_58,0x40);
  if (iVar4 < 0) {
    uVar3 = 0xffffffff;
  }
  else {
    strncpy(acStack_98,param_1,(int)pcVar1 - (int)param_1);
    snprintf(param_2,param_3,"%s%s%s",acStack_98,auStack_58,pcVar2);
    uVar3 = 0;
  }
  return uVar3;
}



// === signaling_create @ 00406af0 ===

void * signaling_create(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  void *__ptr;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  size_t sVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 local_res0 [4];
  
  local_res0[0] = param_1;
  local_res0[1] = param_2;
  local_res0[2] = param_3;
  local_res0[3] = param_4;
  __ptr = calloc(1,0x278);
  if (__ptr == (void *)0x0) {
    return (void *)0x0;
  }
  puVar3 = (undefined4 *)register0x00000074;
  puVar1 = (undefined4 *)((int)__ptr + 0x160);
  do {
    puVar6 = puVar1;
    puVar2 = puVar3;
    uVar9 = puVar2[1];
    uVar8 = puVar2[2];
    uVar7 = puVar2[3];
    puVar3 = puVar2 + 4;
    *puVar6 = *puVar2;
    puVar6[1] = uVar9;
    puVar6[2] = uVar8;
    puVar6[3] = uVar7;
    puVar1 = puVar6 + 4;
  } while (puVar3 != (undefined4 *)&stack0x00000100);
  uVar8 = puVar2[5];
  uVar7 = puVar2[6];
  puVar6[4] = *puVar3;
  puVar6[5] = uVar8;
  puVar6[6] = uVar7;
  if (*(int *)((int)__ptr + 0x160) == 0) {
    iVar4 = GetLogLevel();
    if (iVar4 < 3) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,
               "[%s]-[%s](%d) [cpf]: signaling->option.protocol = SIGNALING_PROTOCOL_WEBSOCKETS\n",
               &DAT_004126a4,"src/signaling.c",0x13);
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(2,g_CrLogBuff,sVar5);
      CrLogUnLock();
    }
  }
  else if (*(int *)((int)__ptr + 0x160) == 1) {
    iVar4 = GetLogLevel();
    if (iVar4 < 3) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,
               "[%s]-[%s](%d) [cpf]: signaling->option.protocol = SIGNALING_PROTOCOL_WEBSOCKETS\n",
               &DAT_004126a4,"src/signaling.c",0x1a);
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(2,g_CrLogBuff,sVar5);
      CrLogUnLock();
      uVar7 = *(undefined4 *)((int)__ptr + 0x268);
    }
    else {
      uVar7 = *(undefined4 *)((int)__ptr + 0x268);
    }
    iVar4 = signaling_wsocket_create
                      ((int)__ptr + 0x164,*(undefined2 *)((int)__ptr + 0x264),(int)__ptr + 0x1e4,
                       uVar7,(int)__ptr + 0x26c);
    *(int *)((int)__ptr + 0x274) = iVar4;
    goto joined_r0x00406c58;
  }
  iVar4 = *(int *)((int)__ptr + 0x274);
joined_r0x00406c58:
  if (iVar4 == 0) {
    free(__ptr);
    __ptr = (void *)0x0;
  }
  return __ptr;
}



// === signaling_destroy @ 00406ce0 ===

void signaling_destroy(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_destroy(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_dispatch @ 00406d00 ===

void signaling_dispatch(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_dispatch(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_shutdown @ 00406d20 ===

void signaling_shutdown(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_shutdown(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_on_call_event @ 00406d40 ===

void signaling_on_call_event(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x26c) = param_2;
  *(undefined4 *)(param_1 + 0x270) = param_3;
  return;
}



// === signaling_send_answer_to_call @ 00406d4c ===

void signaling_send_answer_to_call(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_set_answer(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_observer_notify_event @ 00406d70 ===

void signaling_observer_notify_event
               (undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    if ((code *)*param_1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00406da8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)*param_1)(0,param_4);
      return;
    }
  }
  else if ((param_2 == 2) && ((code *)*param_1 != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x00406d8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*param_1)(2,param_4);
    return;
  }
  return;
}



// === update_icesig @ 00406db0 ===

void update_icesig(int param_1)

{
  int iVar1;
  size_t sVar2;
  
  iVar1 = GetLogLevel();
  if (iVar1 < 2) {
    CrLogLock();
    memset(g_CrLogBuff,0,0x800);
    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) update_icesig:%d for %d\r\n","DEBUG",
             "src/signaling_websockets.c",0x344,param_1,m_ice_sig);
    sVar2 = strlen(g_CrLogBuff);
    CrLogWrite(1,g_CrLogBuff,sVar2);
    CrLogUnLock();
  }
  switch(m_ice_sig) {
  case 1:
    m_ice_sig = 2;
    return;
  case 2:
    if (param_1 == 4) {
      m_ice_sig = 6;
    }
    else if (param_1 == 3) {
      m_ice_sig = 4;
      return;
    }
    break;
  case 4:
    m_ice_sig = 5;
    return;
  case 5:
  case 6:
    m_ice_sig = 7;
    return;
  case 7:
    m_ice_sig = 0;
  }
  return;
}



// === update_ice_server @ 00407268 ===

undefined4 update_ice_server(char *param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  long lVar3;
  time_t tVar4;
  size_t sVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  uVar6 = *(undefined4 *)(param_2 + 0x10);
  uVar7 = *(undefined4 *)(param_3 + 0x10);
  iVar1 = cJSON_IsString(param_2);
  if (iVar1 != 0) {
    pcVar2 = strchr(*(char **)(param_2 + 0x10),0x3a);
    iVar1 = GetLogLevel();
    if (iVar1 < 2) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ###username %s\n","DEBUG",
               "src/signaling_websockets.c",0xc1,*(undefined4 *)(param_2 + 0x10));
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(1,g_CrLogBuff,sVar5);
      CrLogUnLock();
    }
    if (pcVar2 != (char *)0x0) {
      tVar4 = time((time_t *)0x0);
      pcVar2 = *(char **)(param_2 + 0x10);
      iVar1 = get_webrtc_data();
      iVar1 = *(int *)(iVar1 + 4);
      lVar3 = strtol(pcVar2,(char **)0x0,10);
      *(long *)(iVar1 + 8) = lVar3;
      iVar1 = GetLogLevel();
      if (iVar1 < 2) {
        CrLogLock();
        memset(g_CrLogBuff,0,0x800);
        iVar1 = get_webrtc_data();
        uVar8 = *(undefined4 *)(*(int *)(iVar1 + 4) + 8);
        iVar1 = get_webrtc_data();
        snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ice_tm_tv %u, now:%u\n left:%d","DEBUG",
                 "src/signaling_websockets.c",199,uVar8,tVar4,
                 *(int *)(*(int *)(iVar1 + 4) + 8) - tVar4);
        sVar5 = strlen(g_CrLogBuff);
        CrLogWrite(1,g_CrLogBuff,sVar5);
        CrLogUnLock();
      }
    }
  }
  iVar1 = cJSON_IsString(param_3);
  if ((iVar1 != 0) && (iVar1 = GetLogLevel(), iVar1 < 2)) {
    CrLogLock();
    memset(g_CrLogBuff,0,0x800);
    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ###credential %s\n","DEBUG",
             "src/signaling_websockets.c",0xcc,*(undefined4 *)(param_3 + 0x10));
    sVar5 = strlen(g_CrLogBuff);
    CrLogWrite(1,g_CrLogBuff,sVar5);
    CrLogUnLock();
  }
  pcVar2 = strstr(param_1,"turn:");
  param_1 = param_1 + 5;
  if (pcVar2 != (char *)0x0) {
    pcVar2 = strchr(param_1,0x3a);
    iVar1 = get_webrtc_data();
    *(undefined1 *)(*(int *)(iVar1 + 4) + 1) = 1;
    if (pcVar2 == (char *)0x0) {
      lVar3 = 0;
    }
    else {
      *pcVar2 = '\0';
      lVar3 = strtol(pcVar2 + 1,(char **)0x0,10);
    }
    set_stun_server(param_1,lVar3,uVar6,uVar7);
    iVar1 = GetLogLevel();
    if (iVar1 < 2) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ###iceServer %s portNum:%d\n","DEBUG",
               "src/signaling_websockets.c",0xdc,param_1,lVar3);
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(1,g_CrLogBuff,sVar5);
      CrLogUnLock();
      return 0;
    }
  }
  return 0;
}



// === signaling_ws_thd @ 00408c48 ===

undefined4 signaling_ws_thd(int param_1)

{
  pthread_t __th;
  uint __seed;
  int iVar1;
  int iVar2;
  int iVar3;
  time_t tVar4;
  size_t sVar5;
  int iVar6;
  undefined1 auStack_1e8 [4];
  undefined1 *local_1e4;
  undefined4 local_1b8;
  undefined4 local_d0;
  undefined4 local_cc;
  int local_30;
  
  __th = pthread_self();
  pthread_detach(__th);
  if ((globalsn == 0) || (globalmodel == 0)) {
    GetRegisterInfoFromFile_part_1();
  }
  __seed = time((time_t *)0x0);
  srandom(__seed);
  lws_set_log_level(0x407,0);
  memset(auStack_1e8,0,0x1b8);
  local_1b8 = 0xffffffff;
  local_d0 = 0x1000;
  local_cc = 0;
  local_1e4 = protocols;
  if (*(int *)(param_1 + 0x14) == 0) {
    iVar1 = GetLogLevel();
    if (iVar1 < 5) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) lws init failed\n","ERROR",
               "src/signaling_websockets.c",0x473);
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(4,g_CrLogBuff,sVar5);
      CrLogUnLock();
    }
  }
  else {
    iVar1 = GetLogLevel();
    if (iVar1 < 2) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) signaling_ws_thd start\r\n","DEBUG",
               "src/signaling_websockets.c",0x476);
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(1,g_CrLogBuff,sVar5);
      CrLogUnLock();
    }
    iVar1 = 0;
    local_30 = 0x410000;
    do {
      iVar2 = get_webrtc_data();
      if (*(int *)(*(int *)(iVar2 + 4) + 0x10) < 1) {
        if (interrupted != 0) {
          iVar2 = 0;
LAB_00408d5c:
          iVar3 = get_webrtc_data();
          if ((*(char *)(*(int *)(iVar3 + 4) + 0x14) == '\0') ||
             (iVar3 = getsessioncount(), iVar3 == 0)) {
            iVar3 = GetLogLevel();
            if (iVar3 < 2) {
              CrLogLock();
              memset(g_CrLogBuff,0,0x800);
              snprintf(g_CrLogBuff,0x800,(char *)(local_30 + 0x37e8),"DEBUG",
                       "src/signaling_websockets.c",0x484);
              sVar5 = strlen(g_CrLogBuff);
              CrLogWrite(1,g_CrLogBuff,sVar5);
              CrLogUnLock();
            }
            iVar3 = get_webrtc_data();
            pthread_mutex_lock((pthread_mutex_t *)(*(int *)(iVar3 + 4) + 0x114));
            iVar3 = get_webrtc_data();
            iVar6 = *(int *)(iVar3 + 4);
            iVar3 = get_webrtc_data();
            pthread_cond_wait((pthread_cond_t *)(iVar6 + 0x130),
                              (pthread_mutex_t *)(*(int *)(iVar3 + 4) + 0x114));
            iVar3 = get_webrtc_data();
            pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(iVar3 + 4) + 0x114));
            iVar3 = GetLogLevel();
            if (iVar3 < 2) {
              CrLogLock();
              memset(g_CrLogBuff,0,0x800);
              iVar3 = get_webrtc_data();
              snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) interrupted get jwtToken\r\n","DEBUG",
                       "src/signaling_websockets.c",0x488,*(int *)(iVar3 + 4) + 0x14);
              sVar5 = strlen(g_CrLogBuff);
              CrLogWrite(1,g_CrLogBuff,sVar5);
              CrLogUnLock();
            }
          }
          else {
            iVar3 = GetLogLevel();
            if (iVar3 < 2) {
              CrLogLock();
              memset(g_CrLogBuff,0,0x800);
              iVar3 = get_webrtc_data();
              snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) interrupted jwtToken %s\r\n","DEBUG",
                       "src/signaling_websockets.c",0x47f,*(int *)(iVar3 + 4) + 0x14);
              sVar5 = strlen(g_CrLogBuff);
              CrLogWrite(1,g_CrLogBuff,sVar5);
              CrLogUnLock();
            }
            sleep(3);
          }
          iVar3 = GetLogLevel();
          goto joined_r0x00408eec;
        }
      }
      else {
        tVar4 = time((time_t *)0x0);
        iVar2 = get_webrtc_data();
        iVar2 = tVar4 - *(int *)(*(int *)(iVar2 + 4) + 0x10);
        if (interrupted != 0) goto LAB_00408d5c;
        if ((iVar2 < 0x79) || (m_wsi != 0)) goto LAB_00408e18;
        iVar3 = GetLogLevel();
        if (iVar3 < 5) {
          CrLogLock();
          memset(g_CrLogBuff,0,0x800);
          snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ##lws lost \n","ERROR",
                   "src/signaling_websockets.c",0x496);
          sVar5 = strlen(g_CrLogBuff);
          CrLogWrite(4,g_CrLogBuff,sVar5);
          CrLogUnLock();
        }
        iVar3 = get_webrtc_data();
        iVar3 = *(int *)(iVar3 + 4);
        tVar4 = time((time_t *)0x0);
        *(time_t *)(iVar3 + 0x10) = tVar4;
        iVar3 = GetLogLevel();
joined_r0x00408eec:
        if (iVar3 < 2) {
          iVar1 = iVar1 + 1;
          CrLogLock();
          memset(g_CrLogBuff,0,0x800);
          snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ##try to reconnect %lu inactive[%d sec]\r\n",
                   "DEBUG","src/signaling_websockets.c",0x499,iVar1,iVar2);
          sVar5 = strlen(g_CrLogBuff);
          CrLogWrite(1,g_CrLogBuff,sVar5);
          CrLogUnLock();
        }
        connect_client();
        interrupted = 0;
      }
LAB_00408e18:
      iVar2 = lws_service(*(undefined4 *)(param_1 + 0x14),0);
    } while (-1 < iVar2);
    iVar1 = GetLogLevel();
    if (iVar1 < 5) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,
               "[%s]-[%s](%d) ##OOOO -- exiting service loop. n = %d, interrupted = %d\n","ERROR",
               "src/signaling_websockets.c",0x4a1,iVar2,interrupted);
      sVar5 = strlen(g_CrLogBuff);
      CrLogWrite(4,g_CrLogBuff,sVar5);
      CrLogUnLock();
    }
    lws_context_destroy(*(undefined4 *)(param_1 + 0x14));
  }
  return 0;
}



// === cxy_signal_start @ 004092c0 ===

undefined4 cxy_signal_start(void *param_1)

{
  int iVar1;
  pthread_t apStack_10 [2];
  
  iVar1 = get_webrtc_data();
  pthread_mutex_init((pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114),(pthread_mutexattr_t *)0x0);
  iVar1 = get_webrtc_data();
  pthread_cond_init((pthread_cond_t *)(*(int *)(iVar1 + 4) + 0x130),(pthread_condattr_t *)0x0);
  pthread_create(apStack_10,(pthread_attr_t *)0x0,signaling_ws_thd,param_1);
  return 0;
}



// === signaling_wsocket_call_request @ 00409668 ===

void signaling_wsocket_call_request(undefined4 param_1,byte *param_2,size_t param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  uint uVar6;
  time_t tVar7;
  int iVar8;
  char *pcVar9;
  size_t sVar10;
  char acStack_c0 [128];
  byte *local_40 [2];
  char *local_38;
  char *local_34;
  int local_30;
  int local_2c;
  
  local_40[0] = (byte *)0x0;
  local_38 = "src/signaling_websockets.c";
  iVar2 = cJSON_ParseWithOpts(param_2,local_40,0);
  bVar1 = false;
  do {
    if (iVar2 == 0) {
      if (bVar1) {
LAB_00409840:
        if (param_3 == 0) {
          return;
        }
        uVar6 = param_3 + g_tmp_buf_idx;
        if (0x3bff < uVar6) {
          iVar2 = GetLogLevel();
          if (4 < iVar2) {
            g_tmp_buf_idx = 0;
            return;
          }
          CrLogLock();
          memset(g_CrLogBuff,0,0x800);
          snprintf(g_CrLogBuff,0x800,
                   "[%s]-[%s](%d) 2 too big no space cur[%u] for cur_len: %d flush all\r\n","ERROR",
                   "src/signaling_websockets.c",0x63e,g_tmp_buf_idx,param_3);
          sVar10 = strlen(g_CrLogBuff);
          CrLogWrite(4,g_CrLogBuff,sVar10);
          CrLogUnLock();
          g_tmp_buf_idx = 0;
          return;
        }
        g_tmp_buf_idx = uVar6;
        g_tmp_buf[uVar6] = 0;
        if (param_2 != g_tmp_buf) {
          memcpy(g_tmp_buf + uVar6,param_2,param_3);
          return;
        }
        return;
      }
      sVar10 = g_tmp_buf_idx + param_3;
      if (0x3bff < sVar10) {
        iVar2 = GetLogLevel();
        if (iVar2 < 5) {
          CrLogLock();
          memset(g_CrLogBuff,0,0x800);
          snprintf(g_CrLogBuff,0x800,
                   "[%s]-[%s](%d) too big no space cur[%u] for cur_len: %d flush all\r\n","ERROR",
                   "src/signaling_websockets.c",0x5a3,g_tmp_buf_idx,param_3);
          sVar10 = strlen(g_CrLogBuff);
          CrLogWrite(4,g_CrLogBuff,sVar10);
          CrLogUnLock();
          g_tmp_buf_idx = 0;
        }
        else {
          g_tmp_buf_idx = 0;
        }
        goto LAB_00409840;
      }
      memcpy(g_tmp_buf + g_tmp_buf_idx,param_2,param_3);
      g_tmp_buf_idx = 0;
      g_tmp_buf[sVar10] = 0;
      bVar1 = true;
      param_2 = g_tmp_buf;
    }
    else {
      iVar3 = cJSON_GetObjectItem(iVar2,"action");
      if (((((iVar3 != 0) && (iVar4 = cJSON_IsString(iVar3), iVar4 != 0)) &&
           (pcVar9 = *(char **)(iVar3 + 0x10), pcVar9 != (char *)0x0)) &&
          (((pcVar5 = (char *)cJSON_GetObjectItem(iVar2,&DAT_0041321c), pcVar5 != (char *)0x0 &&
            (local_34 = pcVar5, iVar3 = cJSON_IsNumber(pcVar5), iVar3 != 0)) &&
           ((*(int *)(local_34 + 0x14) == 0 &&
            ((pcVar5 = (char *)cJSON_GetObjectItem(iVar2,&DAT_0041396c), pcVar5 != (char *)0x0 &&
             (local_34 = pcVar5, iVar3 = cJSON_IsString(pcVar5), iVar3 != 0)))))))) &&
         (*(char **)(local_34 + 0x10) != (char *)0x0)) {
        strcpy(acStack_c0,*(char **)(local_34 + 0x10));
        iVar3 = strcmp(pcVar9,"join");
        if (iVar3 == 0) {
          update_icesig(1);
          iVar3 = get_webrtc_data();
          local_34 = *(char **)(iVar3 + 4);
          tVar7 = time((time_t *)0x0);
          *(time_t *)(local_34 + 0xc) = tVar7;
          iVar3 = get_webrtc_data();
          **(undefined1 **)(iVar3 + 4) = 1;
          iVar3 = GetLogLevel();
          if (iVar3 < 2) {
            CrLogLock();
            memset(g_CrLogBuff,0,0x800);
            snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) join ack\r\n","DEBUG",local_38,0x5c6);
            sVar10 = strlen(g_CrLogBuff);
            CrLogWrite(1,g_CrLogBuff,sVar10);
            CrLogUnLock();
          }
        }
        iVar3 = strcmp(pcVar9,"push_online");
        if (iVar3 == 0) {
          update_icesig(1);
          iVar3 = get_webrtc_data();
          **(undefined1 **)(iVar3 + 4) = 1;
          iVar3 = GetLogLevel();
          if (iVar3 < 2) {
            CrLogLock();
            memset(g_CrLogBuff,0,0x800);
            snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) join success\r\n","DEBUG",local_38,0x5ce);
            sVar10 = strlen(g_CrLogBuff);
            CrLogWrite(1,g_CrLogBuff,sVar10);
            CrLogUnLock();
          }
          iVar3 = cJSON_GetObjectItem(iVar2,"iceServers");
          if ((iVar3 != 0) && (iVar4 = cJSON_IsArray(iVar3), iVar4 != 0)) {
            local_34 = (char *)cJSON_GetArraySize(iVar3);
            iVar4 = GetLogLevel();
            if (iVar4 < 2) {
              CrLogLock();
              memset(g_CrLogBuff,0,0x800);
              snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ObjArr Len: %d\n","DEBUG",local_38,0x5d5,
                       local_34);
              sVar10 = strlen(g_CrLogBuff);
              CrLogWrite(1,g_CrLogBuff,sVar10);
              CrLogUnLock();
            }
            iVar3 = cJSON_GetArrayItem(iVar3,0);
            if (iVar3 != 0) {
              iVar4 = cJSON_GetObjectItem(iVar3,&DAT_00413238);
              local_34 = *(char **)(iVar4 + 0x10);
              iVar4 = cJSON_GetObjectItem(iVar3,"username");
              local_30 = cJSON_GetObjectItem(iVar3,"credential");
              iVar3 = GetLogLevel();
              if (iVar3 < 2) {
                CrLogLock();
                memset(g_CrLogBuff,0,0x800);
                snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) urls:%s username:%s credential:%s\n",
                         "DEBUG",local_38,0x5e0,local_34,*(undefined4 *)(iVar4 + 0x10),
                         *(undefined4 *)(local_30 + 0x10));
                sVar10 = strlen(g_CrLogBuff);
                CrLogWrite(1,g_CrLogBuff,sVar10);
                CrLogUnLock();
              }
              update_ice_server(local_34,iVar4,local_30);
            }
          }
        }
        else {
          iVar3 = strcmp(pcVar9,"ice_msg");
          if (((((iVar3 == 0) && (iVar3 = cJSON_GetObjectItem(iVar2,"sdpMessage"), iVar3 != 0)) &&
               (iVar4 = cJSON_IsObject(iVar3), iVar4 != 0)) &&
              ((pcVar9 = (char *)cJSON_GetObjectItem(iVar3,&DAT_00413a2c), pcVar9 != (char *)0x0 &&
               (local_34 = pcVar9, iVar4 = cJSON_IsString(pcVar9), iVar4 != 0)))) &&
             ((local_34 = *(char **)(local_34 + 0x10), local_34 != (char *)0x0 &&
              ((iVar3 = cJSON_GetObjectItem(iVar3,&DAT_00413a34), iVar3 != 0 &&
               (iVar4 = cJSON_IsObject(iVar3), iVar4 != 0)))))) {
            iVar4 = strcmp(local_34,"offer");
            if (iVar4 == 0) {
              local_34 = (char *)cJSON_GetObjectItem(iVar2,"iceServers");
              if ((local_34 != (char *)0x0) && (iVar4 = cJSON_IsArray(local_34), iVar4 != 0)) {
                local_30 = cJSON_GetArraySize(local_34);
                iVar4 = GetLogLevel();
                if (iVar4 < 2) {
                  CrLogLock();
                  memset(g_CrLogBuff,0,0x800);
                  snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) ObjArr Len: %d\n","DEBUG",local_38,0x5f7
                           ,local_30);
                  sVar10 = strlen(g_CrLogBuff);
                  CrLogWrite(1,g_CrLogBuff,sVar10);
                  CrLogUnLock();
                }
                iVar4 = cJSON_GetArrayItem(local_34,0);
                if (iVar4 != 0) {
                  local_34 = (char *)iVar4;
                  iVar4 = cJSON_GetObjectItem(iVar4,&DAT_00413238);
                  pcVar9 = local_34;
                  local_30 = (int)local_34;
                  local_34 = *(char **)(iVar4 + 0x10);
                  iVar8 = cJSON_GetObjectItem(pcVar9,"username");
                  iVar4 = local_30;
                  local_30 = iVar8;
                  local_2c = cJSON_GetObjectItem(iVar4,"credential");
                  iVar4 = GetLogLevel();
                  if (iVar4 < 2) {
                    CrLogLock();
                    memset(g_CrLogBuff,0,0x800);
                    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) urls:%s username:%s credential:%s\n",
                             "DEBUG",local_38,0x602,local_34,*(undefined4 *)(local_30 + 0x10),
                             *(undefined4 *)(local_2c + 0x10));
                    sVar10 = strlen(g_CrLogBuff);
                    CrLogWrite(1,g_CrLogBuff,sVar10);
                    CrLogUnLock();
                  }
                  update_ice_server(local_34,local_30,local_2c);
                }
              }
              iVar3 = cJSON_GetObjectItem(iVar3,&DAT_00413a44);
              if ((iVar3 != 0) && (iVar4 = cJSON_IsString(iVar3), iVar4 != 0)) {
                signaling_observer_notify_event
                          (*m_signaling_wsocket,0,acStack_c0,*(undefined4 *)(iVar3 + 0x10));
              }
            }
            else {
              local_30 = 0x410000;
              iVar4 = strcmp(local_34,"candidate");
              if (((iVar4 == 0) &&
                  (iVar3 = cJSON_GetObjectItem(iVar3,local_30 + 0x2bd4), iVar3 != 0)) &&
                 (iVar4 = cJSON_IsString(iVar3), iVar4 != 0)) {
                if (**(char **)(iVar3 + 0x10) == '\0') {
                  cJSON_Delete(iVar2);
                  return;
                }
                signaling_observer_notify_event(*m_signaling_wsocket,2,acStack_c0);
              }
            }
          }
        }
      }
      cJSON_Delete(iVar2);
      if (local_40[0] == (byte *)0x0) {
        g_tmp_buf_idx = 0;
        return;
      }
      sVar10 = param_3 - ((int)local_40[0] - (int)param_2);
      param_2 = local_40[0];
      while( true ) {
        if (sVar10 == 0) {
          g_tmp_buf_idx = 0;
          return;
        }
        if ((0x16 < (*param_2 - 10 & 0xff)) ||
           (-1 < (int)((0x400009U >> (*param_2 - 10 & 0x1f)) << 0x1f))) break;
        sVar10 = sVar10 - 1;
        param_2 = param_2 + 1;
      }
    }
    iVar2 = cJSON_ParseWithOpts(param_2,local_40,0);
    param_3 = sVar10;
  } while( true );
}



// === signaling_wsocket_create @ 0040a03c ===

undefined4 *
signaling_wsocket_create
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5)

{
  int iVar1;
  undefined4 *puVar2;
  size_t sVar3;
  
  iVar1 = GetLogLevel();
  if (iVar1 < 2) {
    CrLogLock();
    memset(g_CrLogBuff,0,0x800);
    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) signaling_wsocket_create %s:%d\r\n","DEBUG",
             "src/signaling_websockets.c",0x6c0,param_1,param_2);
    sVar3 = strlen(g_CrLogBuff);
    CrLogWrite(1,g_CrLogBuff,sVar3);
    CrLogUnLock();
  }
  puVar2 = malloc(0x90);
  if (puVar2 != (undefined4 *)0x0) {
    snprintf((char *)(puVar2 + 1),0x80,"/api/cxy/ws/webrtc/signal/push/%s",param_3);
    puVar2[0x23] = param_4;
    puVar2[0x22] = 0;
    iVar1 = wsocket_init(param_1,param_2);
    puVar2[0x21] = iVar1;
    if (iVar1 != 0) {
      *(undefined4 **)(iVar1 + 0x18) = puVar2;
      m_ws_serv = iVar1;
      *puVar2 = param_5;
      m_signaling_wsocket = puVar2;
      return puVar2;
    }
  }
  return (undefined4 *)0x0;
}



// === signaling_wsocket_destroy @ 0040a1a0 ===

void signaling_wsocket_destroy(void *param_1)

{
  int iVar1;
  size_t sVar2;
  void *pvVar3;
  
  if (param_1 == (void *)0x0) {
    return;
  }
  iVar1 = GetLogLevel();
  if (iVar1 < 2) {
    CrLogLock();
    memset(g_CrLogBuff,0,0x800);
    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) signaling_wsocket_destroy\r\n","DEBUG",
             "src/signaling_websockets.c",0x6db);
    sVar2 = strlen(g_CrLogBuff);
    CrLogWrite(1,g_CrLogBuff,sVar2);
    CrLogUnLock();
    pvVar3 = *(void **)((int)param_1 + 0x84);
    if (pvVar3 == (void *)0x0) {
      pvVar3 = *(void **)((int)param_1 + 0x88);
      goto LAB_0040a1e4;
    }
LAB_0040a1d8:
    free(pvVar3);
  }
  else {
    pvVar3 = *(void **)((int)param_1 + 0x84);
    if (pvVar3 != (void *)0x0) goto LAB_0040a1d8;
  }
  pvVar3 = *(void **)((int)param_1 + 0x88);
LAB_0040a1e4:
  if (pvVar3 != (void *)0x0) {
    free(pvVar3);
  }
  free(param_1);
  if (globalmodel != (void *)0x0) {
    free(globalmodel);
    globalmodel = (void *)0x0;
  }
  if (globalsn != (void *)0x0) {
    free(globalsn);
    globalsn = (void *)0x0;
  }
  return;
}



// === signaling_wsocket_dispatch @ 0040a2d0 ===

undefined4 signaling_wsocket_dispatch(int param_1)

{
  int iVar1;
  void *__arg;
  pthread_t apStack_10 [2];
  
  __arg = *(void **)(param_1 + 0x84);
  iVar1 = get_webrtc_data();
  pthread_mutex_init((pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114),(pthread_mutexattr_t *)0x0);
  iVar1 = get_webrtc_data();
  pthread_cond_init((pthread_cond_t *)(*(int *)(iVar1 + 4) + 0x130),(pthread_condattr_t *)0x0);
  pthread_create(apStack_10,(pthread_attr_t *)0x0,signaling_ws_thd,__arg);
  return 0;
}



// === signaling_wsocket_shutdown @ 0040a2d8 ===

void signaling_wsocket_shutdown(void)

{
  return;
}



// === signaling_wsocket_set_answer @ 0040a490 ===

void signaling_wsocket_set_answer(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  char *pcVar8;
  int iVar9;
  int *piVar10;
  size_t sVar11;
  char *__haystack;
  
  uVar1 = cJSON_CreateObject();
  cJSON_AddStringToObject(uVar1,"action","ice_msg");
  cJSON_AddStringToObject(uVar1,&DAT_00413b88,*(undefined4 *)(param_2 + 0x2c));
  uVar2 = cJSON_CreateObject();
  uVar3 = cJSON_CreateObject();
  cJSON_AddStringToObject(uVar3,&DAT_00413a2c,"answer");
  cJSON_AddStringToObject(uVar2,&DAT_00413a2c,"answer");
  cJSON_AddStringToObject(uVar2,&DAT_00413a44,param_3);
  cJSON_AddItemToObject(uVar3,&DAT_00413a34,uVar2);
  cJSON_AddItemToObject(uVar1,"sdpMessage",uVar3);
  pvVar4 = (void *)cJSON_Print(uVar1);
  iVar5 = GetLogLevel();
  if (iVar5 < 2) {
    CrLogLock();
    memset(g_CrLogBuff,0,0x800);
    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) generate answer,and candidate:\n","DEBUG",
             "src/signaling_websockets.c",0x521);
    sVar11 = strlen(g_CrLogBuff);
    CrLogWrite(1,g_CrLogBuff,sVar11);
    CrLogUnLock();
  }
  cJSON_Delete(uVar1);
  piVar6 = (int *)create_ice_send_buf(pvVar4);
  if (piVar6 != (int *)0x0) {
    g_mutex_lock(param_2 + 0xc);
    piVar7 = *(int **)(param_2 + 0x28);
    *(int **)(param_2 + 0x28) = piVar6;
    *piVar6 = param_2 + 0x24;
    piVar6[1] = (int)piVar7;
    *piVar7 = (int)piVar6;
    g_mutex_unlock(param_2 + 0xc);
  }
  free(pvVar4);
  iVar5 = *(int *)(param_2 + 0x6c);
  *(undefined4 *)(param_2 + 0x30) = 6;
  if ((iVar5 != 0) && (*(char *)(iVar5 + 4) != '\0')) {
    piVar6 = (int *)g_strsplit(iVar5 + 4,"\r\n",0x100);
    __haystack = (char *)*piVar6;
    if (__haystack != (char *)0x0) {
      do {
        piVar6 = piVar6 + 1;
        pcVar8 = strstr(__haystack,"candidate");
        if (pcVar8 != (char *)0x0) {
          iVar5 = g_strsplit(__haystack,&DAT_00413bc4,2);
          uVar1 = cJSON_CreateObject();
          cJSON_AddStringToObject(uVar1,"action","ice_msg");
          cJSON_AddStringToObject(uVar1,&DAT_00413b88,*(undefined4 *)(param_2 + 0x2c));
          uVar2 = cJSON_CreateObject();
          cJSON_AddStringToObject(uVar2,&DAT_00413a2c,"candidate");
          uVar3 = cJSON_CreateObject();
          cJSON_AddStringToObject(uVar3,"candidate",*(undefined4 *)(iVar5 + 4));
          cJSON_AddNumberToObject(uVar3,"sdpMLineIndex",0,0);
          cJSON_AddStringToObject(uVar3,"sdpMid",&DAT_00412928);
          cJSON_AddItemToObject(uVar2,&DAT_00413a34,uVar3);
          cJSON_AddItemToObject(uVar1,"sdpMessage",uVar2);
          pvVar4 = (void *)cJSON_Print(uVar1);
          cJSON_Delete(uVar1);
          if (pvVar4 != (void *)0x0) {
            iVar9 = GetLogLevel();
            if (iVar9 < 2) {
              CrLogLock();
              memset(g_CrLogBuff,0,0x800);
              snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) %s\n","DEBUG","src/signaling_websockets.c",
                       0x570,*(undefined4 *)(iVar5 + 4));
              sVar11 = strlen(g_CrLogBuff);
              CrLogWrite(1,g_CrLogBuff,sVar11);
              CrLogUnLock();
            }
            piVar7 = (int *)create_ice_send_buf(pvVar4);
            if (piVar7 != (int *)0x0) {
              g_mutex_lock(param_2 + 0xc);
              piVar10 = *(int **)(param_2 + 0x28);
              *(int **)(param_2 + 0x28) = piVar7;
              *piVar7 = param_2 + 0x24;
              piVar7[1] = (int)piVar10;
              *piVar10 = (int)piVar7;
              g_mutex_unlock(param_2 + 0xc);
            }
            free(pvVar4);
          }
        }
        __haystack = (char *)*piVar6;
      } while (__haystack != (char *)0x0);
      return;
    }
  }
  return;
}



// === signaling_websockets @ 0040ca74 ===

undefined4 signaling_websockets(undefined4 param_1)

{
  undefined4 *puVar1;
  char **ppcVar2;
  pthread_t __target_thread;
  size_t sVar3;
  long lVar4;
  undefined4 *puVar5;
  int iVar6;
  char **ppcVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  void *__src;
  char *local_120 [67];
  
  __target_thread = pthread_self();
  pthread_setname_np(__target_thread,"sig_websockets");
  pthread_detach(__target_thread);
  iVar6 = webrtc_context_ptr;
  pcVar10 = (char *)(webrtc_context_ptr + 0x200);
  sVar3 = strlen(pcVar10);
  pcVar9 = (char *)(iVar6 + 0x380);
  memcpy(&DAT_004274d4,pcVar10,sVar3);
  lVar4 = strtol(pcVar9,(char **)0x0,10);
  __src = *(void **)(hosts_list + lVar4 * 4);
  lVar4 = strtol(pcVar9,(char **)0x0,10);
  sVar3 = strlen(*(char **)(hosts_list + lVar4 * 4));
  memcpy(&DAT_00427454,__src,sVar3);
  lVar4 = strtol(pcVar9,(char **)0x0,10);
  DAT_00427554 = *(undefined2 *)(hosts_port + lVar4 * 2);
  puVar1 = &DAT_00427460;
  ppcVar2 = local_120;
  do {
    ppcVar7 = ppcVar2;
    puVar5 = puVar1;
    pcVar8 = (char *)puVar5[1];
    pcVar10 = (char *)puVar5[2];
    pcVar9 = (char *)puVar5[3];
    *ppcVar7 = (char *)*puVar5;
    ppcVar7[1] = pcVar8;
    ppcVar7[2] = pcVar10;
    ppcVar7[3] = pcVar9;
    puVar1 = puVar5 + 4;
    ppcVar2 = ppcVar7 + 4;
  } while (puVar5 + 4 != (undefined4 *)0x427550);
  pcVar10 = (char *)puVar5[5];
  pcVar9 = (char *)puVar5[6];
  ppcVar7[4] = pcRam00427550;
  ppcVar7[5] = pcVar10;
  ppcVar7[6] = pcVar9;
  g_webrtc_data._4_4_ = signaling_create(signaling_option,DAT_00427454,DAT_00427458,DAT_0042745c);
  g_gloop = param_1;
  if (g_webrtc_data._4_4_ == 0) {
    iVar6 = GetLogLevel();
    if (iVar6 < 5) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      local_120[1] = (char *)0x21b;
      local_120[0] = "webrtc_main.c";
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) Create signaling service failed\n","ERROR");
      sVar3 = strlen(g_CrLogBuff);
      CrLogWrite(4,g_CrLogBuff,sVar3);
      CrLogUnLock();
    }
  }
  else {
    signaling_on_call_event(g_webrtc_data._4_4_,on_call_event,0);
    signaling_dispatch(g_webrtc_data._4_4_);
  }
  return 0;
}



// === signal_handler @ 0040cca8 ===

void signal_handler(int param_1)

{
  int iVar1;
  char *pcVar2;
  size_t sVar3;
  
  *(undefined1 *)((int)webrtc_context_ptr + 0x52c) = 1;
  iVar1 = GetLogLevel();
  if (iVar1 < 3) {
    CrLogLock();
    memset(g_CrLogBuff,0,0x800);
    pcVar2 = strsignal(param_1);
    snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) Get signal: %s\n",&DAT_004126a4,"webrtc_main.c",0x26e,
             pcVar2);
    sVar3 = strlen(g_CrLogBuff);
    CrLogWrite(2,g_CrLogBuff,sVar3);
    CrLogUnLock();
  }
  usleep(1000000);
  log_exit();
  if (webrtc_context_ptr != (void *)0x0) {
    free(webrtc_context_ptr);
    webrtc_context_ptr = (void *)0x0;
  }
                    /* WARNING: Subroutine does not return */
  exit(1);
}



// === usr_signal_handler @ 0040def0 ===

void usr_signal_handler(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  size_t sVar3;
  
  if (param_1 == 0x10) {
    iVar1 = GetLogLevel();
    if (iVar1 < 3) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) Received SIGUSR1: Showing basic debug info...\n",
               &DAT_004126a4,"webrtc_main.c",0x25a);
      sVar3 = strlen(g_CrLogBuff);
      CrLogWrite(2,g_CrLogBuff,sVar3);
      CrLogUnLock();
    }
    show_webrtc_context(0);
    return;
  }
  if (param_1 == 0x11) {
    iVar1 = GetLogLevel();
    if (iVar1 < 3) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) Received SIGUSR2: log level...\n",&DAT_004126a4,
               "webrtc_main.c",0x260);
      sVar3 = strlen(g_CrLogBuff);
      CrLogWrite(2,g_CrLogBuff,sVar3);
      CrLogUnLock();
    }
    log_set_level(1);
    iVar1 = GetLogLevel();
    if (iVar1 < 3) {
      CrLogLock();
      memset(g_CrLogBuff,0,0x800);
      uVar2 = log_get_level();
      snprintf(g_CrLogBuff,0x800,"[%s]-[%s](%d) log level : %d\n",&DAT_004126a4,"webrtc_main.c",
               0x262,uVar2);
      sVar3 = strlen(g_CrLogBuff);
      CrLogWrite(2,g_CrLogBuff,sVar3);
      CrLogUnLock();
      return;
    }
  }
  return;
}



// === webrtc_signal_init @ 0040e0d8 ===

void webrtc_signal_init(void)

{
  _union_1051 local_98;
  code *local_94;
  sigset_t sStack_90;
  
  local_94 = signal_handler;
  local_98.sa_handler = (__sighandler_t)0x0;
  sigemptyset(&sStack_90);
  sigaction(2,(sigaction *)&local_98,(sigaction *)0x0);
  sigaction(0xf,(sigaction *)&local_98,(sigaction *)0x0);
  sigaction(1,(sigaction *)&local_98,(sigaction *)0x0);
  local_94 = usr_signal_handler;
  sigaction(0x10,(sigaction *)&local_98,(sigaction *)0x0);
  sigaction(0x11,(sigaction *)&local_98,(sigaction *)0x0);
  return;
}



// === webrtc_shm_cmd_process @ 0040f240 ===

undefined4 webrtc_shm_cmd_process(char *param_1)

{
  char *pcVar1;
  
  pcVar1 = strstr(param_1,"webRtc=");
  if (pcVar1 != (char *)0x0) {
    app_webrtc_notify(pcVar1 + 7);
    return 0;
  }
  return 0xffffffff;
}



// === get_total_time @ 00411d40 ===

/* WARNING: Removing unreachable block (ram,0x00411d64) */

int get_total_time(void)

{
  timespec local_10;
  
  clock_gettime(1,&local_10);
  return local_10.tv_sec * 1000 + local_10.tv_nsec / 1000000;
}



// === SSL_CTX_free @ 004160f0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_free(SSL_CTX *param_1)

{
  (*(code *)PTR_SSL_CTX_free_0042701c)();
  return;
}



// === EVP_PKEY_free @ 004161c0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EVP_PKEY_free(EVP_PKEY *pkey)

{
  (*(code *)PTR_EVP_PKEY_free_00427050)();
  return;
}



// === X509_getm_notAfter @ 004161e0 ===

void X509_getm_notAfter(void)

{
  (*(code *)PTR_X509_getm_notAfter_00427058)();
  return;
}



// === SSL_set_options @ 004162a0 ===

void SSL_set_options(void)

{
  (*(code *)PTR_SSL_set_options_00427088)();
  return;
}



// === SSL_new @ 004162c0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL * SSL_new(SSL_CTX *ctx)

{
  SSL *pSVar1;
  
  pSVar1 = (SSL *)(*(code *)PTR_SSL_new_00427090)();
  return pSVar1;
}



// === g_mutex_unlock @ 004162d0 ===

void g_mutex_unlock(void)

{
  (*(code *)PTR_g_mutex_unlock_00427094)();
  return;
}



// === SSL_CTX_use_certificate @ 00416300 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_certificate(SSL_CTX *ctx,X509 *x)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_use_certificate_004270a0)();
  return iVar1;
}



// === g_signal_connect_data @ 00416370 ===

void g_signal_connect_data(void)

{
  (*(code *)PTR_g_signal_connect_data_004270bc)();
  return;
}



// === SSL_read @ 00416400 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_read(SSL *ssl,void *buf,int num)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_read_004270e0)();
  return iVar1;
}



// === SSL_export_keying_material @ 00416510 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_export_keying_material
              (SSL *s,uchar *out,size_t olen,char *label,size_t llen,uchar *p,size_t plen,
              int use_context)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_export_keying_material_00427124)();
  return iVar1;
}



// === strsignal @ 00416540 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strsignal(int __sig)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_strsignal_00427130)();
  return pcVar1;
}



// === EC_KEY_new_by_curve_name @ 00416590 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EC_KEY * EC_KEY_new_by_curve_name(int nid)

{
  EC_KEY *pEVar1;
  
  pEVar1 = (EC_KEY *)(*(code *)PTR_EC_KEY_new_by_curve_name_00427144)();
  return pEVar1;
}



// === SSL_do_handshake @ 00416610 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_do_handshake(SSL *s)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_do_handshake_00427164)();
  return iVar1;
}



// === SSL_CTX_set_verify @ 00416680 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_set_verify(SSL_CTX *ctx,int mode,callback *callback)

{
  (*(code *)PTR_SSL_CTX_set_verify_00427180)();
  return;
}



// === SSL_set_bio @ 00416690 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_bio(SSL *s,BIO *rbio,BIO *wbio)

{
  (*(code *)PTR_SSL_set_bio_00427184)();
  return;
}



// === RSA_generate_key_ex @ 004166e0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int RSA_generate_key_ex(RSA *rsa,int bits,BIGNUM *e,BN_GENCB *cb)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_RSA_generate_key_ex_00427198)();
  return iVar1;
}



// === SSL_CTX_new @ 00416710 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL_CTX * SSL_CTX_new(SSL_METHOD *meth)

{
  SSL_CTX *pSVar1;
  
  pSVar1 = (SSL_CTX *)(*(code *)PTR_SSL_CTX_new_004271a4)();
  return pSVar1;
}



// === EVP_PKEY_assign @ 00416750 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_PKEY_assign(EVP_PKEY *pkey,int type,void *key)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_PKEY_assign_004271b4)();
  return iVar1;
}



// === X509_sign @ 00416780 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_sign(X509 *x,EVP_PKEY *pkey,EVP_MD *md)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_X509_sign_004271c0)();
  return iVar1;
}



// === SSL_free @ 004167c0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_free(SSL *ssl)

{
  (*(code *)PTR_SSL_free_004271d0)();
  return;
}



// === srtp_crypto_policy_set_rtp_default @ 004167d0 ===

void srtp_crypto_policy_set_rtp_default(void)

{
  (*(code *)PTR_srtp_crypto_policy_set_rtp_default_004271d4)();
  return;
}



// === SSL_get_peer_certificate @ 00416840 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

X509 * SSL_get_peer_certificate(SSL *s)

{
  X509 *pXVar1;
  
  pXVar1 = (X509 *)(*(code *)PTR_SSL_get_peer_certificate_004271f0)();
  return pXVar1;
}



// === SSL_get_error @ 004168a0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_get_error(SSL *s,int ret_code)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_get_error_00427208)();
  return iVar1;
}



// === SSL_CTX_ctrl @ 004168e0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_CTX_ctrl(SSL_CTX *ctx,int cmd,long larg,void *parg)

{
  long lVar1;
  
  lVar1 = (*(code *)PTR_SSL_CTX_ctrl_00427218)();
  return lVar1;
}



// === srtp_crypto_policy_set_rtcp_default @ 00416930 ===

void srtp_crypto_policy_set_rtcp_default(void)

{
  (*(code *)PTR_srtp_crypto_policy_set_rtcp_default_0042722c)();
  return;
}



// === SSL_set_accept_state @ 00416940 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_accept_state(SSL *s)

{
  (*(code *)PTR_SSL_set_accept_state_00427230)();
  return;
}



// === EC_KEY_free @ 00416970 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EC_KEY_free(EC_KEY *key)

{
  (*(code *)PTR_EC_KEY_free_0042723c)();
  return;
}



// === pthread_cond_signal @ 004169f0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_cond_signal_0042725c)();
  return iVar1;
}



// === SSL_CTX_use_PrivateKey @ 00416a50 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx,EVP_PKEY *pkey)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_use_PrivateKey_00427274)();
  return iVar1;
}



// === SSL_ctrl @ 00416b50 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_ctrl(SSL *ssl,int cmd,long larg,void *parg)

{
  long lVar1;
  
  lVar1 = (*(code *)PTR_SSL_ctrl_004272b4)();
  return lVar1;
}



// === pthread_mutex_unlock @ 00416bd0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_mutex_unlock_004272d4)();
  return iVar1;
}



// === lws_add_http_header_by_token @ 00416c00 ===

void lws_add_http_header_by_token(void)

{
  (*(code *)PTR_lws_add_http_header_by_token_004272e0)();
  return;
}



// === CrLogUnLock @ 00416d10 ===

void CrLogUnLock(void)

{
  (*(code *)PTR_CrLogUnLock_00427324)();
  return;
}



// === DTLS_method @ 00416d90 ===

void DTLS_method(void)

{
  (*(code *)PTR_DTLS_method_00427344)();
  return;
}



// === EVP_PKEY_new @ 00416dd0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EVP_PKEY * EVP_PKEY_new(void)

{
  EVP_PKEY *pEVar1;
  
  pEVar1 = (EVP_PKEY *)(*(code *)PTR_EVP_PKEY_new_00427354)();
  return pEVar1;
}



// === SSL_CTX_check_private_key @ 00416e80 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_check_private_key(SSL_CTX *ctx)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_check_private_key_00427380)();
  return iVar1;
}



// === SSL_is_init_finished @ 00416ec0 ===

void SSL_is_init_finished(void)

{
  (*(code *)PTR_SSL_is_init_finished_00427390)();
  return;
}



// === X509_set_pubkey @ 00416ed0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_set_pubkey(X509 *x,EVP_PKEY *pkey)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_X509_set_pubkey_00427394)();
  return iVar1;
}



// === g_cond_signal @ 00416f20 ===

void g_cond_signal(void)

{
  (*(code *)PTR_g_cond_signal_004273a8)();
  return;
}



// === SSL_CTX_set_tlsext_use_srtp @ 00416fd0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_set_tlsext_use_srtp(SSL_CTX *ctx,char *profiles)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_set_tlsext_use_srtp_004273d4)();
  return iVar1;
}



// === SSL_CTX_free @ 0043000c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_free(SSL_CTX *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_PKEY_free @ 0043003c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EVP_PKEY_free(EVP_PKEY *pkey)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_PKEY_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === X509_getm_notAfter @ 00430044 ===

/* WARNING: Control flow encountered bad instruction data */

void X509_getm_notAfter(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* X509_getm_notAfter@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_set_options @ 00430078 ===

/* WARNING: Control flow encountered bad instruction data */

void SSL_set_options(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_set_options@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_new @ 00430080 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL * SSL_new(SSL_CTX *ctx)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_new@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === g_mutex_unlock @ 00430084 ===

/* WARNING: Control flow encountered bad instruction data */

void g_mutex_unlock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_CTX_use_certificate @ 00430090 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_certificate(SSL_CTX *ctx,X509 *x)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_use_certificate@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === g_signal_connect_data @ 004300ac ===

/* WARNING: Control flow encountered bad instruction data */

void g_signal_connect_data(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_read @ 004300d0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_read(SSL *ssl,void *buf,int num)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_read@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_export_keying_material @ 00430114 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_export_keying_material
              (SSL *s,uchar *out,size_t olen,char *label,size_t llen,uchar *p,size_t plen,
              int use_context)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_export_keying_material@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === strsignal @ 00430120 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strsignal(int __sig)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* strsignal@@GLIBC_2.0 */
  halt_baddata();
}



// === EC_KEY_new_by_curve_name @ 00430134 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EC_KEY * EC_KEY_new_by_curve_name(int nid)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EC_KEY_new_by_curve_name@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_do_handshake @ 00430154 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_do_handshake(SSL *s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_do_handshake@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_set_verify @ 00430170 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_set_verify(SSL_CTX *ctx,int mode,callback *callback)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_set_verify@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_set_bio @ 00430174 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_bio(SSL *s,BIO *rbio,BIO *wbio)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_set_bio@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === RSA_generate_key_ex @ 00430188 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int RSA_generate_key_ex(RSA *rsa,int bits,BIGNUM *e,BN_GENCB *cb)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* RSA_generate_key_ex@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_new @ 00430194 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL_CTX * SSL_CTX_new(SSL_METHOD *meth)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_new@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_PKEY_assign @ 004301a4 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_PKEY_assign(EVP_PKEY *pkey,int type,void *key)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_PKEY_assign@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === X509_sign @ 004301b0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_sign(X509 *x,EVP_PKEY *pkey,EVP_MD *md)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* X509_sign@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_free @ 004301c0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_free(SSL *ssl)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === srtp_crypto_policy_set_rtp_default @ 004301c4 ===

/* WARNING: Control flow encountered bad instruction data */

void srtp_crypto_policy_set_rtp_default(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_get_peer_certificate @ 004301e0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

X509 * SSL_get_peer_certificate(SSL *s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_get_peer_certificate@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_get_error @ 004301f8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_get_error(SSL *s,int ret_code)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_get_error@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_ctrl @ 00430208 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_CTX_ctrl(SSL_CTX *ctx,int cmd,long larg,void *parg)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_ctrl@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === srtp_crypto_policy_set_rtcp_default @ 0043021c ===

/* WARNING: Control flow encountered bad instruction data */

void srtp_crypto_policy_set_rtcp_default(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_set_accept_state @ 00430220 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_accept_state(SSL *s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_set_accept_state@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EC_KEY_free @ 0043022c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EC_KEY_free(EC_KEY *key)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EC_KEY_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_cond_signal @ 0043024c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_cond_signal@@GLIBC_2.3.2 */
  halt_baddata();
}



// === SSL_CTX_use_PrivateKey @ 00430264 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx,EVP_PKEY *pkey)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_use_PrivateKey@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_ctrl @ 004302a4 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_ctrl(SSL *ssl,int cmd,long larg,void *parg)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_ctrl@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_mutex_unlock @ 004302c4 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_mutex_unlock@@GLIBC_2.0 */
  halt_baddata();
}



// === lws_add_http_header_by_token @ 004302d0 ===

/* WARNING: Control flow encountered bad instruction data */

void lws_add_http_header_by_token(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === CrLogUnLock @ 00430314 ===

/* WARNING: Control flow encountered bad instruction data */

void CrLogUnLock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === DTLS_method @ 00430334 ===

/* WARNING: Control flow encountered bad instruction data */

void DTLS_method(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* DTLS_method@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_PKEY_new @ 00430348 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EVP_PKEY * EVP_PKEY_new(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_PKEY_new@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_check_private_key @ 00430374 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_check_private_key(SSL_CTX *ctx)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_check_private_key@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_is_init_finished @ 00430384 ===

/* WARNING: Control flow encountered bad instruction data */

void SSL_is_init_finished(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_is_init_finished@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === X509_set_pubkey @ 00430388 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_set_pubkey(X509 *x,EVP_PKEY *pkey)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* X509_set_pubkey@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === g_cond_signal @ 0043039c ===

/* WARNING: Control flow encountered bad instruction data */

void g_cond_signal(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_CTX_set_tlsext_use_srtp @ 004303c4 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_set_tlsext_use_srtp(SSL_CTX *ctx,char *profiles)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_set_tlsext_use_srtp@@OPENSSL_1_1_0 */
  halt_baddata();
}


