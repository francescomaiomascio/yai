# YAI installed layout

## Canonical system surface

- /etc/yai
  Host-specific configuration
- /run/yai
  Ephemeral runtime sockets, pids, locks, transient state
- /var/lib/yai
  Persistent runtime state
- /var/log/yai
  Userspace operational logs
- /var/cache/yai
  Rebuildable cache material
- /usr/bin
  User-facing entrypoints
- /usr/include/yai/client
  Public C client headers
- /usr/lib/yai/client
  Client implementation
- /usr/lib/yai/shell
  Shell implementation
- /usr/share/doc/yai
  Installed documentation
