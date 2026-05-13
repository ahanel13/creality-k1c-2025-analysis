
// === _parse_config_section_key_value @ 00404480 ===

/* WARNING: Unknown calling convention */

void _parse_config_section_key_value(ConfigHelper *config,char *section,char *key,mg_iobuf value)

{
  void *pvVar1;
  OrderedDict *pOVar2;
  int iVar3;
  int in_a0;
  int in_a1;
  int in_a2;
  undefined4 in_a3;
  OrderedDict *in_stack_ffffffd8;
  char *in_stack_ffffffdc;
  void *in_stack_ffffffe0;
  FreeValueFunc in_stack_ffffffe4;
  OrderedDict *section_dict;
  char *value_str;
  
  if ((((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) || (value.len == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/src/confighelper.c"
            ,0xc,"section, key or value is null");
  }
  else {
    pvVar1 = ordered_dict_get(in_stack_ffffffd8,in_stack_ffffffdc);
    if (pvVar1 == (void *)0x0) {
      pOVar2 = ordered_dict_create();
      if (pOVar2 == (OrderedDict *)0x0) {
        log_log(1,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/src/confighelper.c"
                ,0x16,"Memory allocation for section_dict failed");
        return;
      }
      ordered_dict_add(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    }
    iVar3 = mg_mprintf(&DAT_0048faac,value.len,in_a3);
    if (iVar3 != 0) {
      ordered_dict_add(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4);
    }
  }
  return;
}



// === signal_handler @ 004074a0 ===

/* WARNING: Unknown calling convention */

void signal_handler(int signo)

{
  int in_a0;
  Server *in_stack_ffffffd8;
  
  s_signo = in_a0;
  log_log(3,
          "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/src/main.c"
          ,0x20,"Received signal %d, exiting...");
  server_stop(in_stack_ffffffd8);
  return;
}



// === authorization_init @ 0040c0a0 ===

/* WARNING: Unknown calling convention */

int authorization_init(Authorization *auth,Server *server)

{
  int iVar1;
  int *in_a0;
  int in_a1;
  Server *in_stack_ffffffd8;
  char *in_stack_ffffffdc;
  RequestCallback in_stack_ffffffe0;
  void *in_stack_ffffffe4;
  
  if ((in_a0 == (int *)0x0) || (in_a1 == 0)) {
    iVar1 = -1;
  }
  else {
    *in_a0 = in_a1;
    server_reg_endpoint(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4,
                        '\x01');
    server_reg_endpoint(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4,'\a'
                       );
    server_reg_endpoint(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4,
                        '\x03');
    server_reg_endpoint(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4,
                        '\x01');
    server_reg_endpoint(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0,in_stack_ffffffe4,
                        '\x01');
    iVar1 = 0;
  }
  return iVar1;
}



// === authorization_free @ 0040c1cc ===

/* WARNING: Unknown calling convention */

int authorization_free(Authorization *auth)

{
  int iVar1;
  int in_a0;
  
  if (in_a0 == 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}



// === _handle_api_key @ 0040c304 ===

/* WARNING: Unknown calling convention */

Result * _handle_api_key(WebRequest *req)

{
  Result *in_a0;
  int in_a1;
  ErrorCode in_stack_ffffffe4;
  char *in_stack_ffffffe8;
  
  if (in_a1 == 0) {
    result_err(in_stack_ffffffe4,in_stack_ffffffe8);
  }
  else {
    result_ok_fmt(&in_a0->is_ok,"\"3fadf317c8d9459780a909de4e56e286\"");
  }
  return in_a0;
}



// === _handle_oneshot_token @ 0040c3fc ===

/* WARNING: Unknown calling convention */

Result * _handle_oneshot_token(WebRequest *req)

{
  Result *in_a0;
  int in_a1;
  ErrorCode in_stack_ffffffe4;
  char *in_stack_ffffffe8;
  
  if (in_a1 == 0) {
    result_err(in_stack_ffffffe4,in_stack_ffffffe8);
  }
  else {
    result_ok_fmt(&in_a0->is_ok,"\"HZW44TEQVJFJWNFCDIIOUJMG4DA7P4CA\"");
  }
  return in_a0;
}



// === _update_temp_store @ 0040d21c ===

/* WARNING: Unknown calling convention */

void _update_temp_store(void *arg)

{
  int iVar1;
  void *pvVar2;
  char *pcVar3;
  int iVar4;
  void *__ptr;
  int *piVar5;
  undefined8 *puVar6;
  void *__ptr_00;
  int *in_a0;
  CircularQueue *in_stack_ffffff90;
  void *in_stack_ffffff94;
  OrderedDictEntry *entry;
  OrderedDictEntry *sub_entry;
  double *new_val;
  DataStore *data_store;
  Server *server;
  Klippy *klippy;
  OrderedDict *sensor_dict;
  char *sensor_name;
  cJSON *sdata_json;
  char *sdata;
  CircularQueue *field_deque;
  char *field_name;
  char *path;
  void *old_val;
  undefined4 local_20;
  undefined4 local_1c;
  double val;
  undefined4 local_c;
  
  local_c = 0;
  if (((in_a0 == (int *)0x0) || (*in_a0 == 0)) || (*(int *)(*in_a0 + 0x3c) == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/data_store.c"
            ,0xff,"Invalid argument for updating temperature store");
  }
  else {
    iVar1 = *(int *)(*in_a0 + 0x3c);
    pthread_mutex_lock((pthread_mutex_t *)(in_a0 + 3));
    for (entry = *(OrderedDictEntry **)(in_a0[2] + 0xc); entry != (OrderedDictEntry *)0x0;
        entry = entry->list_next) {
      pvVar2 = entry->value;
      pcVar3 = entry->key;
      if ((pvVar2 != (void *)0x0) && (pcVar3 != (char *)0x0)) {
        pthread_rwlock_rdlock((pthread_rwlock_t *)(iVar1 + 0xbc));
        iVar4 = cJSON_GetObjectItem(*(undefined4 *)(iVar1 + 0xb8),pcVar3);
        if (iVar4 == 0) {
          __ptr = (void *)0x0;
        }
        else {
          __ptr = (void *)cJSON_PrintUnformatted(iVar4);
        }
        pthread_rwlock_unlock((pthread_rwlock_t *)(iVar1 + 0xbc));
        for (sub_entry = *(OrderedDictEntry **)((int)pvVar2 + 0xc);
            sub_entry != (OrderedDictEntry *)0x0; sub_entry = sub_entry->list_next) {
          piVar5 = sub_entry->value;
          if ((piVar5 != (int *)0x0) && (sub_entry->key != (char *)0x0)) {
            pvVar2 = (void *)mg_mprintf(&DAT_00491d20,sub_entry->key);
            local_c = 0;
            val._0_4_ = 0;
            val._4_4_ = 0;
            if (__ptr == (void *)0x0) {
LAB_0040d4c4:
              if (piVar5[3] == 0) {
                trap(7);
              }
              if (*(int *)(*piVar5 + ((piVar5[2] + -1 + piVar5[3]) % piVar5[3]) * 4) != 0) {
                puVar6 = malloc(8);
                if (puVar6 == (undefined8 *)0x0) {
                  log_log(1,
                          "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/data_store.c"
                          ,0x133,"Failed to allocate memory for new temperature value");
                  if (pvVar2 != (void *)0x0) {
                    free(pvVar2);
                  }
                  goto LAB_0040d638;
                }
                local_c = 0;
                if (piVar5[3] == 0) {
                  trap(7);
                }
                *puVar6 = **(undefined8 **)
                            (*piVar5 + ((piVar5[2] + -1 + piVar5[3]) % piVar5[3]) * 4);
              }
            }
            else {
              mg_str_s(&local_20,__ptr);
              iVar4 = mg_json_get_num(local_20,local_1c,pvVar2,&val);
              if (iVar4 == 0) goto LAB_0040d4c4;
              puVar6 = malloc(8);
              if (puVar6 == (undefined8 *)0x0) {
                log_log(1,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/data_store.c"
                        ,0x126,"Failed to allocate memory for new temperature value");
                if (pvVar2 != (void *)0x0) {
                  free(pvVar2);
                }
                goto LAB_0040d638;
              }
              local_c = 0;
              *puVar6 = CONCAT44(val._4_4_,val._0_4_);
            }
            __ptr_00 = circular_queue_enqueue(in_stack_ffffff90,in_stack_ffffff94);
            if (__ptr_00 != (void *)0x0) {
              free(__ptr_00);
            }
            if (pvVar2 != (void *)0x0) {
              free(pvVar2);
            }
          }
LAB_0040d638:
        }
        if (__ptr != (void *)0x0) {
          free(__ptr);
        }
      }
    }
    pthread_mutex_unlock((pthread_mutex_t *)(in_a0 + 3));
  }
  return;
}



// === parse_primary_key @ 00410174 ===

/* WARNING: Unknown calling convention */

char * parse_primary_key(char *key)

{
  size_t sVar1;
  char *in_a0;
  size_t i;
  
  if (in_a0 != (char *)0x0) {
    for (i = 0; sVar1 = strlen(in_a0), i < sVar1; i = i + 1) {
      if ((in_a0[i] == '.') && (in_a0[i + 1] != '\0')) {
        in_a0[i] = '\0';
        return in_a0 + i + 1;
      }
    }
  }
  return (char *)0x0;
}



// === get_next_key @ 00410254 ===

/* WARNING: Unknown calling convention */

char * get_next_key(char *path,char *key)

{
  char *pcVar1;
  char *in_a0;
  char *in_a1;
  char *dot;
  
  if ((in_a0 == (char *)0x0) || (*in_a0 == '\0')) {
    pcVar1 = (char *)0x0;
  }
  else {
    pcVar1 = strchr(in_a0,0x2e);
    if ((pcVar1 == (char *)0x0) || (0x3ff < (int)pcVar1 - (int)in_a0)) {
      strncpy(in_a1,in_a0,0x400);
      pcVar1 = (char *)0x0;
    }
    else {
      strncpy(in_a1,in_a0,(int)pcVar1 - (int)in_a0);
      in_a1[(int)pcVar1 - (int)in_a0] = '\0';
      pcVar1 = pcVar1 + 1;
    }
  }
  return pcVar1;
}



// === cjson_insert_nested_key @ 00410458 ===

/* WARNING: Unknown calling convention */

void cjson_insert_nested_key(cJSON *parent,char *path,cJSON *value)

{
  int iVar1;
  char *pcVar2;
  int in_a0;
  char *in_a1;
  int in_a2;
  cJSON *in_stack_fffffbd8;
  char *in_stack_fffffbdc;
  cJSON *in_stack_fffffbe0;
  cJSON *child;
  char *nextPath;
  char key [1024];
  
  if ((((in_a0 == 0) || (iVar1 = cJSON_IsObject(in_a0), iVar1 == 0)) || (in_a1 == (char *)0x0)) ||
     ((*in_a1 == '\0' || (in_a2 == 0)))) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/database.c"
            ,0x1c2,
            "Invalid parameters: parent is not an object or path is null or empty or value is null."
           );
  }
  else {
    memset(key,0,0x400);
    pcVar2 = get_next_key((char *)in_stack_fffffbd8,in_stack_fffffbdc);
    if (pcVar2 == (char *)0x0) {
      cJSON_DeleteItemFromObject(in_a0,key);
      cJSON_AddItemToObject(in_a0,key,in_a2);
    }
    else {
      iVar1 = cJSON_GetObjectItem(in_a0,key);
      if ((iVar1 == 0) || (iVar1 = cJSON_IsObject(iVar1), iVar1 == 0)) {
        cJSON_DeleteItemFromObject(in_a0,key);
        cJSON_AddObjectToObject(in_a0,key);
      }
      cjson_insert_nested_key(in_stack_fffffbd8,in_stack_fffffbdc,in_stack_fffffbe0);
    }
  }
  return;
}



// === cjson_delete_nested_key @ 004105e8 ===

/* WARNING: Unknown calling convention */

void cjson_delete_nested_key(cJSON *parent,char *path)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int in_a0;
  char *in_a1;
  cJSON *in_stack_fffffbd8;
  char *in_stack_fffffbdc;
  char *nextPath;
  cJSON *child;
  char key [1024];
  
  if ((((in_a0 == 0) || (iVar1 = cJSON_IsObject(in_a0), iVar1 == 0)) || (in_a1 == (char *)0x0)) ||
     (*in_a1 == '\0')) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/database.c"
            ,0x1e0,"Invalid parameters: parent is not an object or path is null or empty.");
  }
  else {
    memset(key,0,0x400);
    pcVar2 = get_next_key((char *)in_stack_fffffbd8,in_stack_fffffbdc);
    iVar1 = cJSON_GetObjectItem(in_a0,key);
    if (iVar1 != 0) {
      if (pcVar2 == (char *)0x0) {
        cJSON_DeleteItemFromObject(in_a0,key);
      }
      else {
        iVar3 = cJSON_IsObject(iVar1);
        if (iVar3 != 0) {
          cjson_delete_nested_key(in_stack_fffffbd8,in_stack_fffffbdc);
          iVar1 = cJSON_GetArraySize(iVar1);
          if (iVar1 == 0) {
            cJSON_DeleteItemFromObject(in_a0,key);
          }
        }
      }
    }
  }
  return;
}



// === is_roots_name_exists @ 00413b04 ===

/* WARNING: Unknown calling convention */

_Bool is_roots_name_exists(char *rootName)

{
  int iVar1;
  char *in_a0;
  size_t i;
  char *root [6];
  
  if (in_a0 == (char *)0x0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
            ,0x29d,"point is null.");
  }
  else {
    root[0] = "config";
    root[1] = "logs";
    root[2] = "gcodes";
    root[3] = "config_examples";
    root[4] = "docs";
    root[5] = "udisk";
    for (i = 0; i < 6; i = i + 1) {
      iVar1 = strcmp(in_a0,root[i]);
      if (iVar1 == 0) {
        return true;
      }
    }
  }
  return false;
}



// === is_full_access_roots @ 00413c14 ===

/* WARNING: Unknown calling convention */

_Bool is_full_access_roots(char *rootName)

{
  int iVar1;
  char *in_a0;
  size_t i;
  char *root [3];
  
  if (in_a0 == (char *)0x0) {
    log_log(2,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
            ,0x2b0,"point is null.");
  }
  else {
    root[0] = "config";
    root[1] = "gcodes";
    root[2] = "udisk";
    for (i = 0; i < 3; i = i + 1) {
      iVar1 = strcmp(in_a0,root[i]);
      if (iVar1 == 0) {
        return true;
      }
    }
  }
  return false;
}



// === process_metadata_update @ 00417dbc ===

/* WARNING: Unknown calling convention */

int process_metadata_update(char *fname,upload_file_info_st *pFileInfo)

