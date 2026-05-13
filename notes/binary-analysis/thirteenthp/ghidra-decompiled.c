
// === signal_handler @ 00403a50 ===

void signal_handler(int param_1)

{
  FILE *__stream;
  char *pcVar1;
  
  __stream = stdout;
  pcVar1 = strsignal(param_1);
  fprintf(__stream,"[%s %s:%d] Get signal: %s\n\n",&DAT_0040e168,"webrtclocal_main.c",0x146,pcVar1);
  hs_log_destory(log);
                    /* WARNING: Subroutine does not return */
  exit(1);
}



// === signaling_http @ 00403e34 ===

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 signaling_http(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  pthread_t __th;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 local_118 [66];
  pthread_t apStack_10 [2];
  
  __th = pthread_self();
  pthread_detach(__th);
  puVar1 = &DAT_0040e6e4;
  puVar2 = local_118;
  do {
    puVar4 = puVar2;
    puVar3 = puVar1;
    uVar7 = puVar3[1];
    uVar6 = puVar3[2];
    uVar5 = puVar3[3];
    *puVar4 = *puVar3;
    puVar4[1] = uVar7;
    puVar4[2] = uVar6;
    puVar4[3] = uVar5;
    puVar1 = puVar3 + 4;
    puVar2 = puVar4 + 4;
  } while (puVar3 + 4 != (undefined4 *)&UNK_0040e7d4);
  uVar6 = puVar3[5];
  uVar5 = puVar3[6];
  puVar4[4] = _UNK_0040e7d4;
  puVar4[5] = uVar6;
  puVar4[6] = uVar5;
  g_webrtc_data._4_4_ = signaling_create(signaling_option,DAT_0040e6d8,DAT_0040e6dc,DAT_0040e6e0);
  if (g_webrtc_data._4_4_ != 0) {
    pthread_create(apStack_10,(pthread_attr_t *)0x0,sessions_manager,(void *)0x0);
    signaling_on_call_event(g_webrtc_data._4_4_,on_call_event,0);
    signaling_dispatch(g_webrtc_data._4_4_);
    return 0;
  }
  local_118[0] = 0x12e;
  fprintf(stdout,"[%s %s:%d] Create signaling service failed\n\n","ERROR","webrtclocal_main.c");
  return 0;
}



// === cb_dtls_verify @ 00404620 ===

bool cb_dtls_verify(undefined4 param_1,X509_STORE_CTX *param_2)

{
  int iVar1;
  
  iVar1 = X509_STORE_CTX_get_error(param_2);
  return iVar1 != 10;
}



// === dtls_transport_genarate_key_init @ 00404644 ===

void dtls_transport_genarate_key_init(void)

{
  pthread_t apStack_10 [3];
  
  keyList = 0;
  DAT_00426ed4 = 0;
  DAT_00426ed8 = 0;
  DAT_00426edc = 0;
  DAT_00426ee0 = 0;
  DAT_00426ee4 = 0;
  DAT_00426ee8 = 0;
  DAT_00426eec = 0;
  DAT_00426ef0 = 0;
  DAT_00426ef4 = 0;
  pthread_create(apStack_10,(pthread_attr_t *)0x0,genarate_key,(void *)0x0);
  return;
}



// === generate_self_certificate @ 004046a0 ===

void generate_self_certificate(undefined4 *param_1)

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
  param_1[1] = pEVar1;
  if (pEVar1 == (EVP_PKEY *)0x0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0x8f);
    a = BN_new();
  }
  else {
    a = BN_new();
  }
  if (a == (BIGNUM *)0x0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0x93);
  }
  iVar2 = BN_set_word(a,0x10001);
  if (iVar2 == 0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0x97);
    rsa = RSA_new();
  }
  else {
    rsa = RSA_new();
  }
  if (rsa == (RSA *)0x0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0x9c);
  }
  iVar2 = RSA_generate_key_ex(rsa,0x800,a,(BN_GENCB *)0x0);
  if (iVar2 == 0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xa0);
    pEVar1 = (EVP_PKEY *)param_1[1];
  }
  else {
    pEVar1 = (EVP_PKEY *)param_1[1];
  }
  iVar2 = EVP_PKEY_assign(pEVar1,6,rsa);
  if (iVar2 == 0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xa4);
    pXVar3 = X509_new();
    *param_1 = pXVar3;
  }
  else {
    pXVar3 = X509_new();
    *param_1 = pXVar3;
  }
  if (pXVar3 == (X509 *)0x0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xab);
    pXVar3 = (X509 *)*param_1;
  }
  X509_set_version(pXVar3,2);
  pAVar4 = (ASN1_TIME *)X509_getm_notBefore(*param_1);
  X509_gmtime_adj(pAVar4,-0x1e13380);
  pAVar4 = (ASN1_TIME *)X509_getm_notAfter(*param_1);
  X509_gmtime_adj(pAVar4,0x1e13380);
  iVar2 = X509_set_pubkey((X509 *)*param_1,(EVP_PKEY *)param_1[1]);
  if (iVar2 == 0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xb5);
    name = X509_get_subject_name((X509 *)*param_1);
  }
  else {
    name = X509_get_subject_name((X509 *)*param_1);
  }
  if (name == (X509_NAME *)0x0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xba);
  }
  X509_NAME_add_entry_by_txt(name,"O",0x1001,"Test",-1,-1,0);
  X509_NAME_add_entry_by_txt(name,"CN",0x1001,"Test",-1,-1,0);
  iVar2 = X509_set_issuer_name((X509 *)*param_1,name);
  if (iVar2 == 0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xc0);
    pXVar3 = (X509 *)*param_1;
  }
  else {
    pXVar3 = (X509 *)*param_1;
  }
  pEVar1 = (EVP_PKEY *)param_1[1];
  md = EVP_sha1();
  iVar2 = X509_sign(pXVar3,pEVar1,md);
  if (iVar2 == 0) {
    hs_log_push(0,"%s:%d","generate_self_certificate",0xc4);
  }
  BN_free(a);
  return;
}



// === genarate_key @ 004049e4 ===

void genarate_key(void)

{
  pthread_t __th;
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 *puVar4;
  int iVar5;
  
  __th = pthread_self();
  puVar4 = &keyList;
  iVar5 = 0;
  pthread_detach(__th);
  do {
    hs_log_push(1,"genarate_key i:%d %x",iVar5,puVar4);
    generate_self_certificate(puVar4);
    g_mutex_lock(&listMutex);
    iVar5 = iVar5 + 1;
    prepareList = g_slist_append(prepareList,puVar4);
    puVar4 = puVar4 + 2;
    g_mutex_unlock(&listMutex);
  } while (iVar5 != 5);
  do {
    g_mutex_lock(&listMutex);
    iVar5 = g_slist_length(nullList);
    if (iVar5 == 0) {
LAB_00404aa0:
      g_mutex_unlock(&listMutex);
    }
    else {
      uVar1 = g_slist_length(nullList);
      uVar2 = g_slist_length(prepareList);
      hs_log_push(1,"nullkey:%d,preparedkey:%d ",uVar1,uVar2);
      piVar3 = (int *)g_slist_nth(nullList,0);
      iVar5 = *piVar3;
      hs_log_push(1,"nullkey remove:%x ",iVar5);
      nullList = g_slist_remove(nullList,iVar5);
      g_mutex_unlock(&listMutex);
      if (iVar5 != 0) {
        generate_self_certificate(iVar5);
        g_mutex_lock(&listMutex);
        prepareList = g_slist_append(prepareList,iVar5);
        goto LAB_00404aa0;
      }
    }
    sleep(10);
  } while( true );
}



// === setDtlsTransportKey @ 00404b58 ===

void setDtlsTransportKey(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (param_1 == 0) {
    return;
  }
  g_mutex_lock(&listMutex);
  uVar1 = g_slist_length(prepareList);
  hs_log_push(1,"setDtlsTransportKey preparedkey:%d ",uVar1);
  iVar2 = g_slist_length(prepareList);
  if (iVar2 != 0) {
    puVar3 = (undefined4 *)g_slist_nth(prepareList,0);
    puVar3 = (undefined4 *)*puVar3;
    prepareList = g_slist_remove(prepareList,puVar3);
    uVar1 = puVar3[1];
    *(undefined4 *)(param_1 + 8) = *puVar3;
    *(undefined4 *)(param_1 + 0xc) = uVar1;
    hs_log_push(1,"nullList add:%x ",puVar3);
    nullList = g_slist_append(nullList,puVar3);
    g_mutex_unlock(&listMutex);
    return;
  }
  g_mutex_unlock(&listMutex);
  generate_self_certificate(&local_20);
  *(undefined4 *)(param_1 + 0xc) = local_1c;
  *(undefined4 *)(param_1 + 8) = local_20;
  return;
}



