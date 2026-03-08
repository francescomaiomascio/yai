#include <stdio.h>
#include <string.h>

#include <yai/law/loader.h>

int main(void) {
  yai_law_runtime_t rt;
  char err[256] = {0};
  char json[4096] = {0};

  if (yai_law_load_runtime(&rt, err, sizeof(err)) != 0) return 1;
  if (yai_law_load_domain_manifest(&rt, "D1-digital", json, sizeof(json)) != 0) return 1;

  if (!strstr(json, "D1-digital")) {
    fprintf(stderr, "domain_loader: D1 manifest not loaded\n");
    return 1;
  }

  puts("domain_loader: ok");
  return 0;
}
