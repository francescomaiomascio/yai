# C7 Control Families De-Hardcoding Map

Old primary model:
- `families/<family>/manifest.json`
- `families/<family>/family.manifest.json`

New primary model:
- `families/descriptors/<family>.descriptor.v1.json`
- `families/index/families.descriptors.index.json`
- `families/index/family.matrix.v1.json`

Role split:
- descriptors/index/schema = canonical semantic model
- per-family folders = materialized views / compatibility surfaces
