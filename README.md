# Event Detection

Detects events from raw signal in nanopore fast5 files

## Installation: 
[HDF5](https://www.hdfgroup.org/downloads/hdf5/) must be installed. Libraries and headers should be in system paths (ie `$LD_LIBRARY_PATH` and `$CPATH` respectively), or specified by running `python setup.py build_ext --library-dirs <hdf5-location>/lib --include-dirs <hdf5-location>/include` prior to installation.

```
git clone --recursive https://github.com/skovaka/event_detection.git
cd event_detection
make
```

## Usage
`./detect_events <fast5-path>`

Outputs event tab separated mean, standard deviation, raw length, and raw start on each line.

Optional arguments:
* `--win-len1 = 3`
* `--win-len2 = 6`
* `--thresh1 = 1.4`
* `--thresh2 = 9.0`
* `--peak-height = 0.2`
* `--min-mean = 30` (events with lower mean pA will not be output)
* `--max-mean = 150` (events with higher mean pA will not be output)

I don't have a great understanding of the first four parameters, beyond that the average event length seems to be between `win-len1` and `win-len2`. I will work on this.