{
  int iVar1;
  int in_a0;
  undefined4 *in_a1;
  char *in_stack_ffffffb8;
  upload_file_info_st *in_stack_ffffffbc;
  metadata_info_st *in_stack_ffffffc0;
  uint8_t i;
  cJSON *json;
  mg_iobuf metabuff;
  metadata_info_st metadata;
  
  if ((in_a0 == 0) || (in_a1 == (undefined4 *)0x0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
            ,0x85a,"point is null.");
    iVar1 = -1;
  }
  else {
    iVar1 = has_valid_data(in_stack_ffffffb8,in_stack_ffffffbc);
    if (iVar1 == 0) {
      metabuff.buf = (uchar *)0x0;
      metabuff.size = 0;
      metabuff.len = 0;
      metabuff.align = 0x80;
      metadata.pfn = mg_pfn_iobuf;
      metadata.pfn_data = &metabuff;
      meta_mprintf(&metadata,"{");
      for (i = '\0'; i < 3; i = i + '\x01') {
        mg_iobuf_del(&metabuff,1,metabuff.len);
        iVar1 = run_extract_metadata(in_stack_ffffffb8,in_stack_ffffffbc,in_stack_ffffffc0);
        if (iVar1 == 0) break;
      }
      if (i < 3) {
        meta_mprintf(&metadata,",\"print_start_time\": null");
        meta_mprintf(&metadata,",\"job_id\": null");
        meta_mprintf(&metadata,"}");
      }
      else {
        if (*(char *)(in_a1 + 2) == '\x01') {
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
                  ,0x879,"extract metadata fail");
          mg_iobuf_free(&metabuff);
          return -2;
        }
        meta_mprintf(&metadata,"\"size\": %ld",in_a1[7]);
        meta_mprintf(&metadata,",\"modified\": %lu.%06lu",in_a1[8],in_a1[9]);
        meta_mprintf(&metadata,",\"print_start_time\": null");
        meta_mprintf(&metadata,",\"job_id\": null");
        meta_mprintf(&metadata,"}");
      }
      trim_spaces(in_stack_ffffffb8);
      iVar1 = cJSON_Parse(metabuff.buf);
      if (iVar1 == 0) {
        log_log(2,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
                ,0x88a,"json is invalid.");
        mg_iobuf_free(&metabuff);
        return -3;
      }
      cJSON_Delete(iVar1);
      iVar1 = strncmp((char *)*in_a1,"/media/creality",0xf);
      if (iVar1 == 0) {
        write_gcode_metadata_to_buf
                  (in_stack_ffffffb8,(char *)in_stack_ffffffbc,(char *)in_stack_ffffffc0);
        log_log(3,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
                ,0x893,"udisk metadata. path:%s,fname:%s.\n",*in_a1,in_a0);
      }
      else {
        write_gcode_metadata(in_stack_ffffffb8,(char *)in_stack_ffffffbc);
        log_log(3,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
                ,0x898,"gcode metadata. path:%s,fname:%s.\n",*in_a1,in_a0);
      }
      mg_iobuf_free(&metabuff);
    }
    iVar1 = 0;
  }
  return iVar1;
}



// === server_files_roots @ 0041ff4c ===

/* WARNING: Removing unreachable block (ram,0x004201e8) */
/* WARNING: Unknown calling convention */

Result * server_files_roots(WebRequest *req)

{
  mg_str config_name_00;
  bool bVar1;
  char *pcVar2;
  Result *in_a0;
  int in_a1;
  Server *in_stack_ffffff78;
  stat_info_st *in_stack_ffffff7c;
  char *in_stack_ffffff80;
  int flg;
  size_t i;
  FileOpAPI *fileopApi;
  char *path;
  Server *server;
  undefined1 local_54 [8];
  stat_info_st statInfo;
  char *config_name [6];
  mg_iobuf io;
  
  if ((in_a1 == 0) || (*(int *)(in_a1 + 0x1c) == 0)) {
    result_err((ErrorCode)in_stack_ffffff7c,in_stack_ffffff80);
  }
  else {
    statInfo.path = (char *)0x0;
    statInfo.size = 0;
    statInfo.mode = 0;
    statInfo.permissions[0] = '\0';
    statInfo.permissions[1] = '\0';
    statInfo.permissions[2] = '\0';
    statInfo._15_1_ = 0;
    statInfo.modifiedTimeSec = 0;
    statInfo.modifiedTimeNsec = 0;
    bVar1 = false;
    config_name[0] = "config";
    config_name[1] = "logs";
    config_name[2] = "gcodes";
    config_name[3] = "config_examples";
    config_name[4] = "docs";
    config_name[5] = "udisk";
    if (**(int **)(in_a1 + 0x1c) == 0) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
              ,0x12a5,"point is null.");
      result_err((ErrorCode)in_stack_ffffff7c,in_stack_ffffff80);
    }
    else {
      io.buf = (uchar *)0x0;
      io.size = 0;
      io.len = 0;
      io.align = 0x100;
      mg_iobuf_add(&io,0,&DAT_004944ec,1);
      for (i = 0; i < 6; i = i + 1) {
        if (bVar1) {
          mg_iobuf_add(&io,io.len,&DAT_004944f0,1);
        }
        mg_str_s(local_54,config_name[i]);
        config_name_00.len = (size_t)in_stack_ffffff80;
        config_name_00.buf = (char *)in_stack_ffffff7c;
        pcVar2 = server_get_path_from_config_name(in_stack_ffffff78,config_name_00);
        if (pcVar2 != (char *)0x0) {
                    /* WARNING: Subroutine does not return */
          get_stat_Info((char *)in_stack_ffffff78,in_stack_ffffff7c);
        }
        mg_xprintf(mg_pfn_iobuf,&io,"{\"name\":\"%s\",\"path\":\"\",\"permissions\":\"\"}\n",
                   config_name[i]);
        bVar1 = true;
      }
      mg_iobuf_add(&io,io.len,&DAT_00494540,1);
      result_ok(in_stack_ffffff7c);
    }
  }
  return in_a0;
}



// === server_files_http_roots_file @ 00429730 ===

/* WARNING: Removing unreachable block (ram,0x00429a04) */
/* WARNING: Unknown calling convention */

int server_files_http_roots_file(mg_connection *c,char *httpHeads)

{
  mg_str config_name_00;
  bool bVar1;
  int iVar2;
  char *pcVar3;
  int in_a0;
  int in_a1;
  Server *in_stack_ffffff80;
  stat_info_st *in_stack_ffffff84;
  size_t in_stack_ffffff88;
  size_t flg;
  size_t i;
  Server *server;
  char *path;
  undefined1 local_50 [8];
  char *config_name [6];
  stat_info_st statInfo;
  mg_iobuf respIoBuff;
  
  if ((((in_a0 == 0) || (*(int *)(in_a0 + 4) == 0)) || (*(int *)(*(int *)(in_a0 + 4) + 0x24) == 0))
     || (in_a1 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
            ,0x1c79,"point is null.");
    iVar2 = -1;
  }
  else if (*(int *)(*(int *)(in_a0 + 4) + 0x24) == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/file_manager.c"
            ,0x1c80,"point is null.");
    mg_http_reply(in_a0,400,"Content-Type: text/plain\r\n","Invalid server.");
    iVar2 = -1;
  }
  else {
    config_name[0] = "config";
    config_name[1] = "logs";
    config_name[2] = "gcodes";
    config_name[3] = "config_examples";
    config_name[4] = "docs";
    config_name[5] = "udisk";
    bVar1 = false;
    respIoBuff.buf = (uchar *)0x0;
    respIoBuff.size = 0;
    respIoBuff.len = 0;
    respIoBuff.align = 0x80;
    mg_xprintf(mg_pfn_iobuf,&respIoBuff,"{%m:[",mg_print_esc,0,"result");
    for (i = 0; i < 6; i = i + 1) {
      if (bVar1) {
        mg_xprintf(mg_pfn_iobuf,&respIoBuff,&DAT_004944f0);
      }
      mg_str_s(local_50,config_name[i]);
      config_name_00.len = in_stack_ffffff88;
      config_name_00.buf = (char *)in_stack_ffffff84;
      pcVar3 = server_get_path_from_config_name(in_stack_ffffff80,config_name_00);
      if (pcVar3 != (char *)0x0) {
                    /* WARNING: Subroutine does not return */
        get_stat_Info((char *)in_stack_ffffff80,in_stack_ffffff84);
      }
      mg_xprintf(mg_pfn_iobuf,&respIoBuff,"{\"name\":\"%s\",\"path\":\"\",\"permissions\":\"\"}\n",
                 config_name[i]);
      bVar1 = true;
    }
    mg_xprintf(mg_pfn_iobuf,&respIoBuff,&DAT_004956d0);
    mg_http_reply(in_a0,200,in_a1,&DAT_00492ec0,respIoBuff.len,respIoBuff.buf);
    mg_iobuf_free(&respIoBuff);
    iVar2 = 0;
  }
  return iVar2;
}



// === history_update_metadata @ 0042fc38 ===

/* WARNING: Removing unreachable block (ram,0x0042fd28) */
/* WARNING: Removing unreachable block (ram,0x0042fd48) */
/* WARNING: Removing unreachable block (ram,0x0042fd5c) */
/* WARNING: Removing unreachable block (ram,0x0042fd90) */
/* WARNING: Removing unreachable block (ram,0x0042fe60) */
/* WARNING: Removing unreachable block (ram,0x0042fe84) */
/* WARNING: Removing unreachable block (ram,0x0042fe94) */
/* WARNING: Removing unreachable block (ram,0x0042fee4) */
/* WARNING: Removing unreachable block (ram,0x0042ff00) */
/* WARNING: Removing unreachable block (ram,0x0042febc) */
/* WARNING: Removing unreachable block (ram,0x0042fe2c) */
/* WARNING: Removing unreachable block (ram,0x0042fd68) */
/* WARNING: Unknown calling convention */

void history_update_metadata(History *history,int job_id)

{
  int iVar1;
  int in_a0;
  char *in_stack_ffffffb8;
  char **in_stack_ffffffbc;
  PrinterJob *current_job;
  char *filename;
  int ret;
  cJSON *json;
  char *job_id_str;
  char *json_string;
  char *metadata;
  
  if ((in_a0 == 0) || (*(int *)(in_a0 + 0x24) == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x1d9,"history or current_job is null");
  }
  else {
    cJSON_GetStringValue(*(undefined4 *)(*(int *)(in_a0 + 0x24) + 0xc));
    iVar1 = get_gcode_metadata(in_stack_ffffffb8,in_stack_ffffffbc);
    if (iVar1 != 0) {
      log_log(4,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,0x1e4,"Job metadata grabbed failed");
    }
  }
  return;
}



// === history_update_job_totals @ 0042ff2c ===

/* WARNING: Unknown calling convention */

void history_update_job_totals(History *history)

