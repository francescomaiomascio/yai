// Temporary compat layer.
// TODO: remove once imports are migrated to crate::cognition::providers
pub mod adapters;

pub mod embeddings {
    pub use crate::cognition::providers::embeddings::*;
}
pub mod llm {
    pub use crate::cognition::providers::llm::*;
}
