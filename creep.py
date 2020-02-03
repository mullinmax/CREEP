import keyboard
import time
import signal

def callback(event):
    print(event)

def signal_handler(signal, frame):
    print(signal)
    print(frame)

keyboard.hook(callback)


signals = [x for x in dir(signal) if x.startswith("SIG")]
catchable_signals = set(signals) - {signal.SIGKILL, signal.SIGSTOP}
for sig in catchable_signals:
    try:
        print(sig)
        signum = getattr(signal, sig)
        signal.signal(signum, signal.SIG_IGN)
    except (OSError, RuntimeError, ValueError):
        print(sig)

time.sleep(200)