{
  int iVar1;
  int *in_a0;
  History *in_stack_ffffffd0;
  char *in_stack_ffffffd4;
  double in_stack_ffffffd8;
  PrinterJob *current_job;
  
  if ((in_a0 == (int *)0x0) || (*in_a0 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x20d,"history or server is null");
  }
  else if ((in_a0[9] == 0) || (in_a0[10] == -1)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x213,"current_job or current_job_id is null");
  }
  else {
    iVar1 = in_a0[9];
    _accumulate_total(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
    cJSON_GetNumberValue(*(undefined4 *)(iVar1 + 0x20));
    _accumulate_total(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
    cJSON_GetNumberValue(*(undefined4 *)(iVar1 + 0x1c));
    _accumulate_total(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
    cJSON_GetNumberValue(*(undefined4 *)(iVar1 + 0x24));
    _accumulate_total(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
    cJSON_GetNumberValue(*(undefined4 *)(iVar1 + 0x20));
    _maximize_total(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
    cJSON_GetNumberValue(*(undefined4 *)(iVar1 + 0x1c));
    _maximize_total(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
    iVar1 = history_save_total_history(in_stack_ffffffd0);
    if (iVar1 != 0) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,0x223,"Failed to save total history.");
    }
  }
  return;
}



// === printer_job_update_from_ps @ 00430c6c ===

/* WARNING: Unknown calling convention */

void printer_job_update_from_ps(PrinterJob *job,char *printer_job_data)

{
  int iVar1;
  int iVar2;
  undefined4 *in_a0;
  int in_a1;
  PrinterJob *in_stack_ffffffd0;
  char *in_stack_ffffffd4;
  cJSON *in_stack_ffffffd8;
  cJSON *src_child;
  cJSON *src_item;
  
  if ((in_a0 == (undefined4 *)0x0) || (in_a1 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x2b5,"job or printer_job_data is null");
  }
  else {
    iVar1 = cJSON_Parse(in_a1);
    if (iVar1 == 0) {
      log_log(4,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,699,"Error parsing JSON.");
    }
    else {
      src_child = *(cJSON **)(iVar1 + 8);
      while (src_child != (cJSON *)0x0) {
        if (src_child->string == (char *)0x0) {
          src_child = src_child->next;
        }
        else {
          iVar2 = cJSON_HasObjectItem(*in_a0,src_child->string);
          if (iVar2 != 0) {
            cJSON_Duplicate(src_child,1);
            printer_job_set_attribute(in_stack_ffffffd0,in_stack_ffffffd4,in_stack_ffffffd8);
          }
          src_child = src_child->next;
        }
      }
      cJSON_Delete(iVar1);
    }
  }
  return;
}



// === history_load_total_history @ 00431358 ===

/* WARNING: Unknown calling convention */

int history_load_total_history(History *history)

{
  int iVar1;
  FILE *__stream;
  size_t sVar2;
  void *pvVar3;
  undefined4 uVar4;
  char *__s1;
  char *__s1_00;
  int *in_a0;
  double in_f0_1;
  double dVar5;
  Server *in_stack_fffffaa8;
  char *in_stack_fffffaac;
  double value;
  FILE *fp;
  size_t size;
  Database *database;
  int rc;
  char *provider;
  char *field;
  char fname [256];
  char sql [1024];
  sqlite3_stmt *stmt;
  undefined4 local_c;
  
  local_c = 0;
  if ((in_a0 == (int *)0x0) || (*in_a0 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x359,"history or server is null");
    iVar1 = -1;
  }
  else {
    memset(fname,0,0x100);
    sprintf(fname,"%s/%s",*(undefined4 *)(*in_a0 + 0x28),"totals");
    __stream = fopen(fname,"r");
    if (__stream != (FILE *)0x0) {
      sVar2 = fread(in_a0 + 0xc,1,0x30,__stream);
      fclose(__stream);
      if (sVar2 == 0x30) {
        return 0;
      }
    }
    pvVar3 = server_lookup_component(in_stack_fffffaa8,in_stack_fffffaac);
    if ((pvVar3 == (void *)0x0) || (*(int *)((int)pvVar3 + 4) == 0)) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,0x36d,"database is null or db is null");
      iVar1 = -2;
    }
    else {
      memset(sql,0,0x400);
      snprintf(sql,0x400,"SELECT * FROM %s","job_totals");
      sql[0x3ff] = '\0';
      pthread_mutex_lock((pthread_mutex_t *)((int)pvVar3 + 8));
      iVar1 = sqlite3_prepare_v2(*(undefined4 *)((int)pvVar3 + 4),sql,0xffffffff,&stmt,0);
      if (iVar1 == 0) {
LAB_004318d0:
        iVar1 = sqlite3_step(stmt);
        if (iVar1 == 100) {
          __s1 = (char *)sqlite3_column_text(stmt,0);
          __s1_00 = (char *)sqlite3_column_text(stmt,1);
          if ((__s1 != (char *)0x0) && (__s1_00 != (char *)0x0)) {
            local_c = 0;
            iVar1 = sqlite3_column_type(stmt,2);
            if (iVar1 == 5) {
              iVar1 = sqlite3_column_type(stmt,3);
              if (iVar1 == 5) goto LAB_004318d0;
              local_c = 0;
              sqlite3_column_double(stmt,3);
              dVar5 = in_f0_1;
            }
            else {
              local_c = 0;
              sqlite3_column_double(stmt,2);
              dVar5 = in_f0_1;
            }
            local_c = 0;
            in_f0_1 = dVar5;
            iVar1 = strcmp(__s1,"history");
            if (iVar1 == 0) {
              iVar1 = strcmp(__s1_00,"total_jobs");
              if (iVar1 == 0) {
                local_c = 0;
                in_a0[0xc] = (int)dVar5;
                in_f0_1 = (double)CONCAT44((int)((ulonglong)dVar5 >> 0x20),(int)dVar5);
              }
              else {
                iVar1 = strcmp(__s1_00,"total_time");
                if (iVar1 == 0) {
                  local_c = 0;
                  *(double *)(in_a0 + 0xe) = dVar5;
                  in_f0_1 = dVar5;
                }
                else {
                  iVar1 = strcmp(__s1_00,"total_print_time");
                  if (iVar1 == 0) {
                    local_c = 0;
                    *(double *)(in_a0 + 0x10) = dVar5;
                    in_f0_1 = dVar5;
                  }
                  else {
                    iVar1 = strcmp(__s1_00,"total_filament_used");
                    if (iVar1 == 0) {
                      local_c = 0;
                      *(double *)(in_a0 + 0x12) = dVar5;
                      in_f0_1 = dVar5;
                    }
                    else {
                      iVar1 = strcmp(__s1_00,"longest_job");
                      if (iVar1 == 0) {
                        local_c = 0;
                        *(double *)(in_a0 + 0x14) = dVar5;
                        in_f0_1 = dVar5;
                      }
                      else {
                        iVar1 = strcmp(__s1_00,"longest_print");
                        if (iVar1 == 0) {
                          local_c = 0;
                          *(double *)(in_a0 + 0x16) = dVar5;
                          in_f0_1 = dVar5;
                        }
                        else {
                          log_log(2,
                                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                                  ,0x3af,"Unknown total field: %s",__s1_00);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          goto LAB_004318d0;
        }
        sqlite3_finalize(stmt);
        pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar3 + 8));
        iVar1 = 0;
      }
      else {
        uVar4 = sqlite3_errmsg(*(undefined4 *)((int)pvVar3 + 4));
        log_log(1,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                ,0x37a,"Error preparing SQL statement: %s",uVar4);
        pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar3 + 8));
        iVar1 = -3;
      }
    }
  }
  return iVar1;
}



// === history_save_total_history @ 00431934 ===

/* WARNING: Unknown calling convention */

int history_save_total_history(History *history)

{
  int iVar1;
  FILE *__s;
  void *pvVar2;
  undefined4 uVar3;
  int *in_a0;
  Server *in_stack_fffffab8;
  char *in_stack_fffffabc;
  int i;
  FILE *fp;
  Database *database;
  int rc;
  char fname [256];
  char sql [1024];
  sqlite3_stmt *stmt;
  undefined4 local_c;
  
  local_c = 0;
  if ((in_a0 == (int *)0x0) || (*in_a0 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x3c1,"history or server is null");
    iVar1 = -1;
  }
  else {
    memset(fname,0,0x100);
    sprintf(fname,"%s/%s",*(undefined4 *)(*in_a0 + 0x28),"totals");
    __s = fopen(fname,"w");
    if (__s != (FILE *)0x0) {
      fwrite(in_a0 + 0xc,1,0x30,__s);
      fflush(__s);
      iVar1 = fileno(__s);
      fsync(iVar1);
      fclose(__s);
    }
    pvVar2 = server_lookup_component(in_stack_fffffab8,in_stack_fffffabc);
    if ((pvVar2 == (void *)0x0) || (*(int *)((int)pvVar2 + 4) == 0)) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,0x3d3,"database is null or db is null");
      iVar1 = -2;
    }
    else {
      memset(sql,0,0x400);
      snprintf(sql,0x400,"REPLACE INTO %s VALUES(?, ?, ?, ?, ?);","job_totals");
      sql[0x3ff] = '\0';
      pthread_mutex_lock((pthread_mutex_t *)((int)pvVar2 + 8));
      iVar1 = sqlite3_prepare_v2(*(undefined4 *)((int)pvVar2 + 4),sql,0xffffffff,&stmt,0);
      if (iVar1 == 0) {
        for (i = 0; i < 6; i = i + 1) {
          sqlite3_bind_text(stmt,1,"history",0xffffffff,0);
          switch(i) {
          case 0:
            sqlite3_bind_text(stmt,2,"total_jobs",0xffffffff,0);
            sqlite3_bind_null(stmt,3);
            local_c = 0;
            sqlite3_bind_double(stmt,4,SUB84((double)in_a0[0xc],0),
                                (int)((ulonglong)(double)in_a0[0xc] >> 0x20));
            break;
          case 1:
            sqlite3_bind_text(stmt,2,"total_time",0xffffffff,0);
            sqlite3_bind_null(stmt,3);
            local_c = 0;
            sqlite3_bind_double(stmt,4,(int)*(undefined8 *)(in_a0 + 0xe),
                                (int)((ulonglong)*(undefined8 *)(in_a0 + 0xe) >> 0x20));
            break;
          case 2:
            sqlite3_bind_text(stmt,2,"total_print_time",0xffffffff,0);
            sqlite3_bind_null(stmt,3);
            local_c = 0;
            sqlite3_bind_double(stmt,4,(int)*(undefined8 *)(in_a0 + 0x10),
                                (int)((ulonglong)*(undefined8 *)(in_a0 + 0x10) >> 0x20));
            break;
          case 3:
            sqlite3_bind_text(stmt,2,"total_filament_used",0xffffffff,0);
            sqlite3_bind_null(stmt,3);
            local_c = 0;
            sqlite3_bind_double(stmt,4,(int)*(undefined8 *)(in_a0 + 0x12),
                                (int)((ulonglong)*(undefined8 *)(in_a0 + 0x12) >> 0x20));
            break;
          case 4:
            sqlite3_bind_text(stmt,2,"longest_job",0xffffffff,0);
            local_c = 0;
            sqlite3_bind_double(stmt,3,(int)*(undefined8 *)(in_a0 + 0x14),
                                (int)((ulonglong)*(undefined8 *)(in_a0 + 0x14) >> 0x20));
            sqlite3_bind_null(stmt,4);
            break;
          case 5:
            sqlite3_bind_text(stmt,2,"longest_print",0xffffffff,0);
            local_c = 0;
            sqlite3_bind_double(stmt,3,(int)*(undefined8 *)(in_a0 + 0x16),
                                (int)((ulonglong)*(undefined8 *)(in_a0 + 0x16) >> 0x20));
            sqlite3_bind_null(stmt,4);
            break;
          default:
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                    ,0x416,"Invalid total field index: %d",i);
          }
          sqlite3_bind_text(stmt,5,"default",0xffffffff,0);
          iVar1 = sqlite3_step(stmt);
          if (iVar1 != 0x65) {
            uVar3 = sqlite3_errmsg(*(undefined4 *)((int)pvVar2 + 4));
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                    ,0x41d,"Error executing SQL statement: %s",uVar3);
            sqlite3_finalize(stmt);
            pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar2 + 8));
            return -4;
          }
          sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
        pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar2 + 8));
        if (in_a0[0x18] != 0) {
          log_log(2,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                  ,0x428,"Auxiliary totals not implemented.");
        }
        iVar1 = 0;
      }
      else {
        uVar3 = sqlite3_errmsg(*(undefined4 *)((int)pvVar2 + 4));
        log_log(1,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                ,0x3e0,"Error preparing SQL statement: %s",uVar3);
        pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar2 + 8));
        iVar1 = -3;
      }
    }
  }
  return iVar1;
}



// === history_reset_total @ 00434698 ===

/* WARNING: Unknown calling convention */

Result * history_reset_total(History *history)

{
  JobTotals job_totals;
  void *pvVar1;
  char *__ptr;
  char *__ptr_00;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  Result *in_a0;
  int *in_a1;
  History *in_stack_fffffba0;
  char *in_stack_fffffba4;
  char *in_stack_fffffba8;
  undefined4 in_stack_fffffbac;
  Database *database;
  char *last_totals;
  char *last_aux_totals;
  int rc;
  char sql [1024];
  sqlite3_stmt *stmt;
  Result result;
  
  if ((in_a1 == (int *)0x0) || (*in_a1 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x6b3,"history or server is null");
    result_err((ErrorCode)in_stack_fffffba4,in_stack_fffffba8);
  }
  else {
    pvVar1 = server_lookup_component((Server *)in_stack_fffffba0,in_stack_fffffba4);
    if ((pvVar1 == (void *)0x0) || (*(int *)((int)pvVar1 + 4) == 0)) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,0x6b9,"database is null or db is null");
      result_err((ErrorCode)in_stack_fffffba4,in_stack_fffffba8);
    }
    else {
      job_totals._4_4_ = in_stack_fffffba4;
      job_totals.total_jobs = (int)in_stack_fffffba0;
      job_totals.total_time._0_4_ = in_stack_fffffba8;
      job_totals.total_time._4_4_ = in_stack_fffffbac;
      job_totals.total_print_time._0_4_ = in_a1[0x10];
      job_totals.total_print_time._4_4_ = in_a1[0x11];
      job_totals.total_filament_used._0_4_ = in_a1[0x12];
      job_totals.total_filament_used._4_4_ = in_a1[0x13];
      job_totals.longest_job._0_4_ = in_a1[0x14];
      job_totals.longest_job._4_4_ = in_a1[0x15];
      job_totals.longest_print._0_4_ = in_a1[0x16];
      job_totals.longest_print._4_4_ = in_a1[0x17];
      __ptr = job_totals_to_json(job_totals);
      memcpy(in_a1 + 0xc,&BASE_TOTALS,0x30);
      if (in_a1[0x18] == 0) {
        __ptr_00 = (char *)0x0;
      }
      else {
        __ptr_00 = strdup((char *)in_a1[0x18]);
      }
      memset(sql,0,0x400);
      snprintf(sql,0x400,"DELETE FROM %s WHERE instance_id = ?","job_totals");
      sql[0x3ff] = '\0';
      pthread_mutex_lock((pthread_mutex_t *)((int)pvVar1 + 8));
      iVar2 = sqlite3_prepare_v2(*(undefined4 *)((int)pvVar1 + 4),sql,0xffffffff,&stmt,0);
      if (iVar2 == 0) {
        sqlite3_bind_text(stmt,1,"default",0xffffffff,0);
        iVar2 = sqlite3_step(stmt);
        if (iVar2 == 0x65) {
          sqlite3_finalize(stmt);
          pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar1 + 8));
          history_save_total_history(in_stack_fffffba0);
          pcVar4 = __ptr;
          if (__ptr == (char *)0x0) {
            pcVar4 = "null";
          }
          pcVar5 = __ptr_00;
          if (__ptr_00 == (char *)0x0) {
            pcVar5 = "[]";
          }
          result_ok_fmt(&result.is_ok,"{\"last_totals\": %s, \"last_auxiliary_totals\": %s}",pcVar4,
                        pcVar5);
          if (__ptr != (char *)0x0) {
            free(__ptr);
          }
          if (__ptr_00 != (char *)0x0) {
            free(__ptr_00);
          }
          in_a0->is_ok = result.is_ok;
          *(undefined3 *)&in_a0->field_0x1 = result._1_3_;
          (in_a0->field_1).data = result.field_1.data;
          (in_a0->field_1).err.code = result.field_1.err.code;
        }
        else {
          uVar3 = sqlite3_errmsg(*(undefined4 *)((int)pvVar1 + 4));
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                  ,0x6d5,"Failed to delete totals: %s",uVar3);
          sqlite3_finalize(stmt);
          pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar1 + 8));
          if (__ptr != (char *)0x0) {
            free(__ptr);
          }
          if (__ptr_00 != (char *)0x0) {
            free(__ptr_00);
          }
          result_err((ErrorCode)in_stack_fffffba4,in_stack_fffffba8);
        }
      }
      else {
        uVar3 = sqlite3_errmsg(*(undefined4 *)((int)pvVar1 + 4));
        log_log(1,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
                ,0x6ca,"Failed to prepare DELETE statement: %s",uVar3);
        pthread_mutex_unlock((pthread_mutex_t *)((int)pvVar1 + 8));
        if (__ptr != (char *)0x0) {
          free(__ptr);
        }
        if (__ptr_00 != (char *)0x0) {
          free(__ptr_00);
        }
        result_err((ErrorCode)in_stack_fffffba4,in_stack_fffffba8);
      }
    }
  }
  return in_a0;
}



// === _accumulate_total @ 00434b84 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention */

void _accumulate_total(History *history,char *field,double value)

