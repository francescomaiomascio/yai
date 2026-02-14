// mind/src/transport/mod.rs
pub mod protocol;
pub mod uds_server;

// Ri-esportiamo per comodità di utilizzo esterna
pub use uds_server::EngineClient;
pub use protocol::YaiCommand;