// === dtls_transport_init @ 00404c74 ===

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
  uchar *puVar3;
  X509 *data;
  uchar *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uchar local_68 [64];
  uchar *local_28 [3];
  
  meth = (SSL_METHOD *)DTLS_method();
  ctx = SSL_CTX_new(meth);
  param_1[1] = ctx;
  SSL_CTX_set_verify(ctx,3,cb_dtls_verify);
  SSL_CTX_set_tlsext_use_srtp((SSL_CTX *)param_1[1],"SRTP_AES128_CM_SHA1_80");
  setDtlsTransportKey(param_1);
  iVar1 = SSL_CTX_use_certificate((SSL_CTX *)param_1[1],(X509 *)param_1[2]);
  if (iVar1 == 0) {
    hs_log_push(0,"use certificate failed");
    uVar5 = 0xffffffff;
  }
  else {
    iVar1 = SSL_CTX_use_PrivateKey((SSL_CTX *)param_1[1],(EVP_PKEY *)param_1[3]);
    if (iVar1 == 0) {
      hs_log_push(0,"use private key failed");
      uVar5 = 0xffffffff;
    }
    else {
      iVar1 = SSL_CTX_check_private_key((SSL_CTX *)param_1[1]);
      if (iVar1 == 0) {
        hs_log_push(0,"check preverify key failed");
        uVar5 = 0xffffffff;
      }
      else {
        SSL_CTX_ctrl((SSL_CTX *)param_1[1],0x29,1,(void *)0x0);
        data = (X509 *)param_1[2];
        type = EVP_sha256();
        iVar1 = X509_digest(data,type,local_68,(uint *)local_28);
        if (iVar1 == 0) {
          hs_log_push(0,"generate fingerprint failed");
          uVar5 = 0xffffffff;
        }
        else {
          puVar6 = param_1 + 0x36;
          if (local_28[0] != (uchar *)0x0) {
            puVar4 = local_68;
            iVar1 = 1 - (int)puVar4;
            do {
              g_snprintf(puVar6,4,&DAT_0040ef68,*puVar4);
              puVar3 = puVar4 + iVar1;
              puVar6 = (undefined4 *)((int)puVar6 + 3);
              puVar4 = puVar4 + 1;
            } while (puVar3 < local_28[0]);
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
            hs_log_push(0,"New ecdh curve by name failed");
            uVar5 = 0xffffffff;
          }
          else {
            SSL_set_options(*param_1,0x2020000);
            SSL_ctrl((SSL *)*param_1,4,0,key);
            EC_KEY_free(key);
            param_1[0x5e] = 0;
            param_1[0x5f] = 0;
            param_1[0x60] = 0;
            iVar1 = srtp_init();
            uVar5 = 0;
            if (iVar1 != 0) {
              hs_log_push(0,"libsrtp init failed\r\n");
            }
          }
        }
      }
    }
  }
  return uVar5;
}



// === dtls_transport_create @ 00404ecc ===

void * dtls_transport_create(undefined4 param_1)

{
  void *pvVar1;
  
  pvVar1 = calloc(1,0x184);
  if (pvVar1 != (void *)0x0) {
    dtls_transport_init(pvVar1,param_1);
  }
  return pvVar1;
}



// === dtls_transport_destroy @ 00404f18 ===

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



// === dtls_transport_do_handshake @ 00404f98 ===

void dtls_transport_do_handshake(undefined4 *param_1)

{
  pthread_t pVar1;
  
  pVar1 = pthread_self();
  hs_log_push(2,"handshake thread id:%x",pVar1);
  if (param_1[0x5f] == 0) {
    if (param_1[0x60] == 0) {
      param_1[0x60] = 1;
      SSL_set_accept_state((SSL *)*param_1);
      SSL_do_handshake((SSL *)*param_1);
      param_1[0x5e] = 1;
      return;
    }
    param_1[0x60] = 2;
  }
  return;
}



// === dtls_transport_validate @ 00405024 ===

bool dtls_transport_validate(byte *param_1)

{
  if (param_1 != (byte *)0x0) {
    return *param_1 - 0x13 < 0x2e;
  }
  return false;
}



// === dtls_transport_get_srtp_initialized @ 00405044 ===

undefined4 dtls_transport_get_srtp_initialized(int param_1)

{
  if (param_1 != 0) {
    return *(undefined4 *)(param_1 + 0x17c);
  }
  return 0;
}



// === dtls_transport_incomming_msg @ 0040505c ===

void dtls_transport_incomming_msg(undefined4 *param_1,void *param_2,int param_3)

{
  pthread_t pVar1;
  int iVar2;
  X509 *data;
  EVP_MD *type;
  ulong uVar3;
  char *pcVar4;
  uchar *puVar5;
  uchar *md;
  uchar **ppuVar6;
  undefined1 auStack_d08 [3000];
  uchar *local_150;
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  undefined4 local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined2 local_124;
  undefined4 local_122;
  undefined4 local_11e;
  undefined4 local_11a;
  undefined2 local_116;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined2 local_6c;
  uchar *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined2 local_2c;
  
  pVar1 = pthread_self();
  hs_log_push(2,"incomming_msg thread id:%x",pVar1);
  if (param_1[0x5f] == 0) {
    iVar2 = BIO_write((BIO *)param_1[4],param_2,param_3);
    if (param_3 == iVar2) {
      iVar2 = param_1[0x5e];
    }
    else {
      hs_log_push(0,"%s:%d","dtls_transport_incomming_msg",0x153);
      iVar2 = param_1[0x5e];
    }
    if (iVar2 != 0) {
      memset(auStack_d08,0,3000);
      iVar2 = SSL_read((SSL *)*param_1,auStack_d08,3000);
      if ((iVar2 < 0) && (iVar2 = SSL_get_error((SSL *)*param_1,iVar2), iVar2 == 1)) {
        uVar3 = ERR_get_error();
        ERR_error_string_n(uVar3,(char *)&local_150,200);
        hs_log_push(0,"%s",&local_150);
      }
      iVar2 = SSL_is_init_finished(*param_1);
      if (iVar2 != 0) {
        data = SSL_get_peer_certificate((SSL *)*param_1);
        if (data == (X509 *)0x0) {
          uVar3 = ERR_get_error();
          pcVar4 = ERR_reason_error_string(uVar3);
          hs_log_push(0,"%s",pcVar4);
        }
        else {
          type = EVP_sha256();
          md = (uchar *)&local_88;
          X509_digest(data,type,md,(uint *)&local_48);
          X509_free(data);
          ppuVar6 = &local_150;
          if (local_48 != (uchar *)0x0) {
            iVar2 = 1 - (int)md;
            do {
              g_snprintf(ppuVar6,4,&DAT_0040ef68,*md);
              puVar5 = md + iVar2;
              ppuVar6 = (uchar **)((int)ppuVar6 + 3);
              md = md + 1;
            } while (puVar5 < local_48);
          }
          *(undefined1 *)((int)ppuVar6 + -1) = 0;
          hs_log_push(2,"Remote fingerprint %s",&local_150);
          hs_log_push(2,"Local fingerprint %s",param_1 + 0x36);
        }
        memset(param_1 + 6,0,0x5c);
        memset(param_1 + 0x1d,0,0x5c);
        iVar2 = SSL_export_keying_material
                          ((SSL *)*param_1,(uchar *)&local_150,0x3c,"EXTRACTOR-dtls_srtp",0x13,
                           (uchar *)0x0,0,0);
        if (iVar2 == 0) {
          uVar3 = ERR_get_error();
          pcVar4 = ERR_reason_error_string(uVar3);
          hs_log_push(0,"Couldn\'t extract SRTP keying material(%s)",pcVar4);
        }
        srtp_crypto_policy_set_rtp_default(param_1 + 8);
        srtp_crypto_policy_set_rtcp_default(param_1 + 0xe);
        local_48 = local_150;
        local_3c = local_144;
        param_1[6] = 2;
        param_1[0x14] = &local_48;
        param_1[0x1c] = 0;
        local_44 = local_14c;
        local_40 = local_148;
        local_38 = local_130;
        local_34 = local_12c;
        local_30 = local_128;
        local_2c = local_124;
        srtp_crypto_policy_set_rtp_default(param_1 + 0x1f);
        srtp_crypto_policy_set_rtcp_default(param_1 + 0x25);
        local_88 = local_140;
        local_84 = local_13c;
        local_80 = local_138;
        local_7c = local_134;
        param_1[0x1d] = 3;
        param_1[0x2b] = &local_88;
        param_1[0x33] = 0;
        local_78 = local_122;
        local_74 = local_11e;
        local_70 = local_11a;
        local_6c = local_116;
        iVar2 = srtp_create(param_1 + 0x34,param_1 + 6);
        if (iVar2 != 0) {
          hs_log_push(0,"Error creating inbound SRTP session for component");
        }
        hs_log_push(2,"Created inbound SRTP session");
        iVar2 = srtp_create(param_1 + 0x35,param_1 + 0x1d);
        if (iVar2 != 0) {
          hs_log_push(0,"Error creating outbound SRTP session");
        }
        hs_log_push(2,"Created outbound SRTP session");
        param_1[0x5f] = 1;
      }
    }
  }
  return;
}