{
  int iVar1;
  int in_a0;
  char *in_a1;
  undefined4 in_a2;
  undefined4 in_a3;
  
  if ((in_a0 == 0) || (in_a1 == (char *)0x0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x6ef,"history or field is null");
  }
  else {
    iVar1 = strcmp(in_a1,"total_jobs");
    if (iVar1 == 0) {
      *(int *)(in_a0 + 0x30) = (int)(double)CONCAT44(in_a3,in_a2) + *(int *)(in_a0 + 0x30);
    }
    else {
      iVar1 = strcmp(in_a1,"total_time");
      if (iVar1 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar1 = strcmp(in_a1,"total_print_time");
      if (iVar1 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      iVar1 = strcmp(in_a1,"total_filament_used");
      if (iVar1 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
      log_log(2,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
              ,0x704,"Invalid total field: %s",in_a1);
    }
  }
  return;
}



// === _maximize_total @ 00434d84 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention */

void _maximize_total(History *history,char *field,double value)

{
  int iVar1;
  int in_a0;
  char *in_a1;
  
  if ((in_a0 == 0) || (in_a1 == (char *)0x0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x70c,"history or field is null");
  }
  else {
    iVar1 = strcmp(in_a1,"longest_job");
    if (iVar1 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar1 = strcmp(in_a1,"longest_print");
    if (iVar1 == 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    log_log(2,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x71f,"Invalid total field: %s",in_a1);
  }
  return;
}



// === job_totals_to_json @ 00434f1c ===

/* WARNING: Unknown calling convention */

char * job_totals_to_json(JobTotals job_totals)

{
  int iVar1;
  char *pcVar2;
  int in_a0;
  undefined4 in_a2;
  undefined4 in_a3;
  cJSON *json_totals;
  char *json_str;
  
  iVar1 = cJSON_CreateObject();
  if (iVar1 == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/history.c"
            ,0x728,"json_totals:parse fail");
    pcVar2 = (char *)0x0;
  }
  else {
    cJSON_AddNumberToObject
              (iVar1,"total_jobs",SUB84((double)in_a0,0),(int)((ulonglong)(double)in_a0 >> 0x20));
    cJSON_AddNumberToObject(iVar1,"total_time",in_a2,in_a3);
    cJSON_AddNumberToObject
              (iVar1,"total_print_time",job_totals.total_print_time._0_4_,
               job_totals.total_print_time._4_4_);
    cJSON_AddNumberToObject
              (iVar1,"total_filament_used",job_totals.total_filament_used._0_4_,
               job_totals.total_filament_used._4_4_);
    cJSON_AddNumberToObject
              (iVar1,"longest_job",job_totals.longest_job._0_4_,job_totals.longest_job._4_4_);
    cJSON_AddNumberToObject
              (iVar1,"longest_print",job_totals.longest_print._0_4_,job_totals.longest_print._4_4_);
    pcVar2 = (char *)cJSON_PrintUnformatted(iVar1);
    cJSON_Delete(iVar1);
  }
  return pcVar2;
}



// === _handle_job_totals @ 004369b0 ===

/* WARNING: Unknown calling convention */

Result * _handle_job_totals(WebRequest *req)

{
  JobTotals job_totals_00;
  int iVar1;
  char *__ptr;
  char *pcVar2;
  undefined *puVar3;
  Result *in_a0;
  int in_a1;
  undefined4 in_stack_ffffffa8;
  ErrorCode in_stack_ffffffac;
  char *in_stack_ffffffb0;
  undefined4 in_stack_ffffffb4;
  History *history;
  char *job_totals;
  Result result;
  
  if ((in_a1 == 0) || (*(int *)(in_a1 + 0x1c) == 0)) {
    result_err(in_stack_ffffffac,in_stack_ffffffb0);
  }
  else {
    iVar1 = *(int *)(in_a1 + 0x1c);
    job_totals_00._4_4_ = in_stack_ffffffac;
    job_totals_00.total_jobs = in_stack_ffffffa8;
    job_totals_00.total_time._0_4_ = in_stack_ffffffb0;
    job_totals_00.total_time._4_4_ = in_stack_ffffffb4;
    job_totals_00.total_print_time._0_4_ = *(undefined4 *)(iVar1 + 0x40);
    job_totals_00.total_print_time._4_4_ = *(undefined4 *)(iVar1 + 0x44);
    job_totals_00.total_filament_used._0_4_ = *(undefined4 *)(iVar1 + 0x48);
    job_totals_00.total_filament_used._4_4_ = *(undefined4 *)(iVar1 + 0x4c);
    job_totals_00.longest_job._0_4_ = *(undefined4 *)(iVar1 + 0x50);
    job_totals_00.longest_job._4_4_ = *(undefined4 *)(iVar1 + 0x54);
    job_totals_00.longest_print._0_4_ = *(undefined4 *)(iVar1 + 0x58);
    job_totals_00.longest_print._4_4_ = *(undefined4 *)(iVar1 + 0x5c);
    __ptr = job_totals_to_json(job_totals_00);
    pcVar2 = __ptr;
    if (__ptr == (char *)0x0) {
      pcVar2 = "null";
    }
    if (*(int *)(iVar1 + 0x60) == 0) {
      puVar3 = &DAT_00497294;
    }
    else {
      puVar3 = *(undefined **)(iVar1 + 0x60);
    }
    result_ok_fmt(&result.is_ok,"{\"job_totals\": %s, \"auxiliary_totals\": %s}",pcVar2,puVar3);
    if (__ptr != (char *)0x0) {
      free(__ptr);
    }
    in_a0->is_ok = result.is_ok;
    *(undefined3 *)&in_a0->field_0x1 = result._1_3_;
    (in_a0->field_1).data = result.field_1.data;
    (in_a0->field_1).err.code = result.field_1.err.code;
  }
  return in_a0;
}



// === _handle_job_total_reset @ 00436b2c ===

/* WARNING: Unknown calling convention */

Result * _handle_job_total_reset(WebRequest *req)

{
  Result *in_a0;
  int in_a1;
  History *in_stack_ffffffd4;
  char *in_stack_ffffffd8;
  History *history;
  Result result;
  
  if (((in_a1 == 0) || (*(int *)(in_a1 + 0x1c) == 0)) || (**(int **)(in_a1 + 0x1c) == 0)) {
    result_err((ErrorCode)in_stack_ffffffd4,in_stack_ffffffd8);
  }
  else if (*(int *)(*(int *)(in_a1 + 0x1c) + 0x24) == 0) {
    history_reset_total(in_stack_ffffffd4);
    in_a0->is_ok = result.is_ok;
    *(undefined3 *)&in_a0->field_0x1 = result._1_3_;
    (in_a0->field_1).data = result.field_1.data;
    (in_a0->field_1).err.code = result.field_1.err.code;
  }
  else {
    result_err((ErrorCode)in_stack_ffffffd4,in_stack_ffffffd8);
  }
  return in_a0;
}



// === _status_update @ 0043bc40 ===

/* WARNING: Removing unreachable block (ram,0x0043c14c) */
/* WARNING: Removing unreachable block (ram,0x0043c058) */
/* WARNING: Unknown calling convention */

void _status_update(void *args,char *event_name,void *status)

{
  size_t sVar1;
  _Bool _Var2;
  void *pvVar3;
  OrderedDict *pOVar4;
  int iVar5;
  undefined3 extraout_var;
  void *pvVar6;
  JobEvent JVar7;
  int in_a0;
  int in_a1;
  int in_a2;
  Server *in_stack_ffffff18;
  OrderedDict *in_stack_ffffff1c;
  OrderedDict *in_stack_ffffff20;
  FreeValueFunc in_stack_ffffff24;
  mg_str *pmVar8;
  char *pcVar9;
  char *new_state;
  size_t ofs_1;
  size_t ofs;
  JobState *job_state;
  OrderedDict *prev_ps;
  char *old_state;
  OrderedDict *new_ps;
  char *event;
  char *key_str;
  char *val_str;
  char *key_str_1;
  char *val_str_1;
  mg_str status_str;
  mg_str ps;
  mg_str state;
  mg_str info_str;
  mg_str key;
  mg_str val;
  mg_str obj;
  mg_str key_1;
  mg_str val_1;
  mg_str obj_1;
  JobStateEventData event_data;
  mg_str filename;
  mg_str cur_layer;
  mg_str total;
  JobStateEventData event_data_1;
  
  if (((in_a0 != 0) && (in_a1 != 0)) && (in_a2 != 0)) {
    mg_str_s(&status_str,in_a2);
    mg_json_get_tok(&ps,status_str.buf,status_str.len,"$.print_stats");
    if (ps.len != 0) {
      pvVar3 = ordered_dict_get((OrderedDict *)in_stack_ffffff18,(char *)in_stack_ffffff1c);
      mg_json_get_tok(&state,ps.buf,ps.len,"$.state");
      if ((state.len != 0) && (pvVar3 != (void *)0x0)) {
        new_state = (char *)mg_mprintf(&DAT_00498134,state.len,state.buf);
        if (new_state == (char *)0x0) {
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                  ,0xdd,"Failed to malloc memory for new_state");
          return;
        }
        pOVar4 = ordered_dict_copy((OrderedDict *)in_stack_ffffff18,(CopyValueFunc)in_stack_ffffff1c
                                  );
        sVar1 = ps.len;
        pcVar9 = ps.buf;
        if (pOVar4 == (OrderedDict *)0x0) {
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                  ,0xe3,"Failed to create new_ps");
          if (new_state == (char *)0x0) {
            return;
          }
          free(new_state);
          return;
        }
        ofs_1 = 0;
        while( true ) {
          pmVar8 = &val_1;
          ofs_1 = mg_json_next(pcVar9,sVar1,ofs_1,&key_1,pmVar8);
          if (ofs_1 == 0) break;
          if ((key_1.len < 3) || (val_1.len == 0)) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                    ,0xed,"Failed to parse print_stats");
          }
          else {
            pvVar6 = (void *)mg_mprintf(&DAT_00498134,key_1.len - 2,key_1.buf + 1);
            if (pvVar6 == (void *)0x0) {
              log_log(1,
                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                      ,0xf3,"Failed to malloc memory for key_str");
            }
            else {
              iVar5 = mg_mprintf(&DAT_00498134,val_1.len,val_1.buf);
              if (iVar5 == 0) {
                log_log(1,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                        ,0xf9,"Failed to malloc memory for val_str");
                if (pvVar6 != (void *)0x0) {
                  free(pvVar6);
                }
              }
              else {
                ordered_dict_add((OrderedDict *)in_stack_ffffff18,(char *)in_stack_ffffff1c,
                                 in_stack_ffffff20,in_stack_ffffff24);
                if (pvVar6 != (void *)0x0) {
                  free(pvVar6);
                }
              }
            }
          }
        }
        iVar5 = mg_casecmp(new_state,pvVar3);
        if (iVar5 != 0) {
          iVar5 = mg_casecmp(new_state,"\"printing\"");
          if (iVar5 == 0) {
            _Var2 = _check_resumed((JobState *)in_stack_ffffff18,in_stack_ffffff1c,in_stack_ffffff20
                                  );
            if (CONCAT31(extraout_var,_Var2) == 0) {
              mg_json_get_tok(&filename,ps.buf,ps.len,"$.filename");
              if (filename.len != 0) {
                log_log(3,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                        ,0x117,"Job Started: %.*s",filename.len,filename.buf);
                pmVar8 = (mg_str *)filename.len;
              }
              if (new_state != (char *)0x0) {
                free(new_state);
              }
              new_state = (char *)mg_mprintf("\"started\"");
              if (new_state == (char *)0x0) {
                log_log(1,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                        ,0x11d,"Failed to malloc memory for new_state",pmVar8);
                ordered_dict_free((OrderedDict *)in_stack_ffffff18,(FreeValueFunc)in_stack_ffffff1c)
                ;
                return;
              }
            }
            else {
              if (new_state != (char *)0x0) {
                free(new_state);
              }
              new_state = (char *)mg_mprintf("\"resumed\"");
              if (new_state == (char *)0x0) {
                log_log(1,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                        ,0x10c,"Failed to malloc memory for new_state");
                ordered_dict_free((OrderedDict *)in_stack_ffffff18,(FreeValueFunc)in_stack_ffffff1c)
                ;
                return;
              }
            }
          }
          pcVar9 = new_state;
          log_log(4,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                  ,0x124,"Job state changed: %s -> %s",pvVar3,new_state);
          pvVar6 = (void *)mg_mprintf("job_state:%.*s",state.len - 2,state.buf + 1);
          if (pvVar6 == (void *)0x0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                    ,299,"Failed to malloc memory for event",pvVar3,pcVar9);
            ordered_dict_free((OrderedDict *)in_stack_ffffff18,(FreeValueFunc)in_stack_ffffff1c);
            if (new_state == (char *)0x0) {
              return;
            }
            free(new_state);
            return;
          }
          JVar7 = job_event_from_string((char *)in_stack_ffffff18);
          *(JobEvent *)(in_a0 + 8) = JVar7;
          server_send_event(in_stack_ffffff18,(char *)in_stack_ffffff1c,in_stack_ffffff20);
          if (pvVar6 != (void *)0x0) {
            free(pvVar6);
          }
          server_send_event(in_stack_ffffff18,(char *)in_stack_ffffff1c,in_stack_ffffff20);
        }
        ordered_dict_free((OrderedDict *)in_stack_ffffff18,(FreeValueFunc)in_stack_ffffff1c);
        if (new_state != (char *)0x0) {
          free(new_state);
        }
      }
      mg_json_get_tok(&info_str,ps.buf,ps.len,"$.info");
      if ((info_str.len != 0) &&
         (mg_json_get_tok(&cur_layer,info_str.buf,info_str.len,"$.current_layer"),
         cur_layer.len != 0)) {
        mg_json_get_tok(&total,info_str.buf,info_str.len,"$.total_layer");
        atoi(cur_layer.buf);
        atoi(total.buf);
        server_send_event(in_stack_ffffff18,(char *)in_stack_ffffff1c,in_stack_ffffff20);
      }
      ofs = 0;
      while (ofs = mg_json_next(ps.buf,ps.len,ofs,&key,&val), ofs != 0) {
        if ((key.len < 3) || (val.len == 0)) {
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                  ,0x14c,"Failed to parse print_stats");
        }
        else {
          pvVar3 = (void *)mg_mprintf(&DAT_00498134,key.len - 2,key.buf + 1);
          if (pvVar3 == (void *)0x0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                    ,0x152,"Failed to malloc memory for key_str");
          }
          else {
            iVar5 = mg_mprintf(&DAT_00498134,val.len,val.buf);
            if (iVar5 == 0) {
              log_log(1,
                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/job_state.c"
                      ,0x158,"Failed to malloc memory for val_str");
              if (pvVar3 != (void *)0x0) {
                free(pvVar3);
              }
            }
            else {
              ordered_dict_add((OrderedDict *)in_stack_ffffff18,(char *)in_stack_ffffff1c,
                               in_stack_ffffff20,in_stack_ffffff24);
              if (pvVar3 != (void *)0x0) {
                free(pvVar3);
              }
            }
          }
        }
      }
    }
  }
  return;
}



// === _process_status_update @ 0043f300 ===

/* WARNING: Unknown calling convention */

