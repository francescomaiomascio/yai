/* SPDX-License-Identifier: Apache-2.0 */

#include <yai/providers/providers.h>

#include <stdio.h>
#include <string.h>

static yai_provider_t *resolve_provider(const char *provider_name)
{
  yai_provider_registry_t *registry = yai_knowledge_provider_registry();
  if (!registry) return NULL;
  if (provider_name && provider_name[0]) {
    yai_provider_t *named = yai_provider_registry_get(registry, provider_name);
    if (named) return named;
  }
  return yai_provider_registry_default(registry);
}

int yai_client_completion(const char *provider_name,
                               const char *payload,
                               yai_provider_response_t *response_out)
{
  yai_provider_t *provider;
  yai_provider_request_t req;

  if (!payload || !payload[0] || !response_out) return YAI_MIND_ERR_INVALID_ARG;

  provider = resolve_provider(provider_name);
  if (!provider) return YAI_MIND_ERR_PROVIDER;

  memset(&req, 0, sizeof(req));
  snprintf(req.request_id, sizeof(req.request_id), "providers-inference");
  snprintf(req.model, sizeof(req.model), "%s", provider->name ? provider->name : "default");
  snprintf(req.payload, sizeof(req.payload), "%.511s", payload);

  return yai_provider_completion(provider, &req, response_out);
}
