```sh
wget -O rustdesk-server-linux-amd64.zip \
    https://github.com/rustdesk/rustdesk-server/releases/download/1.1.15/rustdesk-server-linux-amd64.zip

unzip rustdesk-server-linux-amd64.zip
```

```sh
#!/usr/bin/env bash

set -euo pipefail

BASE_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUN_DIR="${BASE_DIR}/run"
LOG_DIR="${BASE_DIR}/logs"
ENV_FILE="${BASE_DIR}/.env"

HBBS_BIN="${BASE_DIR}/hbbs"
HBBR_BIN="${BASE_DIR}/hbbr"

HBBS_PID_FILE="${RUN_DIR}/hbbs.pid"
HBBR_PID_FILE="${RUN_DIR}/hbbr.pid"

HBBS_LOG_FILE="${LOG_DIR}/hbbs.log"
HBBR_LOG_FILE="${LOG_DIR}/hbbr.log"

usage() {
  cat <<'EOF'
Usage:
  ./run.sh start [hbbs|hbbr|all]
  ./run.sh stop [hbbs|hbbr|all]
  ./run.sh restart [hbbs|hbbr|all]
  ./run.sh status [hbbs|hbbr|all]
  ./run.sh log [hbbs|hbbr|all]

Defaults to "all" when no service name is provided.

Required in .env for hbbs:

  HBBS_RELAY_HOST
  HBBS_RELAY_PORT
EOF
}

ensure_dirs() {
  mkdir -p "${RUN_DIR}" "${LOG_DIR}"
}

load_env() {
  if [[ -f "${ENV_FILE}" ]]; then
    set -a
    # shellcheck disable=SC1090
    source "${ENV_FILE}"
    set +a
  fi
}

hbbs_args() {
  : "${HBBS_RELAY_HOST:?HBBS_RELAY_HOST is required in .env}"
  : "${HBBS_RELAY_PORT:?HBBS_RELAY_PORT is required in .env}"

  printf '%s\n' "-r" "${HBBS_RELAY_HOST}:${HBBS_RELAY_PORT}"
}

is_running() {
  local pid_file="$1"

  [[ ! -f "${pid_file}" ]] && return 1

  local pid
  pid="$(<"${pid_file}")"

  [[ -z "${pid}" ]] && return 1

  if kill -0 "${pid}" 2>/dev/null; then
    return 0
  fi

  rm -f "${pid_file}"
  return 1
}

start_service() {
  local name="$1"
  local bin="$2"
  local pid_file="$3"
  local log_file="$4"
  shift 4

  local args=("$@")

  if [[ ! -x "${bin}" ]]; then
    echo "${name}: binary not found or not executable: ${bin}" >&2
    return 1
  fi

  if is_running "${pid_file}"; then
    echo "${name}: already running (pid $(<"${pid_file}"))"
    return 0
  fi

  touch "${log_file}"

  nohup "${bin}" "${args[@]}" >>"${log_file}" 2>&1 &
  local pid=$!

  echo "${pid}" > "${pid_file}"

  sleep 1

  if kill -0 "${pid}" 2>/dev/null; then
    echo "${name}: started (pid ${pid})"
    return 0
  fi

  echo "${name}: failed to start, check ${log_file}" >&2
  rm -f "${pid_file}"
  return 1
}

stop_service() {
  local name="$1"
  local pid_file="$2"

  if ! is_running "${pid_file}"; then
    echo "${name}: not running"
    return 0
  fi

  local pid
  pid="$(<"${pid_file}")"

  kill "${pid}" 2>/dev/null || true

  for _ in {1..10}; do
    if ! kill -0 "${pid}" 2>/dev/null; then
      rm -f "${pid_file}"
      echo "${name}: stopped"
      return 0
    fi
    sleep 1
  done

  kill -9 "${pid}" 2>/dev/null || true
  rm -f "${pid_file}"

  echo "${name}: stopped forcefully"
}

status_service() {
  local name="$1"
  local pid_file="$2"
  local log_file="$3"

  if is_running "${pid_file}"; then
    echo "${name}: running (pid $(<"${pid_file}")) log=${log_file}"
  else
    echo "${name}: stopped"
  fi
}

log_service() {
  local service="$1"

  case "${service}" in
    hbbs)
      touch "${HBBS_LOG_FILE}"
      tail -n 100 -F "${HBBS_LOG_FILE}"
      ;;
    hbbr)
      touch "${HBBR_LOG_FILE}"
      tail -n 100 -F "${HBBR_LOG_FILE}"
      ;;
    all)
      touch "${HBBS_LOG_FILE}" "${HBBR_LOG_FILE}"
      tail -n 100 -F "${HBBS_LOG_FILE}" "${HBBR_LOG_FILE}"
      ;;
  esac
}

dispatch() {
  local action="$1"
  local service="${2:-all}"

  local hbbs_runtime_args=()

  if [[ "${action}" == "start" || "${action}" == "restart" ]]; then
    mapfile -t hbbs_runtime_args < <(hbbs_args)
  fi

  case "${action}:${service}" in

    start:hbbs)
      start_service hbbs \
        "${HBBS_BIN}" \
        "${HBBS_PID_FILE}" \
        "${HBBS_LOG_FILE}" \
        "${hbbs_runtime_args[@]}"
      ;;

    start:hbbr)
      start_service hbbr \
        "${HBBR_BIN}" \
        "${HBBR_PID_FILE}" \
        "${HBBR_LOG_FILE}"
      ;;

    start:all)
      dispatch start hbbs
      dispatch start hbbr
      ;;

    stop:hbbs)
      stop_service hbbs "${HBBS_PID_FILE}"
      ;;

    stop:hbbr)
      stop_service hbbr "${HBBR_PID_FILE}"
      ;;

    stop:all)
      dispatch stop hbbs
      dispatch stop hbbr
      ;;

    restart:hbbs)
      dispatch stop hbbs
      dispatch start hbbs
      ;;

    restart:hbbr)
      dispatch stop hbbr
      dispatch start hbbr
      ;;

    restart:all)
      dispatch stop all
      dispatch start all
      ;;

    status:hbbs)
      status_service hbbs "${HBBS_PID_FILE}" "${HBBS_LOG_FILE}"
      ;;

    status:hbbr)
      status_service hbbr "${HBBR_PID_FILE}" "${HBBR_LOG_FILE}"
      ;;

    status:all)
      dispatch status hbbs
      dispatch status hbbr
      ;;

    log:hbbs|log:hbbr|log:all)
      log_service "${service}"
      ;;

    *)
      echo "Unknown action/service: ${action} ${service}" >&2
      usage
      return 1
      ;;
  esac
}

main() {
  if [[ $# -lt 1 ]]; then
    usage
    exit 1
  fi

  ensure_dirs
  load_env

  dispatch "$1" "${2:-all}"
}

main "$@"
```

```sh
vim .env
```

```env
HBBS_RELAY_HOST=<ip>
HBBS_RELAY_PORT=<port>
```

```sh
bash run.sh start

cat logs/hbbs.log
```