void _process_status_update(void *args,mg_str data)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  KlippyState KVar4;
  char *pcVar5;
  OrderedDict *pOVar6;
  char *__needle;
  char *pcVar7;
  size_t sVar8;
  void *__ptr;
  char *pcVar9;
  uint uVar10;
  long lVar11;
  int *in_a0;
  undefined4 in_a1;
  int in_a2;
  Server *in_stack_fffffef0;
  cJSON *in_stack_fffffef4;
  void *in_stack_fffffef8;
  FreeValueFunc in_stack_fffffefc;
  OrderedDictEntry *current;
  size_t ofs;
  char *value;
  size_t sub_ofs;
  Klippy *klippy;
  Server *server;
  char *status;
  cJSON *status_json;
  char *msg;
  char *state;
  KlippyState new_state;
  char *conn_id;
  char *sub_dict;
  OrderedDict *conn_status;
  char *conn_status_json;
  long c_id;
  char *name_path;
  char *fields_list;
  char *field;
  char *name_str;
  undefined4 local_98;
  undefined4 local_94;
  mg_str params_str;
  mg_str status_str;
  mg_str eventtime_str;
  mg_str webhooks_str;
  mg_str state_message_str;
  mg_str state_str;
  mg_str name;
  mg_str fields;
  mg_str sub_obj;
  mg_str val;
  mg_iobuf io;
  mg_str k;
  mg_str v;
  mg_iobuf iobuf;
  char *endptr;
  
  if (((in_a0 != (int *)0x0) && (*in_a0 != 0)) && (in_a2 != 0)) {
    mg_json_get_tok(&params_str,in_a1,in_a2,"$.params");
    if (params_str.len == 0) {
      log_log(2,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
              ,0x488,"Invalid status update: %.*s",in_a2,in_a1);
    }
    else {
      mg_json_get_tok(&status_str,params_str.buf,params_str.len,"$.status");
      if (status_str.len != 0) {
        pvVar2 = (void *)mg_mprintf(&DAT_00498b30,status_str.len,status_str.buf);
        if (pvVar2 == (void *)0x0) {
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                  ,0x3cd,"Failed to allocate memory for status.");
        }
        else {
          iVar3 = cJSON_Parse(pvVar2);
          if (iVar3 == 0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                    ,0x3c8,"Failed to parse status JSON: %s",pvVar2);
          }
          else {
            pthread_rwlock_wrlock((pthread_rwlock_t *)(in_a0 + 0x2f));
            merge_cjson_object((cJSON *)in_stack_fffffef0,in_stack_fffffef4);
            pthread_rwlock_unlock((pthread_rwlock_t *)(in_a0 + 0x2f));
            cJSON_Delete(iVar3);
          }
        }
        if (pvVar2 != (void *)0x0) {
          free(pvVar2);
        }
        mg_json_get_tok(&webhooks_str,status_str.buf,status_str.len,"$.webhooks");
        if (webhooks_str.len != 0) {
          mg_json_get_tok(&state_message_str,webhooks_str.buf,webhooks_str.len,"$.state_message");
          if (state_message_str.len != 0) {
            iVar3 = mg_mprintf(&DAT_00498b30,state_message_str.len,state_message_str.buf);
            if (iVar3 == 0) {
              log_log(1,
                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                      ,0x3da,"Failed to allocate memory for state message.");
            }
            else {
              if (in_a0[2] != 0) {
                free((void *)in_a0[2]);
                in_a0[2] = 0;
              }
              in_a0[2] = iVar3;
            }
          }
          mg_json_get_tok(&state_str,webhooks_str.buf,webhooks_str.len,"$.state");
          if (state_str.len != 0) {
            pvVar2 = (void *)mg_mprintf(&DAT_00498b30,state_str.len - 2,state_str.buf + 1);
            if (pvVar2 == (void *)0x0) {
              log_log(1,
                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                      ,1000,"Failed to allocate memory for state.");
            }
            else {
              pcVar5 = klippy_state_to_string((KlippyState)in_stack_fffffef0);
              log_log(3,
                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                      ,0x3ec,"Klippy state transition: {%s} -> {%s}",pcVar5,pvVar2);
              KVar4 = klippy_state_from_string((char *)in_stack_fffffef0);
              if (pvVar2 != (void *)0x0) {
                free(pvVar2);
              }
              if (((KVar4 == KLIPPY_STATE_SHUTDOWN) && (*(char *)((int)in_a0 + 0x31) != '\x01')) &&
                 (in_a0[1] != 4)) {
                server_send_event(in_stack_fffffef0,(char *)in_stack_fffffef4,in_stack_fffffef8);
              }
              in_a0[1] = KVar4;
            }
          }
        }
      }
      mg_json_get_tok(&eventtime_str,params_str.buf,params_str.len,"$.eventtime");
      if ((status_str.len == 0) || (eventtime_str.len == 0)) {
        log_log(2,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                ,0x3fb,"Invalid status update: %.*s",in_a2,in_a1);
      }
      else {
        pthread_rwlock_rdlock((pthread_rwlock_t *)(in_a0[0x2d] + 0x14));
        current = *(OrderedDictEntry **)(in_a0[0x2d] + 0xc);
        while (current != (OrderedDictEntry *)0x0) {
          pcVar5 = current->key;
          pvVar2 = current->value;
          pOVar6 = ordered_dict_create();
          if (pOVar6 == (OrderedDict *)0x0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                    ,0x408,"Failed to allocate memory for connection status.");
            current = current->list_next;
          }
          else {
            if ((pcVar5 == (char *)0x0) || (pvVar2 == (void *)0x0)) {
              log_log(2,
                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                      ,0x47e,"Invalid subscription for connection: %s",pcVar5);
            }
            else {
              mg_str_s(&sub_obj,pvVar2);
              ofs = 0;
              while (ofs = mg_json_next(sub_obj.buf,sub_obj.len,ofs,&name,&fields), ofs != 0) {
                if ((2 < name.len) && (fields.len != 0)) {
                  pvVar2 = (void *)mg_mprintf("$.%.*s",name.len - 2,name.buf + 1);
                  mg_json_get_tok(&val,status_str.buf,status_str.len,pvVar2);
                  if (val.len != 0) {
                    mg_str_s(&local_98,&DAT_00498b90);
                    iVar3 = mg_strcmp(fields.buf,fields.len,local_98,local_94);
                    if (iVar3 == 0) {
                      value = (char *)mg_mprintf(&DAT_00498b30,val.len,val.buf);
                    }
                    else {
                      io.buf = (uchar *)0x0;
                      io.size = 0;
                      io.len = 0;
                      io.align = 0x40;
                      sub_ofs = 0;
                      while (sub_ofs = mg_json_next(val.buf,val.len,sub_ofs,&k,&v), sub_ofs != 0) {
                        if ((k.len != 0) && (v.len != 0)) {
                          pcVar9 = (char *)mg_mprintf(&DAT_00498b30,fields.len,fields.buf);
                          if (pcVar9 == (char *)0x0) {
                            log_log(1,
                                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                                    ,0x42e,"Failed to allocate memory for fields list.");
                          }
                          else {
                            __needle = (char *)mg_mprintf(&DAT_00498b30,k.len,k.buf);
                            if (__needle == (char *)0x0) {
                              log_log(1,
                                      "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                                      ,0x434,"Failed to allocate memory for field.");
                              if (pcVar9 != (char *)0x0) {
                                free(pcVar9);
                              }
                            }
                            else {
                              pcVar7 = strstr(pcVar9,__needle);
                              if (pcVar7 != (char *)0x0) {
                                mg_xprintf(mg_pfn_iobuf,&io,"%.*s: %.*s,",k.len,k.buf,v.len,v.buf);
                              }
                              if (pcVar9 != (char *)0x0) {
                                free(pcVar9);
                              }
                              if (__needle != (char *)0x0) {
                                free(__needle);
                              }
                            }
                          }
                        }
                      }
                      if ((io.len != 0) && (io.buf[io.len - 1] == ',')) {
                        mg_iobuf_del(&io,io.len - 1,1);
                      }
                      value = (char *)mg_mprintf("{%.*s}",io.len,io.buf);
                      mg_iobuf_free(&io);
                    }
                    if ((value == (char *)0x0) || (sVar8 = strlen(value), sVar8 < 3)) {
                      if (value != (char *)0x0) {
                        free(value);
                      }
                    }
                    else {
                      __ptr = (void *)mg_mprintf(&DAT_00498b30,name.len - 2,name.buf + 1);
                      ordered_dict_add((OrderedDict *)in_stack_fffffef0,(char *)in_stack_fffffef4,
                                       in_stack_fffffef8,in_stack_fffffefc);
                      if (__ptr != (void *)0x0) {
                        free(__ptr);
                      }
                    }
                  }
                  if (pvVar2 != (void *)0x0) {
                    free(pvVar2);
                  }
                }
              }
              pcVar9 = ordered_dict_to_json((OrderedDict *)in_stack_fffffef0);
              if (pcVar9 == (char *)0x0) {
                log_log(1,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                        ,0x458,"Failed to allocate memory for connection status JSON.");
              }
              else {
                iVar3 = strncmp(pcVar5,"Internal",8);
                if (iVar3 == 0) {
                  server_send_event(in_stack_fffffef0,(char *)in_stack_fffffef4,in_stack_fffffef8);
                }
                else {
                  uVar10 = ordered_dict_count((OrderedDict *)in_stack_fffffef0);
                  if (uVar10 != 0) {
                    iobuf.buf = (uchar *)0x0;
                    iobuf.size = 0;
                    iobuf.len = 0;
                    iobuf.align = 0x40;
                    mg_xprintf(mg_pfn_iobuf,&iobuf,
                               "{\"jsonrpc\":\"2.0\",\"method\":\"notify_status_update\",\"params\":[%s,%.*s]}"
                               ,pcVar9,eventtime_str.len,eventtime_str.buf);
                    endptr = (char *)0x0;
                    lVar11 = strtol(pcVar5,&endptr,10);
                    if ((pcVar5 == endptr) || (*endptr != '\0')) {
                      log_log(1,
                              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                              ,0x46b,"Invalid connection ID: %s",pcVar5);
                      mg_iobuf_free(&iobuf);
                      if (pcVar9 != (char *)0x0) {
                        free(pcVar9);
                      }
                      goto LAB_0043fed8;
                    }
                    cVar1 = mg_wakeup(*(undefined4 *)*in_a0,lVar11,&iobuf,0x10);
                    if (cVar1 != '\x01') {
                      log_log(1,
                              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/klippy.c"
                              ,0x474,"Failed to wake up connection %lu",lVar11);
                      mg_iobuf_free(&iobuf);
                    }
                  }
                }
                if (pcVar9 != (char *)0x0) {
                  free(pcVar9);
                }
              }
            }
LAB_0043fed8:
            ordered_dict_free((OrderedDict *)in_stack_fffffef0,(FreeValueFunc)in_stack_fffffef4);
            current = current->list_next;
          }
        }
        pthread_rwlock_unlock((pthread_rwlock_t *)(in_a0[0x2d] + 0x14));
      }
    }
  }
  return;
}



// === machine_update_system_info @ 0044868c ===

/* WARNING: Unknown calling convention */

void machine_update_system_info(Machine *machine)

{
  char *pcVar1;
  int iVar2;
  int in_a0;
  Machine *in_stack_ffffffc8;
  char *in_stack_ffffffcc;
  void *in_stack_ffffffd0;
  FreeValueFunc in_stack_ffffffd4;
  char *cpu_info;
  char *sd_info;
  char *dist_info;
  char *virtual_info;
  char *network_info;
  char *canbus_info;
  
  if (in_a0 != 0) {
    pcVar1 = machine_get_cpu_info(in_stack_ffffffc8);
    if (pcVar1 != (char *)0x0) {
      ordered_dict_add((OrderedDict *)in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                       in_stack_ffffffd4);
    }
    pcVar1 = machine_get_sdcard_info(in_stack_ffffffc8);
    if (pcVar1 != (char *)0x0) {
      ordered_dict_add((OrderedDict *)in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                       in_stack_ffffffd4);
    }
    pcVar1 = machine_get_dist_info(in_stack_ffffffc8);
    if (pcVar1 != (char *)0x0) {
      ordered_dict_add((OrderedDict *)in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                       in_stack_ffffffd4);
    }
    pcVar1 = machine_get_virtual_info(in_stack_ffffffc8);
    if (pcVar1 != (char *)0x0) {
      ordered_dict_add((OrderedDict *)in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                       in_stack_ffffffd4);
    }
    iVar2 = mg_mprintf(&DAT_0049b038);
    if (iVar2 != 0) {
      ordered_dict_add((OrderedDict *)in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                       in_stack_ffffffd4);
    }
    iVar2 = mg_mprintf(&DAT_0049b038);
    if (iVar2 != 0) {
      ordered_dict_add((OrderedDict *)in_stack_ffffffc8,in_stack_ffffffcc,in_stack_ffffffd0,
                       in_stack_ffffffd4);
    }
  }
  return;
}



// === kisslicer_parse_filament_total @ 0044f9b8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention */

_Bool kisslicer_parse_filament_total(char *pattern,char *data,double *outfloat)

{
  _Bool _Var1;
  void *__s;
  undefined3 extraout_var;
  int in_a0;
  int in_a1;
  undefined8 *in_a2;
  char *in_stack_ffffffb8;
  char *in_stack_ffffffbc;
  size_t *in_stack_ffffffc0;
  double **in_stack_ffffffc4;
  double total;
  size_t i;
  double *filament_matches;
  size_t inSize;
  size_t outCnt;
  undefined4 local_c;
  
  local_c = 0;
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == (undefined8 *)0x0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0x975,"point is null.");
  }
  else {
    outCnt = 0;
    __s = malloc(800);
    if (__s != (void *)0x0) {
      memset(__s,0,800);
      _Var1 = regex_find_floats(in_stack_ffffffb8,in_stack_ffffffbc,in_stack_ffffffc0,
                                in_stack_ffffffc4,&outCnt);
      if ((CONCAT31(extraout_var,_Var1) != 0) && (outCnt != 0)) {
        if (outCnt != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        local_c = 0;
        *in_a2 = 0;
        if (__s != (void *)0x0) {
          free(__s);
        }
        return true;
      }
      if (__s != (void *)0x0) {
        free(__s);
      }
    }
  }
  return false;
}



// === cura_parse_filament_total @ 004514ac ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention */

int cura_parse_filament_total
              (metadata_path_info_st *pM_PathInfo,metadata_info_st *metaData,void *userData)

{
  _Bool _Var1;
  int iVar2;
  undefined3 extraout_var;
  int in_a0;
  int in_a1;
  int in_a2;
  char *in_stack_ffffffb8;
  char *in_stack_ffffffbc;
  double *in_stack_ffffffc0;
  metadata_parse_data_st *pMetaPraseData;
  double fDat;
  
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xaf3,"point is null.");
    iVar2 = -1;
  }
  else if (((*(int *)(in_a2 + 4) == 0) || (*(int *)(in_a2 + 8) == 0)) ||
          ((*(int *)(in_a2 + 0x18) == 0 || (**(int **)(in_a2 + 0x18) == 0)))) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xafa,"point is null.");
    iVar2 = -2;
  }
  else {
    _Var1 = regex_find_float(in_stack_ffffffb8,in_stack_ffffffbc,in_stack_ffffffc0);
    if (CONCAT31(extraout_var,_Var1) != 0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
      halt_baddata();
    }
    iVar2 = 0;
  }
  return iVar2;
}



// === cura_parse_filament_weight_total @ 004516b4 ===

/* WARNING: Unknown calling convention */

int cura_parse_filament_weight_total
              (metadata_path_info_st *pM_PathInfo,metadata_info_st *metaData,void *userData)

