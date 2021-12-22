import numpy as np
import scipy.io.wavfile
import sys

def main(file):
    border=950000
    w, signal = scipy.io.wavfile.read(file)
    signal=np.array(signal).astype(np.float64)
    
    if signal.ndim>1:
        signal = [s[0] for s in signal]
        signal*=np.hamming(len(signal))

    ceps=np.fft.fft(np.log(abs(np.fft.fft(signal))))

    if max(ceps) > border:
        result='K'
    else:
        result='M'
    print(result)
    return result


if __name__ == '__main__':
    main(sys.argv[1])