// === dtls_transport_decrypt_rtp_packet @ 00405468 ===

void dtls_transport_decrypt_rtp_packet(int param_1)

{
  if (param_1 != 0) {
    srtp_unprotect(*(undefined4 *)(param_1 + 0xd0));
    return;
  }
  return;
}



// === dtls_transport_decrypt_rtcp_packet @ 00405480 ===

void dtls_transport_decrypt_rtcp_packet(int param_1)

{
  if (param_1 != 0) {
    srtp_unprotect_rtcp(*(undefined4 *)(param_1 + 0xd0));
    return;
  }
  return;
}



// === dtls_transport_encrypt_rtp_packet @ 00405498 ===

void dtls_transport_encrypt_rtp_packet(int param_1)

{
  if (param_1 != 0) {
    srtp_protect(*(undefined4 *)(param_1 + 0xd4));
    return;
  }
  return;
}



// === dtls_transport_encrypt_rctp_packet @ 004054b0 ===

void dtls_transport_encrypt_rctp_packet(int param_1)

{
  if (param_1 != 0) {
    srtp_protect_rtcp(*(undefined4 *)(param_1 + 0xd4));
    return;
  }
  return;
}



// === dtls_transport_get_fingerprint @ 004054c8 ===

int dtls_transport_get_fingerprint(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0xd8;
  if (param_1 == 0) {
    iVar1 = 0;
  }
  return iVar1;
}



// === peer_connection_enable_mdns @ 00406ff0 ===

void peer_connection_enable_mdns(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x5c) = param_2;
  return;
}



// === session_description_update_break_lines @ 00407ea4 ===

undefined4 session_description_update_break_lines(int param_1,char *param_2)

{
  undefined4 uVar1;
  char *pcVar2;
  
  if (param_1 != 0) {
    if (*(void **)(param_1 + 0x2804) == (void *)0x0) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = 0xffffffff;
      if (param_2 != (char *)0x0) {
        free(*(void **)(param_1 + 0x2804));
        pcVar2 = strdup(param_2);
        *(char **)(param_1 + 0x2804) = pcVar2;
        uVar1 = 0;
      }
    }
    return uVar1;
  }
  return 0xffffffff;
}



// === session_description_update_mdns_of_candidate @ 00407f0c ===

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



// === signaling_create @ 00408640 ===

void * signaling_create(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  void *__ptr;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 local_res0 [4];
  
  local_res0[0] = param_1;
  local_res0[1] = param_2;
  local_res0[2] = param_3;
  local_res0[3] = param_4;
  __ptr = calloc(1,0x278);
  dtls_transport_genarate_key_init();
  if (__ptr != (void *)0x0) {
    puVar3 = (undefined4 *)register0x00000074;
    puVar1 = (undefined4 *)((int)__ptr + 0x160);
    do {
      puVar5 = puVar1;
      puVar2 = puVar3;
      uVar8 = puVar2[1];
      uVar7 = puVar2[2];
      uVar6 = puVar2[3];
      puVar3 = puVar2 + 4;
      *puVar5 = *puVar2;
      puVar5[1] = uVar8;
      puVar5[2] = uVar7;
      puVar5[3] = uVar6;
      puVar1 = puVar5 + 4;
    } while (puVar3 != (undefined4 *)&stack0x00000100);
    uVar7 = puVar2[5];
    uVar6 = puVar2[6];
    puVar5[4] = *puVar3;
    puVar5[5] = uVar7;
    puVar5[6] = uVar6;
    if (*(int *)((int)__ptr + 0x160) == 0) {
      iVar4 = signaling_http_create
                        ((int)__ptr + 0x164,*(undefined2 *)((int)__ptr + 0x264),(int)__ptr + 0x1e4,
                         *(undefined4 *)((int)__ptr + 0x268),(int)__ptr + 0x26c);
      *(int *)((int)__ptr + 0x274) = iVar4;
    }
    else if (*(int *)((int)__ptr + 0x160) == 1) {
      iVar4 = signaling_wsocket_create
                        ((int)__ptr + 0x164,*(undefined2 *)((int)__ptr + 0x264),(int)__ptr + 0x1e4,
                         *(undefined4 *)((int)__ptr + 0x268),(int)__ptr + 0x26c);
      *(int *)((int)__ptr + 0x274) = iVar4;
    }
    else {
      iVar4 = *(int *)((int)__ptr + 0x274);
    }
    if (iVar4 == 0) {
      free(__ptr);
      __ptr = (void *)0x0;
    }
  }
  return __ptr;
}



// === signaling_destroy @ 0040874c ===

