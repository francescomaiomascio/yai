import secrets


def generate_runtime_id() -> str:
    """
    Genera un runtime_id corto, stabile, non temporale.
    NON usare datetime, UUIDv7 o session_id.
    """
    return f"ice-rt-{secrets.token_hex(4)}"