{
  _Bool _Var1;
  int iVar2;
  undefined3 extraout_var;
  int in_a0;
  metadata_info_st *in_a1;
  int in_a2;
  char *in_stack_ffffffb8;
  char *in_stack_ffffffbc;
  double *in_stack_ffffffc0;
  metadata_parse_data_st *pMetaPraseData;
  double fDat;
  
  if (((in_a0 == 0) || (in_a1 == (metadata_info_st *)0x0)) || (in_a2 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xb0c,"point is null.");
    iVar2 = -1;
  }
  else if (((*(int *)(in_a2 + 4) == 0) || (*(int *)(in_a2 + 8) == 0)) ||
          ((*(int *)(in_a2 + 0x18) == 0 || (**(int **)(in_a2 + 0x18) == 0)))) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xb13,"point is null.");
    iVar2 = -2;
  }
  else {
    _Var1 = regex_find_float(in_stack_ffffffb8,in_stack_ffffffbc,in_stack_ffffffc0);
    if (CONCAT31(extraout_var,_Var1) != 0) {
      log_log(5,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
              ,0xb1a,",\"%s\":%f",**(undefined4 **)(in_a2 + 0x18));
      meta_mprintf(in_a1,",\"%s\":%f",**(undefined4 **)(in_a2 + 0x18));
    }
    iVar2 = 0;
  }
  return iVar2;
}



// === PrusaSlicer_parse_filament_total @ 00454dc8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x00455028) */
/* WARNING: Unknown calling convention */

int PrusaSlicer_parse_filament_total
              (metadata_path_info_st *pM_PathInfo,metadata_info_st *metaData,void *userData)

{
  _Bool _Var1;
  int iVar2;
  undefined3 extraout_var;
  double *pdVar3;
  int in_a0;
  int in_a1;
  int in_a2;
  char *in_stack_fffffbb0;
  size_t *in_stack_fffffbb4;
  char character;
  char *in_stack_fffffbb8;
  size_t in_stack_fffffbbc;
  double sum;
  size_t i;
  metadata_parse_data_st *pMetaPraseData;
  double *fDatArry;
  char str [1024];
  size_t size;
  
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) {
    log_log(2,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xe2e,"point is null.");
    iVar2 = -1;
  }
  else if (((*(int *)(in_a2 + 4) == 0) || (*(int *)(in_a2 + 8) == 0)) ||
          ((*(int *)(in_a2 + 0x18) == 0 || (**(int **)(in_a2 + 0x18) == 0)))) {
    log_log(2,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xe35,"point is null.");
    iVar2 = -2;
  }
  else {
    memset(str,0,0x400);
    _Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                              in_stack_fffffbbc);
    character = (char)in_stack_fffffbb8;
    if (CONCAT31(extraout_var,_Var1) != 0) {
      str[0x3ff] = '\0';
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      escape_quotes(in_stack_fffffbb0,(size_t)in_stack_fffffbb4);
      pdVar3 = str_to_float_array(in_stack_fffffbb0,in_stack_fffffbb4);
      if (pdVar3 != (double *)0x0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}



// === PrusaSlicer_parse_filament_weight_total @ 004551a0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x00455400) */
/* WARNING: Unknown calling convention */

int PrusaSlicer_parse_filament_weight_total
              (metadata_path_info_st *pM_PathInfo,metadata_info_st *metaData,void *userData)

{
  _Bool _Var1;
  int iVar2;
  undefined3 extraout_var;
  double *pdVar3;
  int in_a0;
  int in_a1;
  int in_a2;
  char *in_stack_fffffbb0;
  size_t *in_stack_fffffbb4;
  char character;
  char *in_stack_fffffbb8;
  size_t in_stack_fffffbbc;
  double sum;
  size_t i;
  metadata_parse_data_st *pMetaPraseData;
  double *fDatArry;
  char str [1024];
  size_t size;
  
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) {
    log_log(2,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xe61,"point is null.");
    iVar2 = -1;
  }
  else if (((*(int *)(in_a2 + 4) == 0) || (*(int *)(in_a2 + 8) == 0)) ||
          ((*(int *)(in_a2 + 0x18) == 0 || (**(int **)(in_a2 + 0x18) == 0)))) {
    log_log(2,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0xe68,"point is null.");
    iVar2 = -2;
  }
  else {
    memset(str,0,0x400);
    _Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                              in_stack_fffffbbc);
    character = (char)in_stack_fffffbb8;
    if (CONCAT31(extraout_var,_Var1) != 0) {
      str[0x3ff] = '\0';
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      escape_quotes(in_stack_fffffbb0,(size_t)in_stack_fffffbb4);
      pdVar3 = str_to_float_array(in_stack_fffffbb0,in_stack_fffffbb4);
      if (pdVar3 != (double *)0x0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}



// === creality_parse_filament_total @ 004581a8 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x00458468) */
/* WARNING: Unknown calling convention */

int creality_parse_filament_total
              (metadata_path_info_st *pM_PathInfo,metadata_info_st *metaData,void *userData)

{
  _Bool _Var1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  double *pdVar3;
  int in_a0;
  int in_a1;
  int in_a2;
  char *in_stack_fffffbb0;
  size_t *in_stack_fffffbb4;
  char character;
  char *in_stack_fffffbb8;
  size_t in_stack_fffffbbc;
  double sum;
  size_t i;
  metadata_parse_data_st *pMetaPraseData;
  double *fDatArry;
  char str [1024];
  size_t size;
  
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0x10ec,"point is null.");
    iVar2 = -1;
  }
  else if (((*(int *)(in_a2 + 4) == 0) || (*(int *)(in_a2 + 8) == 0)) ||
          ((*(int *)(in_a2 + 0x18) == 0 || (**(int **)(in_a2 + 0x18) == 0)))) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0x10f3,"point is null.");
    iVar2 = -2;
  }
  else {
    memset(str,0,0x400);
    _Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                              in_stack_fffffbbc);
    if (((CONCAT31(extraout_var,_Var1) != 0) ||
        (_Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                                   in_stack_fffffbbc), CONCAT31(extraout_var_00,_Var1) != 0)) ||
       (_Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                                  in_stack_fffffbbc), CONCAT31(extraout_var_01,_Var1) != 0)) {
      character = (char)in_stack_fffffbb8;
      str[0x3ff] = '\0';
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      escape_quotes(in_stack_fffffbb0,(size_t)in_stack_fffffbb4);
      pdVar3 = str_to_float_array(in_stack_fffffbb0,in_stack_fffffbb4);
      if (pdVar3 != (double *)0x0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}



// === creality_parse_filament_weight_total @ 004585e0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Removing unreachable block (ram,0x00458870) */
/* WARNING: Unknown calling convention */

int creality_parse_filament_weight_total
              (metadata_path_info_st *pM_PathInfo,metadata_info_st *metaData,void *userData)

{
  _Bool _Var1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  double *pdVar3;
  int in_a0;
  int in_a1;
  int in_a2;
  char *in_stack_fffffbb0;
  size_t *in_stack_fffffbb4;
  char character;
  char *in_stack_fffffbb8;
  size_t in_stack_fffffbbc;
  double sum;
  size_t i;
  metadata_parse_data_st *pMetaPraseData;
  double *fDatArry;
  char str [1024];
  size_t size;
  
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0x1120,"point is null.");
    iVar2 = -1;
  }
  else if (((*(int *)(in_a2 + 4) == 0) || (*(int *)(in_a2 + 8) == 0)) ||
          ((*(int *)(in_a2 + 0x18) == 0 || (**(int **)(in_a2 + 0x18) == 0)))) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/metadata.c"
            ,0x1127,"point is null.");
    iVar2 = -2;
  }
  else {
    memset(str,0,0x400);
    _Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                              in_stack_fffffbbc);
    if ((CONCAT31(extraout_var,_Var1) != 0) ||
       (_Var1 = regex_find_string(in_stack_fffffbb0,(char *)in_stack_fffffbb4,in_stack_fffffbb8,
                                  in_stack_fffffbbc), CONCAT31(extraout_var_00,_Var1) != 0)) {
      character = (char)in_stack_fffffbb8;
      str[0x3ff] = '\0';
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      strlen(str);
      trim_character(in_stack_fffffbb0,(size_t)in_stack_fffffbb4,character);
      escape_quotes(in_stack_fffffbb0,(size_t)in_stack_fffffbb4);
      pdVar3 = str_to_float_array(in_stack_fffffbb0,in_stack_fffffbb4);
      if (pdVar3 != (double *)0x0) {
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}



// === _handle_stat_update @ 00459b14 ===

/* WARNING: Unknown calling convention */

void _handle_stat_update(void *arg)

{
  undefined4 *puVar1;
  int *piVar2;
  int in_a0;
  ProcStats *in_stack_ffffffd0;
  ListNode *current;
  ProcStats *proc_stats;
  LinkedList *callbacks;
  StatCallbackNode *callback_node;
  
  if (in_a0 != 0) {
    proc_stats_update_status(in_stack_ffffffd0);
    puVar1 = *(undefined4 **)(in_a0 + 0x40);
    pthread_rwlock_rdlock((pthread_rwlock_t *)(puVar1 + 3));
    for (current = (ListNode *)*puVar1; current != (ListNode *)0x0; current = current->next) {
      piVar2 = current->data;
      if (*piVar2 != 0) {
        (*(code *)*piVar2)(piVar2[1],*(undefined4 *)(in_a0 + 0x30));
      }
    }
    pthread_rwlock_unlock((pthread_rwlock_t *)(puVar1 + 3));
    *(int *)(in_a0 + 0x30) = *(int *)(in_a0 + 0x30) + 1;
  }
  return;
}



// === proc_stats_update_cpu_stats @ 0045aa40 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention */

void proc_stats_update_cpu_stats(ProcStats *proc_stats)

{
  size_t sVar1;
  undefined4 uVar2;
  int iVar3;
  FILE *__stream;
  uint uVar4;
  void *__ptr;
  char *pcVar5;
  undefined4 uVar6;
  int in_a0;
  longlong *plVar7;
  longlong lVar8;
  longlong cpu_sum;
  int i;
  size_t ofs;
  size_t i_1;
  FILE *cpu_file;
  longlong cpu_idle;
  char *path;
  longlong cpu_sum_delta;
  longlong cpu_idle_delta;
  longlong cpu_used;
  double cpu_usage_percent;
  undefined4 local_2b8;
  undefined4 local_2b4;
  mg_iobuf cpu_usage_iobuf;
  mg_iobuf cpu_stats_iobuf;
  mg_str last_cpu_stats_obj;
  longlong last_cpu_sum;
  longlong last_cpu_idle;
  longlong *last_cpu_data [2];
  mg_str val;
  mg_str obj;
  char cpu_name [256];
  char line [256];
  longlong cpu_data [10];
  
  if (in_a0 == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
            ,299,"Invalid argument.");
  }
  else {
    iVar3 = mg_iobuf_init(&cpu_usage_iobuf,0,0x200);
    if (iVar3 == 0) {
      log_log(2,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
              ,0x131,"Failed to update cpu_usage. Reason: Failed to initialize cpu_usage_iobuf.");
    }
    else {
      iVar3 = mg_iobuf_init(&cpu_stats_iobuf,0,0x200);
      if (iVar3 == 0) {
        log_log(2,
                "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
                ,0x136,"Failed to update cpu_usage. Reason: Failed to initialize cpu_stats_iobuf.");
        mg_iobuf_free(&cpu_usage_iobuf);
      }
      else {
        __stream = fopen("/proc/stat","r");
        if (__stream != (FILE *)0x0) {
          while (pcVar5 = fgets(line,0x100,__stream), pcVar5 != (char *)0x0) {
            pcVar5 = strstr(line,"cpu");
            if (pcVar5 != (char *)0x0) {
              memset(cpu_name,0,0x100);
              memset(cpu_data,0,0x50);
              __isoc99_sscanf(line,"%s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",cpu_name,
                              cpu_data,cpu_data + 1,cpu_data + 2,cpu_data + 3,cpu_data + 4,
                              cpu_data + 5,cpu_data + 6,cpu_data + 7,cpu_data + 8,cpu_data + 9);
              uVar2 = cpu_data[3]._4_4_;
              uVar6 = (undefined4)cpu_data[3];
              cpu_sum._0_4_ = 0;
              cpu_sum._4_4_ = 0;
              for (i = 0; i < 10; i = i + 1) {
                uVar4 = (uint)cpu_sum + (int)cpu_data[i];
                cpu_sum._4_4_ =
                     (uint)(uVar4 < (uint)cpu_sum) +
                     cpu_sum._4_4_ + *(int *)((int)cpu_data + i * 8 + 4);
                cpu_sum._0_4_ = uVar4;
              }
              __ptr = (void *)mg_mprintf(&DAT_0049cd14,cpu_name);
              if (__ptr == (void *)0x0) {
                log_log(1,
                        "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
                        ,0x153,"Failed to create path.");
              }
              else {
                mg_str_s(&local_2b8,*(undefined4 *)(in_a0 + 0x34));
                mg_json_get_tok(&last_cpu_stats_obj,local_2b8,local_2b4,__ptr);
                if (__ptr != (void *)0x0) {
                  free(__ptr);
                }
                sVar1 = last_cpu_stats_obj.len;
                pcVar5 = last_cpu_stats_obj.buf;
                if (last_cpu_stats_obj.len != 0) {
                  last_cpu_sum._0_4_ = 0;
                  last_cpu_sum._4_4_ = 0;
                  last_cpu_idle._0_4_ = 0;
                  last_cpu_idle._4_4_ = 0;
                  last_cpu_data[0] = &last_cpu_sum;
                  last_cpu_data[1] = &last_cpu_idle;
                  ofs = 0;
                  for (i_1 = 0; (ofs = mg_json_next(pcVar5,sVar1,ofs,0,&val), ofs != 0 && (i_1 < 2))
                      ; i_1 = i_1 + 1) {
                    plVar7 = last_cpu_data[i_1];
                    lVar8 = strtoll(val.buf,(char **)0x0,10);
                    *plVar7 = lVar8;
                  }
                  if ((uint)cpu_sum != (uint)last_cpu_sum ||
                      cpu_sum._4_4_ - last_cpu_sum._4_4_ !=
                      (uint)((uint)cpu_sum < (uint)cpu_sum - (uint)last_cpu_sum)) {
                    /* WARNING: Bad instruction - Truncating control flow here */
                    halt_baddata();
                  }
                  mg_xprintf(mg_pfn_iobuf,&cpu_usage_iobuf,"\"%s\": %f,",cpu_name,0);
                }
                mg_xprintf(mg_pfn_iobuf,&cpu_stats_iobuf,"\"%s\":[%llu,%llu],",cpu_name,
                           (uint)cpu_sum,cpu_sum._4_4_,uVar6,uVar2);
              }
            }
          }
          fclose(__stream);
          if (*(int *)(in_a0 + 0xc) != 0) {
            free(*(void **)(in_a0 + 0xc));
            *(undefined4 *)(in_a0 + 0xc) = 0;
          }
          if (cpu_usage_iobuf.len == 0) {
            iVar3 = 0;
          }
          else {
            iVar3 = cpu_usage_iobuf.len - 1;
          }
          uVar6 = mg_mprintf("{%.*s}",iVar3,cpu_usage_iobuf.buf);
          *(undefined4 *)(in_a0 + 0xc) = uVar6;
          if (*(int *)(in_a0 + 0xc) == 0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
                    ,0x172,"Failed to create cpu_usage.");
          }
          if (*(int *)(in_a0 + 0x34) != 0) {
            free(*(void **)(in_a0 + 0x34));
            *(undefined4 *)(in_a0 + 0x34) = 0;
          }
          if (cpu_stats_iobuf.len == 0) {
            iVar3 = 0;
          }
          else {
            iVar3 = cpu_stats_iobuf.len - 1;
          }
          uVar6 = mg_mprintf("{%.*s}",iVar3,cpu_stats_iobuf.buf);
          *(undefined4 *)(in_a0 + 0x34) = uVar6;
          if (*(int *)(in_a0 + 0x34) == 0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
                    ,0x178,"Failed to create last_cpu_stats.");
          }
        }
        mg_iobuf_free(&cpu_usage_iobuf);
        mg_iobuf_free(&cpu_stats_iobuf);
      }
    }
  }
  return;
}