void signaling_destroy(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 0) {
    signaling_http_destroy(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_destroy(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_dispatch @ 00408778 ===

void signaling_dispatch(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 0) {
    signaling_http_dispatch(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_dispatch(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_shutdown @ 004087a4 ===

void signaling_shutdown(int param_1)

{
  if (*(int *)(param_1 + 0x160) == 0) {
    signaling_http_shutdown(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_shutdown(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === signaling_on_call_event @ 004087d0 ===

void signaling_on_call_event(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x26c) = param_2;
  *(undefined4 *)(param_1 + 0x270) = param_3;
  return;
}



// === signaling_send_answer_to_call @ 004087dc ===

void signaling_send_answer_to_call(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (*(int *)(param_1 + 0x160) == 0) {
    signaling_http_set_answer(*(undefined4 *)(param_1 + 0x274),param_3);
    return;
  }
  if (*(int *)(param_1 + 0x160) == 1) {
    signaling_wsocket_set_answer(*(undefined4 *)(param_1 + 0x274));
    return;
  }
  return;
}



// === hs_stream_begin_token @ 00408aa4 ===

void hs_stream_begin_token(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x28) = param_2;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x18);
  return;
}



// === hs_stream_current_token @ 00408b68 ===

undefined4 * hs_stream_current_token(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_2 + 0x24);
  uVar1 = *(undefined4 *)(param_2 + 0x28);
  *param_1 = *(undefined4 *)(param_2 + 0x20);
  param_1[1] = uVar2;
  param_1[2] = uVar1;
  return param_1;
}



// === http_token_dyn_push @ 00409648 ===

void http_token_dyn_push(undefined4 *param_1,undefined4 param_2,undefined4 param_3,
                        undefined4 param_4)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  
  iVar3 = param_1[2];
  if (iVar3 != param_1[1]) {
    puVar1 = (undefined4 *)(iVar3 * 0xc + (int)*param_1);
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    param_1[2] = iVar3 + 1;
    return;
  }
  param_1[1] = iVar3 * 2;
  pvVar2 = realloc((void *)*param_1,iVar3 * 0x18);
  *param_1 = pvVar2;
  if (pvVar2 != (void *)0x0) {
    iVar3 = param_1[2];
    puVar1 = (undefined4 *)(iVar3 * 0xc + (int)pvVar2);
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    param_1[2] = iVar3 + 1;
    return;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("dyn->buf != NULL","include/httpserver.h",0x3ea,"http_token_dyn_push");
}



// === http_token_dyn_init @ 00409730 ===

void http_token_dyn_init(undefined4 *param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = malloc(param_2 * 0xc);
  *param_1 = pvVar1;
  if (pvVar1 != (void *)0x0) {
    param_1[1] = param_2;
    param_1[2] = 0;
    return;
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail("dyn->buf != NULL","include/httpserver.h",0x3f2,"http_token_dyn_init");
}



// === http_get_token_string @ 00409c90 ===

void http_get_token_string(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar2 = *(int **)(param_2 + 0x70);
  if ((piVar2 != (int *)0x0) && (0 < *(int *)(param_2 + 0x78))) {
    iVar4 = *piVar2;
    iVar5 = piVar2[1];
    iVar3 = 0;
    if (param_3 == piVar2[2]) {
      iVar3 = *(int *)(param_2 + 0x18);
    }
    else {
      do {
        iVar3 = iVar3 + 1;
        if (iVar3 == *(int *)(param_2 + 0x78)) goto LAB_00409cec;
        iVar4 = piVar2[3];
        iVar5 = piVar2[4];
        piVar1 = piVar2 + 5;
        piVar2 = piVar2 + 3;
      } while (param_3 != *piVar1);
      iVar3 = *(int *)(param_2 + 0x18);
    }
    param_1[1] = iVar5;
    *param_1 = iVar3 + iVar4;
    return;
  }
LAB_00409cec:
  *param_1 = 0;
  param_1[1] = 0;
  return;
}



// === hs_assign_iteration_headers @ 00409efc ===

undefined4 hs_assign_iteration_headers(int param_1,int *param_2,int *param_3,int *param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x70);
  piVar1 = (int *)(*param_4 * 0xc + iVar5);
  if (piVar1[2] != 7) {
    iVar3 = *(int *)(param_1 + 0x18);
    iVar4 = *piVar1;
    param_2[1] = piVar1[1];
    iVar2 = *param_4;
    *param_2 = iVar3 + iVar4;
    *param_4 = iVar2 + 1;
    piVar1 = (int *)((iVar2 + 1) * 0xc + iVar5);
    iVar5 = piVar1[1];
    *param_3 = iVar3 + *piVar1;
    param_3[1] = iVar5;
    return 1;
  }
  return 0;
}



// === signaling_http_get_answer @ 0040b38c ===

size_t signaling_http_get_answer(int param_1,char *param_2,size_t param_3)

{
  size_t sVar1;
  char *__s;
  
  memset(param_2,0,param_3);
  __s = *(char **)(param_1 + 0x88);
  if (__s != (char *)0x0) {
    sVar1 = strlen(__s);
    snprintf(param_2,param_3,"%s",__s);
    free(*(void **)(param_1 + 0x88));
    *(undefined4 *)(param_1 + 0x88) = 0;
    return sVar1;
  }
  snprintf(param_2,param_3,"{}");
  sVar1 = strlen(param_2);
  return sVar1;
}



// === signaling_http_set_answer @ 0040b448 ===

void signaling_http_set_answer(int param_1,undefined4 param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  char acStack_2810 [10244];
  
  memset(acStack_2810,0,0x2800);
  snprintf(acStack_2810,0x2800,"{\"type\": \"answer\", \"sdp\": \"%s\"}",param_2);
  if (*(void **)(param_1 + 0x88) != (void *)0x0) {
    free(*(void **)(param_1 + 0x88));
  }
  sVar1 = strlen(acStack_2810);
  uVar2 = g_base64_encode(acStack_2810,sVar1);
  *(undefined4 *)(param_1 + 0x88) = uVar2;
  return;
}



// === signaling_http_call_request @ 0040b4c8 ===

void signaling_http_call_request(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  void *__ptr;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_res8 [2];
  
  local_res8[0] = param_3;
  __ptr = (void *)g_base64_decode(param_2,local_res8);
  if ((__ptr != (void *)0x0) && (iVar1 = cJSON_Parse(__ptr), iVar1 != 0)) {
    iVar2 = cJSON_GetObjectItemCaseSensitive(iVar1,&DAT_0040fcec);
    iVar3 = cJSON_IsString(iVar2);
    if ((iVar3 != 0) && (*(int *)(iVar2 + 0x10) != 0)) {
      iVar3 = cJSON_GetObjectItemCaseSensitive(iVar1,&DAT_0040fcf4);
      iVar4 = cJSON_IsString(iVar3);
      if (((iVar4 != 0) && (iVar3 = *(int *)(iVar3 + 0x10), iVar3 != 0)) &&
         (iVar2 = strcmp(*(char **)(iVar2 + 0x10),"offer"), iVar2 == 0)) {
        signaling_observer_notify_event(param_1,0,&DAT_0040fd00,iVar3);
      }
    }
    cJSON_Delete(iVar1);
    free(__ptr);
  }
  return;
}



// === signaling_http_handle_request @ 0040b5cc ===

void signaling_http_handle_request(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  size_t sVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  char *pcVar9;
  size_t sVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined1 auStack_2830 [10240];
  char *local_30;
  size_t local_2c;
  
  puVar11 = *(undefined4 **)(*(int *)(param_1 + 0x6c) + 0x38);
  iVar3 = http_response_init();
  *(undefined4 *)(iVar3 + 0xc) = 200;
  http_response_header(iVar3,"Access-Control-Allow-Origin","*");
  http_response_header
            (iVar3,"Access-Control-Allow-Headers",
             "DNT,X-CustomHeader,Keep-Alive,User-Agent,X-Requested-With,If-Modified-Since,Cache-Control,Content-Type,Sample-Source"
            );
  piVar8 = *(int **)(param_1 + 0x70);
  pcVar9 = (char *)(puVar11 + 1);
  if ((piVar8 == (int *)0x0) || (iVar14 = *(int *)(param_1 + 0x78), iVar14 < 1)) {
    sVar10 = strlen(pcVar9);
    if (sVar10 != 0) goto LAB_0040b784;
    iVar12 = 0;
    sVar10 = 0;
  }
  else {
    iVar12 = *piVar8;
    sVar10 = piVar8[1];
    iVar13 = piVar8[2];
    sVar4 = sVar10;
    iVar7 = iVar12;
    if (iVar13 != 2) {
      iVar6 = 0;
      piVar2 = piVar8;
      do {
        iVar6 = iVar6 + 1;
        if (iVar6 == iVar14) {
          sVar4 = strlen(pcVar9);
          if (sVar4 == 0) goto LAB_0040b6bc;
          goto LAB_0040b784;
        }
        iVar7 = piVar2[3];
        sVar4 = piVar2[4];
        piVar1 = piVar2 + 5;
        piVar2 = piVar2 + 3;
      } while (*piVar1 != 2);
    }
    iVar6 = *(int *)(param_1 + 0x18);
    local_30 = pcVar9;
    local_2c = sVar4;
    sVar4 = strlen(pcVar9);
    if ((local_2c != sVar4) ||
       (iVar7 = memcmp((void *)(iVar6 + iVar7),local_30,local_2c), iVar7 != 0)) {
LAB_0040b784:
      http_response_header(iVar3,"Content-Type","text/html");
      pcVar9 = (char *)puVar11[0x23];
      if (pcVar9 == (char *)0x0) {
        *(char **)(iVar3 + 4) = "";
        *(undefined4 *)(iVar3 + 8) = 0;
      }
      else {
        sVar10 = strlen(pcVar9);
        *(size_t *)(iVar3 + 8) = sVar10;
        *(char **)(iVar3 + 4) = pcVar9;
      }
      goto LAB_0040b7b4;
    }
LAB_0040b6bc:
    if (iVar13 != 7) {
      iVar7 = 0;
      do {
        iVar7 = iVar7 + 1;
        sVar10 = 0;
        if (iVar7 == iVar14) {
          iVar12 = 0;
          goto LAB_0040b6f8;
        }
        iVar12 = piVar8[3];
        sVar10 = piVar8[4];
        piVar2 = piVar8 + 5;
        piVar8 = piVar8 + 3;
      } while (*piVar2 != 7);
    }
    iVar12 = *(int *)(param_1 + 0x18) + iVar12;
  }
LAB_0040b6f8:
  signaling_http_call_request(*puVar11,iVar12,sVar10);
  http_response_header(iVar3,"Content-Type","text/plain");
  memset(auStack_2830,0,0x2800);
  uVar5 = signaling_http_get_answer(puVar11,auStack_2830,0x2800);
  *(undefined4 *)(iVar3 + 8) = uVar5;
  *(undefined1 **)(iVar3 + 4) = auStack_2830;
LAB_0040b7b4:
  http_respond(param_1,iVar3);
  return;
}



// === signaling_http_create @ 0040b828 ===

undefined4 *
signaling_http_create
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = malloc(0x90);
  if (puVar1 != (undefined4 *)0x0) {
    snprintf((char *)(puVar1 + 1),0x80,"/call/%s",param_3);
    puVar1[0x23] = param_4;
    puVar1[0x22] = 0;
    iVar2 = http_server_init(param_2,signaling_http_handle_request);
    puVar1[0x21] = iVar2;
    *(undefined4 **)(iVar2 + 0x38) = puVar1;
    *puVar1 = param_5;
  }
  return puVar1;
}



// === signaling_http_destroy @ 0040b8bc ===

void signaling_http_destroy(void *param_1)

{
  if (param_1 != (void *)0x0) {
    if (*(void **)((int)param_1 + 0x84) != (void *)0x0) {
      free(*(void **)((int)param_1 + 0x84));
    }
    if (*(void **)((int)param_1 + 0x88) != (void *)0x0) {
      free(*(void **)((int)param_1 + 0x88));
    }
    free(param_1);
    return;
  }
  return;
}



// === signaling_http_dispatch @ 0040b914 ===

void signaling_http_dispatch(int param_1)

{
  http_server_listen(*(undefined4 *)(param_1 + 0x84));
  return;
}



// === signaling_http_shutdown @ 0040b928 ===

void signaling_http_shutdown(void)

{
  return;
}



// === signaling_observer_notify_event @ 0040b930 ===

void signaling_observer_notify_event
               (undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 0) {
    if ((code *)*param_1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0040b968. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)*param_1)(0,param_4);
      return;
    }
  }
  else if ((param_2 == 2) && ((code *)*param_1 != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0040b94c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)*param_1)(2,param_4);
    return;
  }
  return;
}



// === update_icesig @ 0040b99c ===

void update_icesig(int param_1)

{
  hs_log_push(1,"update_icesig:%d for %d\r\n",param_1,m_ice_sig);
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



// === update_ice_server @ 0040ba88 ===

undefined4 update_ice_server(char *param_1,int param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  long lVar3;
  time_t tVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  char *__s;
  undefined4 uVar7;
  
  uVar5 = *(undefined4 *)(param_2 + 0x10);
  uVar6 = *(undefined4 *)(param_3 + 0x10);
  iVar1 = cJSON_IsString(param_2);
  if (iVar1 != 0) {
    __s = *(char **)(param_2 + 0x10);
    pcVar2 = strchr(__s,0x3a);
    hs_log_push(1,"###username %s\n",__s);
    if (pcVar2 != (char *)0x0) {
      tVar4 = time((time_t *)0x0);
      pcVar2 = *(char **)(param_2 + 0x10);
      iVar1 = get_webrtc_data();
      iVar1 = *(int *)(iVar1 + 4);
      lVar3 = strtol(pcVar2,(char **)0x0,10);
      *(long *)(iVar1 + 8) = lVar3;
      iVar1 = get_webrtc_data();
      uVar7 = *(undefined4 *)(*(int *)(iVar1 + 4) + 8);
      iVar1 = get_webrtc_data();
      hs_log_push(1,"ice_tm_tv %u, now:%u\n left:%d",uVar7,tVar4,
                  *(int *)(*(int *)(iVar1 + 4) + 8) - tVar4);
    }
  }
  iVar1 = cJSON_IsString(param_3);
  if (iVar1 != 0) {
    hs_log_push(1,"###credential %s\n",*(undefined4 *)(param_3 + 0x10));
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
    set_stun_server(param_1,lVar3,uVar5,uVar6);
    hs_log_push(1,"###iceServer %s portNum:%d\n",param_1,lVar3);
  }
  return 0;
}



// === signaling_ws_thd @ 0040c18c ===

undefined4 signaling_ws_thd(int param_1)

{
  pthread_t __th;
  uint __seed;
  int iVar1;
  time_t tVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_278 [4];
  undefined1 *local_274;
  undefined4 local_248;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_c0;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_b4;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  char *local_a4;
  char *local_78;
  timespec local_3c;
  timespec local_34;
  
  __th = pthread_self();
  pthread_detach(__th);
  if ((globalsn == 0) || (globalmodel == 0)) {
    GetRegisterInfoFromFile_part_1();
  }
  __seed = time((time_t *)0x0);
  srandom(__seed);
  lws_set_log_level(0x40f,log_callback);
  memset(auStack_278,0,0x1b8);
  local_248 = 0xffffffff;
  local_160 = 0x1000;
  local_15c = 0;
  local_274 = protocols;
  if (*(int *)(param_1 + 0x14) == 0) {
    hs_log_push(0,"lws init failed\n");
    return 0;
  }
  hs_log_push(1,"signaling_ws_thd start : %d\r\n",interrupted);
  iVar3 = 0;
  do {
    while (interrupted == 0) {
LAB_0040c388:
      iVar1 = lws_service(*(undefined4 *)(param_1 + 0x14),0);
      if (iVar1 < 0) {
        hs_log_push(0,"##OOOO -- exiting service loop. n = %d, interrupted = %d\n",iVar1);
        lws_context_destroy(*(undefined4 *)(param_1 + 0x14));
        return 0;
      }
    }
    while( true ) {
      clock_gettime(1,&local_34);
      local_3c.tv_sec = local_34.tv_sec + 0xf;
      local_3c.tv_nsec = local_34.tv_nsec;
      hs_log_push(1,"signaling_ws_thd wait\r\n");
      iVar1 = get_webrtc_data();
      pthread_mutex_lock((pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114));
      iVar1 = get_webrtc_data();
      iVar4 = *(int *)(iVar1 + 4);
      iVar1 = get_webrtc_data();
      pthread_cond_timedwait
                ((pthread_cond_t *)(iVar4 + 0x130),(pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114),
                 &local_3c);
      iVar1 = get_webrtc_data();
      pthread_mutex_unlock((pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114));
      hs_log_push(1,"signaling_ws_thd wait end : %d\r\n",interrupted);
      iVar1 = get_webrtc_data();
      if (*(char *)(*(int *)(iVar1 + 4) + 0x14) == '\0') break;
      if (interrupted == 0) goto LAB_0040c388;
      iVar3 = iVar3 + 1;
      hs_log_push(1,"##try to reconnect %lu \r\n",iVar3);
      if (m_fir_ver == '\0') {
        get_ver_info_part_2();
      }
      memset(&local_c0,0,0x84);
      local_b4 = 0x19;
      local_b8 = *(int *)(m_ws_serv + 0x10);
      local_bc = *(undefined4 *)(m_ws_serv + 0xc);
      local_c0 = *(undefined4 *)(m_ws_serv + 0x14);
      if (local_b8 != 0x1bb) {
        local_b4 = 0;
      }
      local_b0 = *(int *)(m_ws_serv + 0x18) + 4;
      local_a4 = "lws-minimal";
      local_78 = "lws-minimal";
      local_ac = local_bc;
      local_a8 = local_bc;
      iVar1 = get_webrtc_data();
      **(undefined1 **)(iVar1 + 4) = 0;
      iVar1 = get_webrtc_data();
      iVar1 = *(int *)(iVar1 + 4);
      tVar2 = time((time_t *)0x0);
      *(time_t *)(iVar1 + 0x10) = tVar2;
      hs_log_push(1,"%s: connection %s:%d -> %s\n","connect_client",local_bc,local_b8,local_b0);
      iVar1 = lws_client_connect_via_info(&local_c0);
      if (iVar1 != 0) {
        hs_log_push(1,"lws_client_connect_via_info 1 \r\n");
        interrupted = 0;
        goto LAB_0040c388;
      }
      hs_log_push(1,"lws_client_connect_via_info 0 \r\n");
      interrupted = 1;
    }
  } while( true );
}



// === cxy_signal_start @ 0040c5e4 ===

undefined4 cxy_signal_start(void *param_1)

{
  int iVar1;
  pthread_condattr_t pStack_10;
  pthread_t pStack_c;
  
  pthread_condattr_setclock(&pStack_10,1);
  iVar1 = get_webrtc_data();
  pthread_cond_init((pthread_cond_t *)(*(int *)(iVar1 + 4) + 0x130),&pStack_10);
  pthread_condattr_destroy(&pStack_10);
  iVar1 = get_webrtc_data();
  pthread_mutex_init((pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114),(pthread_mutexattr_t *)0x0);
  interrupted = 1;
  pthread_create(&pStack_c,(pthread_attr_t *)0x0,signaling_ws_thd,param_1);
  return 0;
}



// === signaling_wsocket_call_request @ 0040c7a0 ===

void signaling_wsocket_call_request(undefined4 param_1,byte *param_2,size_t param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  time_t tVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  size_t sVar9;
  char *pcVar10;
  char acStack_c0 [128];
  byte *local_40 [2];
  undefined *local_38;
  undefined **local_34;
  undefined **local_30;
  int local_2c;
  
  local_38 = &DAT_00410d38;
  local_40[0] = (byte *)0x0;
  local_34 = &PTR_caseD_0_00410000;
  iVar2 = cJSON_ParseWithOpts(param_2,local_40,0);
  bVar1 = false;
  do {
    if (iVar2 == 0) {
      if (bVar1) {
LAB_0040c980:
        if (param_3 == 0) {
          return;
        }
        uVar8 = g_tmp_buf_idx + param_3;
        if (0x3bff < uVar8) {
          hs_log_push(0,"2 too big no space cur[%u] for cur_len: %d flush all\r\n",g_tmp_buf_idx,
                      param_3);
          g_tmp_buf_idx = 0;
          return;
        }
        g_tmp_buf_idx = uVar8;
        g_tmp_buf[uVar8] = 0;
        if (param_2 != g_tmp_buf) {
          memcpy(g_tmp_buf + uVar8,param_2,param_3);
          return;
        }
        return;
      }
      sVar9 = g_tmp_buf_idx + param_3;
      if (0x3bff < sVar9) {
        hs_log_push(0,"too big no space cur[%u] for cur_len: %d flush all\r\n",g_tmp_buf_idx,param_3
                   );
        g_tmp_buf_idx = 0;
        goto LAB_0040c980;
      }
      memcpy(g_tmp_buf + g_tmp_buf_idx,param_2,param_3);
      g_tmp_buf_idx = 0;
      g_tmp_buf[sVar9] = 0;
      bVar1 = true;
      param_2 = g_tmp_buf;
    }
    else {
      iVar3 = cJSON_GetObjectItem(iVar2,"action");
      if (((((iVar3 != 0) && (iVar4 = cJSON_IsString(iVar3), iVar4 != 0)) &&
           (pcVar10 = *(char **)(iVar3 + 0x10), pcVar10 != (char *)0x0)) &&
          (((iVar3 = cJSON_GetObjectItem(iVar2,&DAT_00410d30), iVar3 != 0 &&
            (iVar4 = cJSON_IsNumber(iVar3), iVar4 != 0)) &&
           ((*(int *)(iVar3 + 0x14) == 0 &&
            ((iVar3 = cJSON_GetObjectItem(iVar2,local_38), iVar3 != 0 &&
             (iVar4 = cJSON_IsString(iVar3), iVar4 != 0)))))))) &&
         (*(char **)(iVar3 + 0x10) != (char *)0x0)) {
        strcpy(acStack_c0,*(char **)(iVar3 + 0x10));
        iVar3 = strcmp(pcVar10,(char *)(local_34 + 0x350));
        if (iVar3 == 0) {
          update_icesig(1);
          iVar3 = get_webrtc_data();
          iVar3 = *(int *)(iVar3 + 4);
          tVar5 = time((time_t *)0x0);
          *(time_t *)(iVar3 + 0xc) = tVar5;
          iVar3 = get_webrtc_data();
          **(undefined1 **)(iVar3 + 4) = 1;
          hs_log_push(1,"join ack\r\n");
        }
        iVar3 = strcmp(pcVar10,"push_online");
        if (iVar3 == 0) {
          update_icesig(1);
          iVar3 = get_webrtc_data();
          **(undefined1 **)(iVar3 + 4) = 1;
          hs_log_push(1,"join success\r\n");
          iVar3 = cJSON_GetObjectItem(iVar2,"iceServers");
          if ((iVar3 != 0) && (iVar4 = cJSON_IsArray(iVar3), iVar4 != 0)) {
            uVar7 = cJSON_GetArraySize(iVar3);
            hs_log_push(1,"ObjArr Len: %d\n",uVar7);
            iVar3 = cJSON_GetArrayItem(iVar3,0);
            if (iVar3 != 0) {
              iVar4 = cJSON_GetObjectItem(iVar3,&DAT_00410d8c);
              uVar7 = *(undefined4 *)(iVar4 + 0x10);
              iVar4 = cJSON_GetObjectItem(iVar3,"username");
              local_30 = (undefined **)cJSON_GetObjectItem(iVar3,"credential");
              hs_log_push(1,"urls:%s username:%s credential:%s\n",uVar7,
                          *(undefined4 *)(iVar4 + 0x10),local_30[4]);
              update_ice_server(uVar7,iVar4,local_30);
            }
          }
        }
        else {
          iVar3 = strcmp(pcVar10,"ice_msg");
          if (((((iVar3 == 0) && (iVar3 = cJSON_GetObjectItem(iVar2,"sdpMessage"), iVar3 != 0)) &&
               (iVar4 = cJSON_IsObject(iVar3), iVar4 != 0)) &&
              ((iVar4 = cJSON_GetObjectItem(iVar3,&DAT_0040fcec), iVar4 != 0 &&
               (iVar6 = cJSON_IsString(iVar4), iVar6 != 0)))) &&
             ((pcVar10 = *(char **)(iVar4 + 0x10), pcVar10 != (char *)0x0 &&
              ((iVar3 = cJSON_GetObjectItem(iVar3,&DAT_00410de4), iVar3 != 0 &&
               (iVar4 = cJSON_IsObject(iVar3), iVar4 != 0)))))) {
            iVar4 = strcmp(pcVar10,"offer");
            if (iVar4 == 0) {
              iVar4 = cJSON_GetObjectItem(iVar2,"iceServers");
              if ((iVar4 != 0) && (iVar6 = cJSON_IsArray(iVar4), iVar6 != 0)) {
                uVar7 = cJSON_GetArraySize(iVar4);
                hs_log_push(1,"ObjArr Len: %d\n",uVar7);
                iVar4 = cJSON_GetArrayItem(iVar4,0);
                if (iVar4 != 0) {
                  iVar6 = cJSON_GetObjectItem(iVar4,&DAT_00410d8c);
                  local_30 = *(undefined ***)(iVar6 + 0x10);
                  iVar6 = cJSON_GetObjectItem(iVar4,"username");
                  local_2c = cJSON_GetObjectItem(iVar4,"credential");
                  hs_log_push(1,"urls:%s username:%s credential:%s\n",local_30,
                              *(undefined4 *)(iVar6 + 0x10),*(undefined4 *)(local_2c + 0x10));
                  update_ice_server(local_30,iVar6,local_2c);
                }
              }
              iVar3 = cJSON_GetObjectItem(iVar3,&DAT_0040fcf4);
              if ((iVar3 != 0) && (iVar4 = cJSON_IsString(iVar3), iVar4 != 0)) {
                signaling_observer_notify_event
                          (*m_signaling_wsocket,0,acStack_c0,*(undefined4 *)(iVar3 + 0x10));
              }
            }
            else {
              local_30 = &PTR_caseD_0_00410000;
              iVar4 = strcmp(pcVar10,"candidate");
              if (((iVar4 == 0) &&
                  (iVar3 = cJSON_GetObjectItem(iVar3,local_30 + -0x24e), iVar3 != 0)) &&
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
      sVar9 = param_3 - ((int)local_40[0] - (int)param_2);
      param_2 = local_40[0];
      while( true ) {
        if (sVar9 == 0) {
          g_tmp_buf_idx = 0;
          return;
        }
        if ((0x16 < (*param_2 - 10 & 0xff)) ||
           (-1 < (int)((0x400009U >> (*param_2 - 10 & 0x1f)) << 0x1f))) break;
        sVar9 = sVar9 - 1;
        param_2 = param_2 + 1;
      }
    }
    iVar2 = cJSON_ParseWithOpts(param_2,local_40,0);
    param_3 = sVar9;
  } while( true );
}



// === signaling_wsocket_create @ 0040ce08 ===

undefined4 *
signaling_wsocket_create
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  
  hs_log_push(1,"signaling_wsocket_create %s:%d\r\n",param_1,param_2);
  puVar1 = malloc(0x90);
  if (puVar1 != (undefined4 *)0x0) {
    snprintf((char *)(puVar1 + 1),0x80,"/api/cxy/ws/webrtc/signal/push/%s",param_3);
    puVar1[0x23] = param_4;
    puVar1[0x22] = 0;
    iVar2 = wsocket_init(param_1,param_2);
    puVar1[0x21] = iVar2;
    if (iVar2 != 0) {
      *(undefined4 **)(iVar2 + 0x18) = puVar1;
      m_ws_serv = iVar2;
      *puVar1 = param_5;
      m_signaling_wsocket = puVar1;
      return puVar1;
    }
  }
  return (undefined4 *)0x0;
}



// === signaling_wsocket_destroy @ 0040cef8 ===

void signaling_wsocket_destroy(void *param_1)

{
  if (param_1 != (void *)0x0) {
    hs_log_push(1,"signaling_wsocket_destroy\r\n");
    if (*(void **)((int)param_1 + 0x84) != (void *)0x0) {
      free(*(void **)((int)param_1 + 0x84));
    }
    if (*(void **)((int)param_1 + 0x88) != (void *)0x0) {
      free(*(void **)((int)param_1 + 0x88));
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
  return;
}



// === signaling_wsocket_dispatch @ 0040cf9c ===

undefined4 signaling_wsocket_dispatch(int param_1)

{
  int iVar1;
  void *__arg;
  pthread_condattr_t pStack_10;
  pthread_t pStack_c;
  
  __arg = *(void **)(param_1 + 0x84);
  pthread_condattr_setclock(&pStack_10,1);
  iVar1 = get_webrtc_data();
  pthread_cond_init((pthread_cond_t *)(*(int *)(iVar1 + 4) + 0x130),&pStack_10);
  pthread_condattr_destroy(&pStack_10);
  iVar1 = get_webrtc_data();
  pthread_mutex_init((pthread_mutex_t *)(*(int *)(iVar1 + 4) + 0x114),(pthread_mutexattr_t *)0x0);
  interrupted = 1;
  pthread_create(&pStack_c,(pthread_attr_t *)0x0,signaling_ws_thd,__arg);
  return 0;
}



// === signaling_wsocket_shutdown @ 0040cfa4 ===

void signaling_wsocket_shutdown(void)

{
  return;
}



// === signaling_wsocket_set_answer @ 0040d0ac ===

void signaling_wsocket_set_answer(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *pvVar4;
  int *piVar5;
  int *piVar6;
  char *pcVar7;
  int *piVar8;
  int iVar9;
  char *__haystack;
  
  uVar1 = cJSON_CreateObject();
  cJSON_AddStringToObject(uVar1,"action","ice_msg");
  cJSON_AddStringToObject(uVar1,&DAT_00410f00,*(undefined4 *)(param_2 + 0x2c));
  uVar2 = cJSON_CreateObject();
  uVar3 = cJSON_CreateObject();
  cJSON_AddStringToObject(uVar3,&DAT_0040fcec,"answer");
  cJSON_AddStringToObject(uVar2,&DAT_0040fcec,"answer");
  cJSON_AddStringToObject(uVar2,&DAT_0040fcf4,param_3);
  cJSON_AddItemToObject(uVar3,&DAT_00410de4,uVar2);
  cJSON_AddItemToObject(uVar1,"sdpMessage",uVar3);
  pvVar4 = (void *)cJSON_Print(uVar1);
  hs_log_push(1,"generate answer,and candidate:\n");
  cJSON_Delete(uVar1);
  piVar5 = (int *)create_ice_send_buf(pvVar4);
  if (piVar5 != (int *)0x0) {
    g_mutex_lock(param_2 + 0xc);
    piVar6 = *(int **)(param_2 + 0x28);
    *(int **)(param_2 + 0x28) = piVar5;
    *piVar5 = param_2 + 0x24;
    piVar5[1] = (int)piVar6;
    *piVar6 = (int)piVar5;
    g_mutex_unlock(param_2 + 0xc);
  }
  free(pvVar4);
  iVar9 = *(int *)(param_2 + 0x6c);
  *(undefined4 *)(param_2 + 0x30) = 6;
  if ((iVar9 != 0) && (*(char *)(iVar9 + 4) != '\0')) {
    piVar5 = (int *)g_strsplit(iVar9 + 4,"\r\n",0x100);
    __haystack = (char *)*piVar5;
    if (__haystack != (char *)0x0) {
      do {
        piVar5 = piVar5 + 1;
        pcVar7 = strstr(__haystack,"candidate");
        if (pcVar7 != (char *)0x0) {
          iVar9 = g_strsplit(__haystack,&DAT_00410f2c,2);
          uVar1 = cJSON_CreateObject();
          cJSON_AddStringToObject(uVar1,"action","ice_msg");
          cJSON_AddStringToObject(uVar1,&DAT_00410f00,*(undefined4 *)(param_2 + 0x2c));
          uVar2 = cJSON_CreateObject();
          cJSON_AddStringToObject(uVar2,&DAT_0040fcec,"candidate");
          uVar3 = cJSON_CreateObject();
          cJSON_AddStringToObject(uVar3,"candidate",*(undefined4 *)(iVar9 + 4));
          cJSON_AddNumberToObject(uVar3,"sdpMLineIndex",0,0);
          cJSON_AddStringToObject(uVar3,"sdpMid",&DAT_0040f468);
          cJSON_AddItemToObject(uVar2,&DAT_00410de4,uVar3);
          cJSON_AddItemToObject(uVar1,"sdpMessage",uVar2);
          pvVar4 = (void *)cJSON_Print(uVar1);
          cJSON_Delete(uVar1);
          if (pvVar4 != (void *)0x0) {
            hs_log_push(1,"%s\n",*(undefined4 *)(iVar9 + 4));
            piVar6 = (int *)create_ice_send_buf(pvVar4);
            if (piVar6 != (int *)0x0) {
              g_mutex_lock(param_2 + 0xc);
              piVar8 = *(int **)(param_2 + 0x28);
              *(int **)(param_2 + 0x28) = piVar6;
              *piVar6 = param_2 + 0x24;
              piVar6[1] = (int)piVar8;
              *piVar8 = (int)piVar6;
              g_mutex_unlock(param_2 + 0xc);
            }
            free(pvVar4);
          }
        }
        __haystack = (char *)*piVar5;
      } while (__haystack != (char *)0x0);
      return;
    }
  }
  return;
}



// === SSL_CTX_free @ 004114f0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_free(SSL_CTX *param_1)

{
  (*(code *)PTR_SSL_CTX_free_0042234c)();
  return;
}



// === EVP_PKEY_free @ 004115b0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EVP_PKEY_free(EVP_PKEY *pkey)

{
  (*(code *)PTR_EVP_PKEY_free_0042237c)();
  return;
}



// === X509_getm_notAfter @ 004115e0 ===

void X509_getm_notAfter(void)

{
  (*(code *)PTR_X509_getm_notAfter_00422388)();
  return;
}



// === SSL_set_options @ 00411690 ===

void SSL_set_options(void)

{
  (*(code *)PTR_SSL_set_options_004223b4)();
  return;
}



// === SSL_new @ 004116b0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL * SSL_new(SSL_CTX *ctx)

{
  SSL *pSVar1;
  
  pSVar1 = (SSL *)(*(code *)PTR_SSL_new_004223bc)();
  return pSVar1;
}



// === g_mutex_unlock @ 004116c0 ===

void g_mutex_unlock(void)

{
  (*(code *)PTR_g_mutex_unlock_004223c0)();
  return;
}



// === SSL_CTX_use_certificate @ 004116f0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_certificate(SSL_CTX *ctx,X509 *x)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_use_certificate_004223cc)();
  return iVar1;
}



// === g_signal_connect_data @ 00411760 ===

void g_signal_connect_data(void)

{
  (*(code *)PTR_g_signal_connect_data_004223e8)();
  return;
}



// === SSL_read @ 004117f0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_read(SSL *ssl,void *buf,int num)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_read_0042240c)();
  return iVar1;
}



// === SSL_export_keying_material @ 00411900 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_export_keying_material
              (SSL *s,uchar *out,size_t olen,char *label,size_t llen,uchar *p,size_t plen,
              int use_context)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_export_keying_material_00422450)();
  return iVar1;
}



// === strsignal @ 00411930 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strsignal(int __sig)

{
  char *pcVar1;
  
  pcVar1 = (char *)(*(code *)PTR_strsignal_0042245c)();
  return pcVar1;
}



// === EC_KEY_new_by_curve_name @ 00411970 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EC_KEY * EC_KEY_new_by_curve_name(int nid)

{
  EC_KEY *pEVar1;
  
  pEVar1 = (EC_KEY *)(*(code *)PTR_EC_KEY_new_by_curve_name_0042246c)();
  return pEVar1;
}



// === SSL_do_handshake @ 00411a00 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_do_handshake(SSL *s)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_do_handshake_00422490)();
  return iVar1;
}



// === SSL_CTX_set_verify @ 00411a40 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_set_verify(SSL_CTX *ctx,int mode,callback *callback)

{
  (*(code *)PTR_SSL_CTX_set_verify_004224a0)();
  return;
}



// === SSL_set_bio @ 00411a50 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_bio(SSL *s,BIO *rbio,BIO *wbio)

{
  (*(code *)PTR_SSL_set_bio_004224a4)();
  return;
}



// === RSA_generate_key_ex @ 00411aa0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int RSA_generate_key_ex(RSA *rsa,int bits,BIGNUM *e,BN_GENCB *cb)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_RSA_generate_key_ex_004224b8)();
  return iVar1;
}



// === SSL_CTX_new @ 00411ad0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL_CTX * SSL_CTX_new(SSL_METHOD *meth)

{
  SSL_CTX *pSVar1;
  
  pSVar1 = (SSL_CTX *)(*(code *)PTR_SSL_CTX_new_004224c4)();
  return pSVar1;
}



// === EVP_PKEY_assign @ 00411b00 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_PKEY_assign(EVP_PKEY *pkey,int type,void *key)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_EVP_PKEY_assign_004224d0)();
  return iVar1;
}



// === X509_sign @ 00411b10 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_sign(X509 *x,EVP_PKEY *pkey,EVP_MD *md)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_X509_sign_004224d4)();
  return iVar1;
}



