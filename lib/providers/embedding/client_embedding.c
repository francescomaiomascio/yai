/* SPDX-License-Identifier: Apache-2.0 */

#include <yai/providers/providers.h>

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

int yai_client_embedding(const char *provider_name,
                              const char *text,
                              float *vector_out,
                              size_t vector_dim)
{
  yai_provider_t *provider;

  if (!text || !text[0] || !vector_out || vector_dim == 0) return YAI_MIND_ERR_INVALID_ARG;

  provider = resolve_provider(provider_name);
  if (!provider || !provider->vtable || !provider->vtable->embedding) return YAI_MIND_ERR_PROVIDER;

  return provider->vtable->embedding(provider, text, vector_out, vector_dim);
}