// === proc_stats_update_mem_stats @ 0045b1a8 ===

/* WARNING: Unknown calling convention */

void proc_stats_update_mem_stats(ProcStats *proc_stats)

{
  FILE *__stream;
  char *pcVar1;
  uint uVar2;
  undefined4 uVar3;
  int in_a0;
  int iVar4;
  FILE *mem_file;
  longlong mem_used;
  longlong mem_total;
  longlong mem_avail;
  char line [256];
  
  if (in_a0 == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
            ,0x186,"Invalid argument.");
  }
  else {
    __stream = fopen("/proc/meminfo","r");
    if (__stream != (FILE *)0x0) {
      mem_total._0_4_ = 0;
      mem_total._4_4_ = 0;
      mem_avail._0_4_ = 0;
      mem_avail._4_4_ = 0;
      do {
        while( true ) {
          pcVar1 = fgets(line,0x100,__stream);
          if (pcVar1 == (char *)0x0) goto LAB_0045b2f0;
          pcVar1 = strstr(line,"MemTotal:");
          if (pcVar1 == (char *)0x0) break;
          __isoc99_sscanf(line,"MemTotal:%lld",&mem_total);
        }
        pcVar1 = strstr(line,"MemAvailable:");
      } while (pcVar1 == (char *)0x0);
      __isoc99_sscanf(line,"MemAvailable:%lld",&mem_avail);
LAB_0045b2f0:
      fclose(__stream);
      uVar2 = (uint)mem_total - (int)mem_avail;
      iVar4 = (mem_total._4_4_ - mem_avail._4_4_) - (uint)((uint)mem_total < uVar2);
      if (*(int *)(in_a0 + 0x10) != 0) {
        free(*(void **)(in_a0 + 0x10));
        *(undefined4 *)(in_a0 + 0x10) = 0;
      }
      uVar3 = mg_mprintf("{\"total\": %lld, \"available\": %lld, \"used\": %lld}",iVar4,
                         (uint)mem_total,mem_total._4_4_,(int)mem_avail,mem_avail._4_4_,uVar2,iVar4)
      ;
      *(undefined4 *)(in_a0 + 0x10) = uVar3;
    }
  }
  return;
}



// === proc_stats_update_net_stats @ 0045b3b0 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention */

void proc_stats_update_net_stats(ProcStats *proc_stats,double time_diff)

{
  size_t sVar1;
  int iVar2;
  FILE *__stream;
  size_t sVar3;
  char *pcVar4;
  void *__ptr;
  undefined4 uVar5;
  int in_a0;
  char *net_stats;
  int i;
  size_t ofs;
  double bytes_sec;
  FILE *net_file;
  size_t pos;
  char *dev_stats;
  char *path;
  double cur_total;
  double last_total;
  undefined4 local_2b8;
  undefined4 local_2b4;
  mg_iobuf net_iobuf;
  mg_str dev_name_1;
  mg_str dev_stats_1;
  mg_str obj;
  mg_str last_dev_stats;
  double rx_bytes;
  double tx_bytes;
  char dev_name [256];
  char line [256];
  ulonglong all_bytes [12];
  
  net_stats = (char *)0x0;
  if (in_a0 == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
            ,0x1ab,"Invalid argument.");
  }
  else {
    iVar2 = mg_iobuf_init(&net_iobuf,0,0x200);
    if (iVar2 == 0) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
              ,0x1b0,"Failed to initialize net_iobuf.");
    }
    else {
      __stream = fopen("/proc/net/dev","r");
      if (__stream != (FILE *)0x0) {
        while (pcVar4 = fgets(line,0x100,__stream), pcVar4 != (char *)0x0) {
          pcVar4 = strchr(line,0x3a);
          if (pcVar4 != (char *)0x0) {
            memset(dev_name,0,0x100);
            for (i = 0; line[i] != ':'; i = i + 1) {
              if (line[i] != ' ') {
                pcVar4 = strchr(line,0x3a);
                strncat(dev_name,line + i,(int)pcVar4 - (int)(line + i));
                break;
              }
            }
            sVar3 = strcspn(line,":");
            memset(all_bytes,0,0x60);
            __isoc99_sscanf(line + sVar3 + 1,
                            "%llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",all_bytes,
                            all_bytes + 1,all_bytes + 2,all_bytes + 3,all_bytes + 4,all_bytes + 5,
                            all_bytes + 6,all_bytes + 7,all_bytes + 8,all_bytes + 9,all_bytes + 10,
                            all_bytes + 0xb);
            pcVar4 = (char *)mg_mprintf("\"%s\":{                        \"rx_bytes\": %llu,\"tx_bytes\": %llu,                        \"rx_packets\": %llu,\"tx_packets\": %llu,                        \"rx_errs\": %llu,\"tx_errs\": %llu,                        \"rx_drop\": %llu,\"tx_drop\": %llu},"
                                        ,dev_name,(undefined4)all_bytes[0],all_bytes[0]._4_4_,
                                        (undefined4)all_bytes[8],all_bytes[8]._4_4_,
                                        (undefined4)all_bytes[1],all_bytes[1]._4_4_,
                                        (undefined4)all_bytes[9],all_bytes[9]._4_4_,
                                        (undefined4)all_bytes[2],all_bytes[2]._4_4_,
                                        (undefined4)all_bytes[10],all_bytes[10]._4_4_,
                                        (undefined4)all_bytes[3],all_bytes[3]._4_4_,
                                        (undefined4)all_bytes[0xb],all_bytes[0xb]._4_4_);
            sVar1 = net_iobuf.len;
            sVar3 = strlen(pcVar4);
            mg_iobuf_add(&net_iobuf,sVar1,pcVar4,sVar3);
            free(pcVar4);
          }
        }
        fclose(__stream);
        if (net_iobuf.len == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = net_iobuf.len - 1;
        }
        net_stats = (char *)mg_mprintf("{%.*s}",iVar2,net_iobuf.buf);
        mg_iobuf_del(&net_iobuf,0,net_iobuf.len);
      }
      if (net_stats != (char *)0x0) {
        ofs = 0;
        mg_str_s(&obj,net_stats);
        while (ofs = mg_json_next(obj.buf,obj.len,ofs,&dev_name_1,&dev_stats_1), ofs != 0) {
          __ptr = (void *)mg_mprintf("$.%.*s",dev_name_1.len - 2,dev_name_1.buf + 1);
          if (__ptr == (void *)0x0) {
            log_log(1,
                    "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
                    ,0x1eb,"Failed to create path.");
          }
          else {
            mg_str_s(&local_2b8,*(undefined4 *)(in_a0 + 0x14));
            mg_json_get_tok(&last_dev_stats,local_2b8,local_2b4,__ptr);
            if (__ptr != (void *)0x0) {
              free(__ptr);
            }
            if (last_dev_stats.len != 0) {
              rx_bytes._0_4_ = 0;
              rx_bytes._4_4_ = 0;
              tx_bytes._0_4_ = 0;
              tx_bytes._4_4_ = 0;
              mg_json_get_num(dev_stats_1.buf,dev_stats_1.len,"$.rx_bytes",&rx_bytes);
              mg_json_get_num(dev_stats_1.buf,dev_stats_1.len,"$.tx_bytes",&tx_bytes);
                    /* WARNING: Bad instruction - Truncating control flow here */
              halt_baddata();
            }
            mg_xprintf(mg_pfn_iobuf,&net_iobuf,"%.*s: {%.*s, \"bandwidth\": %lf},",dev_name_1.len,
                       dev_name_1.buf,dev_stats_1.len - 2,dev_stats_1.buf + 1);
          }
        }
        if (net_stats != (char *)0x0) {
          free(net_stats);
        }
        if (*(int *)(in_a0 + 0x14) != 0) {
          free(*(void **)(in_a0 + 0x14));
          *(undefined4 *)(in_a0 + 0x14) = 0;
        }
        if (net_iobuf.len == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = net_iobuf.len - 1;
        }
        uVar5 = mg_mprintf("{%.*s}",iVar2,net_iobuf.buf);
        *(undefined4 *)(in_a0 + 0x14) = uVar5;
        if (*(int *)(in_a0 + 0x14) == 0) {
          log_log(1,
                  "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
                  ,0x205,"Failed to create net_stats.");
        }
      }
      mg_iobuf_free(&net_iobuf);
    }
  }
  return;
}



// === proc_stats_update_proc_stat_queue @ 0045bbf4 ===

/* WARNING: Unknown calling convention */

char * proc_stats_update_proc_stat_queue(ProcStats *proc_stats,double time_diff)

{
  char *pcVar1;
  int in_a0;
  clock_t current_proc_time;
  clock_t proc_time_diff;
  double proc_cpu_usage;
  FILE *mem_file;
  char *moonraker_stats;
  char *old_value;
  ulong mem;
  char mem_units [10];
  timeval time_now;
  char line [256];
  
  if (in_a0 == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
            ,0x210,"Invalid argument.");
    return (char *)0x0;
  }
  pcVar1 = (char *)clock();
  return pcVar1;
}



// === proc_stats_update_status @ 0045bee8 ===

/* WARNING: Unknown calling convention */

void proc_stats_update_status(ProcStats *proc_stats)

{
  time_t __time1;
  char *pcVar1;
  char *__ptr;
  int iVar2;
  void *__ptr_00;
  int in_a0;
  undefined *puVar3;
  undefined *puVar4;
  char *pcVar5;
  undefined *puVar6;
  Server *in_stack_ffffff98;
  char *in_stack_ffffff9c;
  void *in_stack_ffffffa0;
  undefined4 in_stack_ffffffa4;
  time_t current_update_time;
  double time_diff;
  char *moonraker_stats;
  char *cpu_temp;
  char *status;
  
  if (in_a0 == 0) {
    log_log(1,
            "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
            ,0x245,"Invalid argument.");
  }
  else {
    __time1 = time((time_t *)0x0);
    difftime(__time1,*(time_t *)(in_a0 + 0x3c));
    *(time_t *)(in_a0 + 0x3c) = __time1;
    pthread_mutex_lock((pthread_mutex_t *)(in_a0 + 0x18));
    proc_stats_update_cpu_stats((ProcStats *)in_stack_ffffff98);
    proc_stats_update_mem_stats((ProcStats *)in_stack_ffffff98);
    proc_stats_update_net_stats
              ((ProcStats *)in_stack_ffffff98,(double)CONCAT44(in_stack_ffffffa4,in_stack_ffffffa0))
    ;
    pthread_mutex_unlock((pthread_mutex_t *)(in_a0 + 0x18));
    pcVar1 = proc_stats_update_proc_stat_queue
                       ((ProcStats *)in_stack_ffffff98,
                        (double)CONCAT44(in_stack_ffffffa4,in_stack_ffffffa0));
    __ptr = proc_stats_get_cpu_temp((ProcStats *)in_stack_ffffff98);
    if (pcVar1 == (char *)0x0) {
      pcVar1 = "null";
    }
    pcVar5 = __ptr;
    if (__ptr == (char *)0x0) {
      pcVar5 = "null";
    }
    if (*(int *)(in_a0 + 0x14) == 0) {
      puVar6 = &DAT_0049cb58;
    }
    else {
      puVar6 = *(undefined **)(in_a0 + 0x14);
    }
    if (*(int *)(in_a0 + 0xc) == 0) {
      puVar3 = &DAT_0049cb58;
    }
    else {
      puVar3 = *(undefined **)(in_a0 + 0xc);
    }
    if (*(int *)(in_a0 + 0x10) == 0) {
      puVar4 = &DAT_0049cb58;
    }
    else {
      puVar4 = *(undefined **)(in_a0 + 0x10);
    }
    iVar2 = server_get_websocket_count(in_stack_ffffff98);
    __ptr_00 = (void *)mg_mprintf("{            \"moonraker_stats\": %s,            \"cpu_temp\": %s,            \"network\": %s,            \"system_cpu_usage\": %s,            \"system_memory\": %s,            \"websocket_connections\": %d        }"
                                  ,pcVar1,pcVar5,puVar6,puVar3,puVar4,iVar2);
    if (__ptr != (char *)0x0) {
      free(__ptr);
    }
    if (__ptr_00 == (void *)0x0) {
      log_log(1,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/components/proc_stats.c"
              ,0x26b,"Failed to create status.");
    }
    else {
      server_send_event(in_stack_ffffff98,in_stack_ffffff9c,in_stack_ffffffa0);
      if (__ptr_00 != (void *)0x0) {
        free(__ptr_00);
      }
    }
  }
  return;
}



// === base_provider_reboot @ 0045c5cc ===

/* WARNING: Unknown calling convention */

char * base_provider_reboot(BaseProvider *provider)

{
  int iVar1;
  int in_a0;
  BaseProvider *in_stack_ffffffd8;
  char *in_stack_ffffffdc;
  char **in_stack_ffffffe0;
  int ret;
  char *output;
  
  if (in_a0 == 0) {
    output = (char *)0x0;
  }
  else {
    output = (char *)0x0;
    iVar1 = exec_sudo_command(in_stack_ffffffd8,in_stack_ffffffdc,in_stack_ffffffe0);
    if ((iVar1 != 0) && (output = (char *)mg_mprintf("\"Failed to reboot\""), output == (char *)0x0)
       ) {
      output = (char *)0x0;
    }
  }
  return output;
}



// === update @ 004618bc ===

/* WARNING: Unknown calling convention */

int update(Set *set,char *old_item,char *new_item)