// === SSL_free @ 00411b40 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_free(SSL *ssl)

{
  (*(code *)PTR_SSL_free_004224e0)();
  return;
}



// === srtp_crypto_policy_set_rtp_default @ 00411b60 ===

void srtp_crypto_policy_set_rtp_default(void)

{
  (*(code *)PTR_srtp_crypto_policy_set_rtp_default_004224e8)();
  return;
}



// === SSL_get_peer_certificate @ 00411bc0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

X509 * SSL_get_peer_certificate(SSL *s)

{
  X509 *pXVar1;
  
  pXVar1 = (X509 *)(*(code *)PTR_SSL_get_peer_certificate_00422500)();
  return pXVar1;
}



// === SSL_get_error @ 00411c20 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_get_error(SSL *s,int ret_code)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_get_error_00422518)();
  return iVar1;
}



// === SSL_CTX_ctrl @ 00411c60 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_CTX_ctrl(SSL_CTX *ctx,int cmd,long larg,void *parg)

{
  long lVar1;
  
  lVar1 = (*(code *)PTR_SSL_CTX_ctrl_00422528)();
  return lVar1;
}



// === srtp_crypto_policy_set_rtcp_default @ 00411cd0 ===

void srtp_crypto_policy_set_rtcp_default(void)

{
  (*(code *)PTR_srtp_crypto_policy_set_rtcp_default_00422544)();
  return;
}



