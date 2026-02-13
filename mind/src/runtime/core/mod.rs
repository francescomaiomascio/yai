use crate::{
    error::{MindError, Result},
    runtime::workspace::WorkspaceContext,
};

#[derive(Debug)]
pub enum Error {
    Stub,
}

impl From<MindError> for Error {
    fn from(_: MindError) -> Self {
        Error::Stub
    }
}

/// Legacy compat runtime context.
/// Temporary: maps to WorkspaceContext.
#[derive(Debug, Clone)]
pub struct RuntimeContext {
    pub ws: WorkspaceContext,
}

impl RuntimeContext {
    pub fn new(ws_id: String) -> Self {
        Self {
            ws: WorkspaceContext::new(ws_id),
        }
    }
}

/// Legacy compat API surface.
pub fn ok<T>(v: T) -> Result<T> {
    Ok(v)
}