{
  _Bool _Var1;
  int iVar2;
  int in_a0;
  int in_a1;
  int in_a2;
  Set *in_stack_ffffffd8;
  char *in_stack_ffffffdc;
  
  if (((in_a0 == 0) || (in_a1 == 0)) || (in_a2 == 0)) {
    iVar2 = -4;
  }
  else {
    _Var1 = contains(in_stack_ffffffd8,in_stack_ffffffdc);
    if (_Var1) {
      remove_element(in_stack_ffffffd8,in_stack_ffffffdc);
      iVar2 = add(in_stack_ffffffd8,in_stack_ffffffdc);
    }
    else {
      log_log(4,
              "/var/jenkins_home/workspace/IngenicX2600-security-build/integrated_platform/creality/output/build/nexusprime/utils/set.c"
              ,0x9f,"Element \'%s\' not found in the set.",in_a1);
      iVar2 = 0;
    }
  }
  return iVar2;
}



// === unlock @ 004662b4 ===

void unlock(void)

{
  if (DAT_004b19c4 != (code *)0x0) {
    (*DAT_004b19c4)(0,L);
  }
  return;
}



// === mg_base64_update @ 004669d0 ===

/* WARNING: Removing unreachable block (ram,0x00466a00) */

int mg_base64_update(byte param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 local_res8;
  
  uVar2 = (param_3 & 3) % 3;
  if (uVar2 == 0) {
    uVar1 = mg_base64_encode_single(param_1 >> 2);
    *(undefined1 *)(param_2 + param_3) = uVar1;
    local_res8 = param_3 + 1;
    *(byte *)(param_2 + local_res8) = (param_1 & 3) << 4;
  }
  else if (uVar2 == 1) {
    uVar1 = mg_base64_encode_single((int)*(char *)(param_2 + param_3) | (uint)(param_1 >> 4));
    *(undefined1 *)(param_2 + param_3) = uVar1;
    local_res8 = param_3 + 1;
    *(byte *)(param_2 + local_res8) = (param_1 & 0xf) << 2;
  }
  else {
    uVar1 = mg_base64_encode_single((int)*(char *)(param_2 + param_3) | (uint)(param_1 >> 6));
    *(undefined1 *)(param_2 + param_3) = uVar1;
    uVar1 = mg_base64_encode_single(param_1 & 0x3f);
    *(undefined1 *)(param_2 + param_3 + 1) = uVar1;
    local_res8 = param_3 + 2;
  }
  return local_res8;
}



// === mg_http_bauth @ 0046bd08 ===

void mg_http_bauth(int param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  void *__dest;
  int iVar2;
  uint local_28;
  undefined4 local_24;
  int local_18;
  uint local_14;
  int local_10;
  uint local_c;
  
  mg_str_s(&local_18,param_2);
  mg_str_s(&local_10,param_3);
  uVar1 = *(int *)(param_1 + 0x50) + (local_14 + local_c) * 2 + 0x24;
  if (*(uint *)(param_1 + 0x4c) < uVar1) {
    mg_iobuf_resize(param_1 + 0x48,uVar1);
  }
  if (uVar1 <= *(uint *)(param_1 + 0x4c)) {
    local_24 = 0;
    __dest = (void *)(*(int *)(param_1 + 0x48) + *(int *)(param_1 + 0x50));
    memcpy(__dest,"Authorization: Basic ",0x15);
    for (local_28 = 0; local_28 < local_14; local_28 = local_28 + 1) {
      local_24 = mg_base64_update(*(undefined1 *)(local_18 + local_28),(int)__dest + 0x15,local_24);
    }
    if (local_c != 0) {
      local_24 = mg_base64_update(0x3a,(int)__dest + 0x15,local_24);
      for (local_28 = 0; local_28 < local_c; local_28 = local_28 + 1) {
        local_24 = mg_base64_update(*(undefined1 *)(local_10 + local_28),(int)__dest + 0x15,local_24
                                   );
      }
    }
    iVar2 = mg_base64_final((int)__dest + 0x15,local_24);
    *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + iVar2 + 0x17;
    memcpy((void *)(*(int *)(param_1 + 0x48) + *(int *)(param_1 + 0x50) + -2),&DAT_0049e36c,2);
  }
  return;
}



// === mg_md5_update @ 0047596c ===

void mg_md5_update(int param_1,void *param_2,uint param_3)

{
  uint uVar1;
  void *__dest;
  void *local_res4;
  uint local_res8;
  
  uVar1 = *(uint *)(param_1 + 0x10);
  *(uint *)(param_1 + 0x10) = param_3 * 8 + uVar1;
  if (*(uint *)(param_1 + 0x10) < uVar1) {
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + 1;
  }
  *(uint *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + (param_3 >> 0x1d);
  uVar1 = uVar1 >> 3 & 0x3f;
  local_res4 = param_2;
  local_res8 = param_3;
  if (uVar1 != 0) {
    __dest = (void *)(param_1 + 0x18 + uVar1);
    uVar1 = 0x40 - uVar1;
    if (param_3 < uVar1) {
      memcpy(__dest,param_2,param_3);
      return;
    }
    memcpy(__dest,param_2,uVar1);
    mg_byte_reverse(param_1 + 0x18,0x10);
    mg_md5_transform(param_1,param_1 + 0x18);
    local_res4 = (void *)((int)param_2 + uVar1);
    local_res8 = param_3 - uVar1;
  }
  for (; 0x3f < local_res8; local_res8 = local_res8 - 0x40) {
    memcpy((void *)(param_1 + 0x18),local_res4,0x40);
    mg_byte_reverse(param_1 + 0x18,0x10);
    mg_md5_transform(param_1,param_1 + 0x18);
    local_res4 = (void *)((int)local_res4 + 0x40);
  }
  memcpy((void *)(param_1 + 0x18),local_res4,local_res8);
  return;
}



// === mg_ota_begin @ 004793d8 ===

undefined4 mg_ota_begin(void)

{
  return 1;
}



// === mg_ota_write @ 00479400 ===

undefined4 mg_ota_write(void)

{
  return 1;
}



// === mg_ota_end @ 0047942c ===

undefined4 mg_ota_end(void)

{
  return 1;
}



// === mg_ota_commit @ 00479450 ===

undefined4 mg_ota_commit(void)

{
  return 1;
}



// === mg_ota_rollback @ 00479474 ===

undefined4 mg_ota_rollback(void)

{
  return 1;
}



// === mg_ota_status @ 00479498 ===

undefined4 mg_ota_status(void)

{
  return 0;
}



// === mg_ota_crc32 @ 004794c0 ===

undefined4 mg_ota_crc32(void)

{
  return 0;
}



// === mg_ota_timestamp @ 004794e8 ===

undefined4 mg_ota_timestamp(void)

{
  return 0;
}



// === mg_ota_size @ 00479510 ===

undefined4 mg_ota_size(void)

{
  return 0;
}



// === mg_sha1_update @ 0047da48 ===

void mg_sha1_update(int param_1,void *param_2,uint param_3)

{
  uint uVar1;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar1 = *(uint *)(param_1 + 0x14);
  *(uint *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_3 * 8;
  if (*(uint *)(param_1 + 0x14) < uVar1) {
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  }
  *(uint *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + (param_3 >> 0x1d);
  local_c = uVar1 >> 3 & 0x3f;
  if (local_c + param_3 < 0x40) {
    local_10 = 0;
  }
  else {
    local_10 = 0x40 - local_c;
    memcpy((void *)(param_1 + local_c + 0x1c),param_2,local_10);
    mg_sha1_transform(param_1,param_1 + 0x1c);
    for (; local_10 + 0x3f < param_3; local_10 = local_10 + 0x40) {
      mg_sha1_transform(param_1,(int)param_2 + local_10);
    }
    local_c = 0;
  }
  memcpy((void *)(param_1 + local_c + 0x1c),(void *)((int)param_2 + local_10),param_3 - local_10);
  return;
}



// === mg_sha256_update @ 0047e2d4 ===

void mg_sha256_update(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_10;
  
  for (local_10 = 0; local_10 < param_3; local_10 = local_10 + 1) {
    *(undefined1 *)(param_1 + *(int *)(param_1 + 0x28) + 0x2c) = *(undefined1 *)(param_2 + local_10)
    ;
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + 1;
    if (*(int *)(param_1 + 0x28) == 0x40) {
      mg_sha256_chunk(param_1);
      uVar2 = *(uint *)(param_1 + 0x20);
      uVar1 = uVar2 + 0x200;
      *(uint *)(param_1 + 0x20) = uVar1;
      *(uint *)(param_1 + 0x24) = (uint)(uVar1 < uVar2) + *(int *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
  }
  return;
}



// === mg_tls_init @ 00482ffc ===

void mg_tls_init(undefined4 param_1)

{
  mg_error(param_1,"TLS is not enabled");
  return;
}



// === mg_tls_handshake @ 00483044 ===

void mg_tls_handshake(void)

{
  return;
}



// === mg_tls_free @ 0048306c ===

void mg_tls_free(void)

{
  return;
}



// === mg_tls_recv @ 00483094 ===

undefined4 mg_tls_recv(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



// === mg_tls_send @ 004830f4 ===

undefined4 mg_tls_send(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



// === mg_tls_pending @ 00483154 ===

undefined4 mg_tls_pending(void)

{
  return 0;
}



// === mg_tls_ctx_init @ 0048317c ===

void mg_tls_ctx_init(void)

{
  return;
}



// === mg_tls_ctx_free @ 004831a4 ===

void mg_tls_ctx_free(void)

{
  return;
}



// === mg_tls_x25519 @ 00484128 ===

undefined4 mg_tls_x25519(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  int local_f0;
  undefined4 local_ec;
  undefined1 *local_e8;
  uint local_e4;
  undefined1 auStack_cc [32];
  undefined1 auStack_ac [64];
  undefined1 auStack_6c [64];
  undefined4 auStack_2c [9];
  
  x25519_core(auStack_cc,param_2,param_3,param_4);
  local_e8 = auStack_ac;
  for (local_f0 = 0; local_f0 < 0xd; local_f0 = local_f0 + 1) {
    puVar1 = auStack_cc + (uint)(byte)steps_8626[local_f0 * 3] * 0x20;
    for (local_e4 = (uint)(byte)steps_8626[local_f0 * 3 + 2]; 0 < (int)local_e4;
        local_e4 = local_e4 - 1) {
      sqr(puVar1,local_e8);
      local_e8 = puVar1;
    }
    mul1(puVar1,auStack_cc + (uint)(byte)steps_8626[local_f0 * 3 + 1] * 0x20);
  }
  mul(auStack_2c,auStack_cc,auStack_6c,8);
  local_ec = canon(auStack_2c);
  if (param_4 == 0) {
    local_ec = 0;
  }
  for (local_f0 = 0; local_f0 < 8; local_f0 = local_f0 + 1) {
    uVar2 = auStack_2c[local_f0];
    *(char *)(param_1 + local_f0 * 4) = (char)uVar2;
    *(char *)(param_1 + local_f0 * 4 + 1) = (char)((uint)uVar2 >> 8);
    *(char *)(param_1 + local_f0 * 4 + 2) = (char)((uint)uVar2 >> 0x10);
    *(char *)(param_1 + local_f0 * 4 + 3) = (char)((uint)uVar2 >> 0x18);
  }
  return local_ec;
}



// === mg_url_is_ssl @ 00484398 ===

undefined4 mg_url_is_ssl(char *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = strncmp(param_1,"wss:",4);
  if ((((iVar1 == 0) || (iVar1 = strncmp(param_1,"https:",6), iVar1 == 0)) ||
      (iVar1 = strncmp(param_1,"mqtts:",6), iVar1 == 0)) ||
     (((iVar1 = strncmp(param_1,"ssl:",4), iVar1 == 0 ||
       (iVar1 = strncmp(param_1,"tls:",4), iVar1 == 0)) ||
      (iVar1 = strncmp(param_1,"tcps:",5), iVar1 == 0)))) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// === mg_ws_upgrade @ 00486568 ===

void mg_ws_upgrade(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_resc;
  undefined4 *local_10 [2];
  
  local_resc = param_4;
  iVar1 = mg_http_get_header(param_2,"Sec-WebSocket-Key");
  *(code **)(param_1 + 0x80) = mg_ws_cb;
  *(undefined4 *)(param_1 + 0x84) = 0;
  if (iVar1 == 0) {
    mg_http_reply(param_1,0x1aa,&DAT_0049e854,"WS upgrade expected\n");
    *(uint *)(param_1 + 0xac) = *(uint *)(param_1 + 0xac) & 0xffffefff | 0x1000;
  }
  else {
    uVar2 = mg_http_get_header(param_2,"Sec-WebSocket-Protocol");
    local_10[0] = &local_resc;
    ws_handshake(param_1,iVar1,uVar2,param_3,local_10);
    *(uint *)(param_1 + 0xac) = *(uint *)(param_1 + 0xac) & 0xfffffdff | 0x200;
    *(uint *)(param_1 + 0xac) = *(uint *)(param_1 + 0xac) & 0xffff7fff;
    mg_call(param_1,0xc,param_2);
  }
  return;
}



// === update_offset @ 00487dd0 ===

void update_offset(int *param_1)

{
  size_t sVar1;
  int iVar2;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    iVar2 = param_1[2];
    sVar1 = strlen((char *)(*param_1 + param_1[2]));
    param_1[2] = iVar2 + sVar1;
  }
  return;
}



// === mg_ota_boot @ 0048f460 ===

void mg_ota_boot(void)

{
  return;
}



// === pthread_cond_signal @ 004a07e0 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_cond_signal_004b1560)();
  return iVar1;
}



// === pthread_mutex_unlock @ 004a0f20 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_mutex_unlock_004b1730)();
  return iVar1;
}



// === signal @ 004a0f60 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
  __sighandler_t p_Var1;
  
  p_Var1 = (__sighandler_t)(*(code *)PTR_signal_004b1740)();
  return p_Var1;
}



// === SHA256_Update @ 004a1160 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SHA256_Update(SHA256_CTX *c,void *data,size_t len)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_SHA256_Update_004b17c0)();
  return iVar1;
}



// === pthread_rwlock_unlock @ 004a1270 ===

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_pthread_rwlock_unlock_004b1804)();
  return iVar1;
}



// === pthread_cond_signal @ 004b4000 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cond_signal(pthread_cond_t *__cond)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_cond_signal@@GLIBC_2.3.2 */
  halt_baddata();
}



// === pthread_mutex_unlock @ 004b41bc ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_mutex_unlock@@GLIBC_2.0 */
  halt_baddata();
}



// === signal @ 004b41cc ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

__sighandler_t signal(int __sig,__sighandler_t __handler)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* signal@@GLIBC_2.0 */
  halt_baddata();
}



// === SHA256_Update @ 004b4248 ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SHA256_Update(SHA256_CTX *c,void *data,size_t len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* SHA256_Update@@OPENSSL_1_1_0 */
  halt_baddata();
}



// === pthread_rwlock_unlock @ 004b428c ===

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* pthread_rwlock_unlock@@GLIBC_2.2 */
  halt_baddata();
}