// === SSL_set_accept_state @ 00411cf0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_accept_state(SSL *s)

{
  (*(code *)PTR_SSL_set_accept_state_0042254c)();
  return;
}



// === EC_KEY_free @ 00411d00 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EC_KEY_free(EC_KEY *key)

{
  (*(code *)PTR_EC_KEY_free_00422550)();
  return;
}



// === pthread_cond_signal @ 00411d50 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_cond_signal_00422564)();
  return iVar1;
}



// === SSL_CTX_use_PrivateKey @ 00411db0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx,EVP_PKEY *pkey)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_use_PrivateKey_0042257c)();
  return iVar1;
}



// === SSL_ctrl @ 00411ea0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_ctrl(SSL *ssl,int cmd,long larg,void *parg)

{
  long lVar1;
  
  lVar1 = (*(code *)PTR_SSL_ctrl_004225b8)();
  return lVar1;
}



// === pthread_mutex_unlock @ 00411f20 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_mutex_unlock_004225d8)();
  return iVar1;
}



// === signal @ 00412040 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;
  
  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_00422620)();
  return p_Var1;
}



// === DTLS_method @ 004120d0 ===

void DTLS_method(void)

{
  (*(code *)PTR_DTLS_method_00422644)();
  return;
}



// === EVP_PKEY_new @ 00412110 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EVP_PKEY * EVP_PKEY_new(void)

{
  EVP_PKEY *pEVar1;
  
  pEVar1 = (EVP_PKEY *)(*(code *)PTR_EVP_PKEY_new_00422654)();
  return pEVar1;
}



// === SSL_CTX_check_private_key @ 004121c0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_check_private_key(SSL_CTX *ctx)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_check_private_key_00422680)();
  return iVar1;
}



// === SSL_is_init_finished @ 004121f0 ===

void SSL_is_init_finished(void)

{
  (*(code *)PTR_SSL_is_init_finished_0042268c)();
  return;
}



// === X509_set_pubkey @ 00412200 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_set_pubkey(X509 *x,EVP_PKEY *pkey)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_X509_set_pubkey_00422690)();
  return iVar1;
}



// === g_cond_signal @ 00412260 ===

void g_cond_signal(void)

{
  (*(code *)PTR_g_cond_signal_004226a8)();
  return;
}



// === SSL_CTX_set_tlsext_use_srtp @ 00412320 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_set_tlsext_use_srtp(SSL_CTX *ctx,char *profiles)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SSL_CTX_set_tlsext_use_srtp_004226d8)();
  return iVar1;
}



// === SSL_CTX_free @ 0042700c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_free(SSL_CTX *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_PKEY_free @ 00427038 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EVP_PKEY_free(EVP_PKEY *pkey)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_PKEY_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === X509_getm_notAfter @ 00427044 ===

/* WARNING: Control flow encountered bad instruction data */

void X509_getm_notAfter(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* X509_getm_notAfter@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_set_options @ 00427074 ===

/* WARNING: Control flow encountered bad instruction data */

void SSL_set_options(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_set_options@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_new @ 0042707c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL * SSL_new(SSL_CTX *ctx)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_new@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === g_mutex_unlock @ 00427080 ===

/* WARNING: Control flow encountered bad instruction data */

void g_mutex_unlock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_CTX_use_certificate @ 0042708c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_certificate(SSL_CTX *ctx,X509 *x)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_use_certificate@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === g_signal_connect_data @ 004270a8 ===

/* WARNING: Control flow encountered bad instruction data */

void g_signal_connect_data(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_read @ 004270cc ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_read(SSL *ssl,void *buf,int num)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_read@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_export_keying_material @ 00427110 ===

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



// === strsignal @ 0042711c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strsignal(int __sig)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* strsignal@@GLIBC_2.0 */
  halt_baddata();
}



// === EC_KEY_new_by_curve_name @ 0042712c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EC_KEY * EC_KEY_new_by_curve_name(int nid)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EC_KEY_new_by_curve_name@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_do_handshake @ 00427150 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_do_handshake(SSL *s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_do_handshake@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_set_verify @ 00427160 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_CTX_set_verify(SSL_CTX *ctx,int mode,callback *callback)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_set_verify@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_set_bio @ 00427164 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_bio(SSL *s,BIO *rbio,BIO *wbio)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_set_bio@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === RSA_generate_key_ex @ 00427178 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int RSA_generate_key_ex(RSA *rsa,int bits,BIGNUM *e,BN_GENCB *cb)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* RSA_generate_key_ex@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_new @ 00427184 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

SSL_CTX * SSL_CTX_new(SSL_METHOD *meth)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_new@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_PKEY_assign @ 00427190 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EVP_PKEY_assign(EVP_PKEY *pkey,int type,void *key)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_PKEY_assign@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === X509_sign @ 00427194 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_sign(X509 *x,EVP_PKEY *pkey,EVP_MD *md)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* X509_sign@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_free @ 004271a0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_free(SSL *ssl)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === srtp_crypto_policy_set_rtp_default @ 004271a8 ===

/* WARNING: Control flow encountered bad instruction data */

void srtp_crypto_policy_set_rtp_default(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_get_peer_certificate @ 004271c0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

X509 * SSL_get_peer_certificate(SSL *s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_get_peer_certificate@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_get_error @ 004271d8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_get_error(SSL *s,int ret_code)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_get_error@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_ctrl @ 004271e8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_CTX_ctrl(SSL_CTX *ctx,int cmd,long larg,void *parg)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_ctrl@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === srtp_crypto_policy_set_rtcp_default @ 00427204 ===

/* WARNING: Control flow encountered bad instruction data */

void srtp_crypto_policy_set_rtcp_default(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_set_accept_state @ 0042720c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SSL_set_accept_state(SSL *s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_set_accept_state@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EC_KEY_free @ 00427210 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EC_KEY_free(EC_KEY *key)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EC_KEY_free@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_cond_signal @ 00427224 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_cond_signal@@GLIBC_2.3.2 */
  halt_baddata();
}



// === SSL_CTX_use_PrivateKey @ 0042723c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_use_PrivateKey(SSL_CTX *ctx,EVP_PKEY *pkey)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_use_PrivateKey@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_ctrl @ 00427278 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long SSL_ctrl(SSL *ssl,int cmd,long larg,void *parg)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_ctrl@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_mutex_unlock @ 00427298 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_mutex_unlock@@GLIBC_2.0 */
  halt_baddata();
}



// === signal @ 004272e0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* signal@@GLIBC_2.0 */
  halt_baddata();
}



// === DTLS_method @ 00427304 ===

/* WARNING: Control flow encountered bad instruction data */

void DTLS_method(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* DTLS_method@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === EVP_PKEY_new @ 00427318 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

EVP_PKEY * EVP_PKEY_new(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* EVP_PKEY_new@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_CTX_check_private_key @ 00427344 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_check_private_key(SSL_CTX *ctx)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_check_private_key@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === SSL_is_init_finished @ 00427350 ===

/* WARNING: Control flow encountered bad instruction data */

void SSL_is_init_finished(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_is_init_finished@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === X509_set_pubkey @ 00427354 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int X509_set_pubkey(X509 *x,EVP_PKEY *pkey)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* X509_set_pubkey@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === g_cond_signal @ 0042736c ===

/* WARNING: Control flow encountered bad instruction data */

void g_cond_signal(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



// === SSL_CTX_set_tlsext_use_srtp @ 00427398 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SSL_CTX_set_tlsext_use_srtp(SSL_CTX *ctx,char *profiles)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SSL_CTX_set_tlsext_use_srtp@@OPENSSL_1_1_0 */
  halt_baddata();
}


