# HelloWorld Examples

## How to Install DDS
### RTI connext (hello_connext)
1. Download `RTI connext` install file from RTI homepage
2. Run the install file using lisence file
3. DONE!

### OpenSplice Community (hello_opensplice)
1. Download `OpenSplice Community` from PrismTech homepage
2. Put HDE folder on home directory
3. DONE!

### OpenDDS (hello_opendds)
1. Download OpenDDS file from OpenDDS homepage
2. Extract file
3. Run `configure` file from OpenDDS folder
4. Type `make` in the OpenDDS folder to create binary file
5. DONE!

---
## Advanced work
### hello_connext
```
export NDDSHOME=[RTI_HOME]
```

### hello_opensplice
```
source [OPENSPLICE_HOME]/[PLATFORM]/release.com
```

### hello_opendds
```
source [OPENDDS_HOME]/setenv.sh
```

---
## How to compile
> Vendor specific environment variables should be sourced to build 
> Before building Publisher and/or Subscriber, you must parse IDL

Following make targets are available
* **all** build everything
* **generate** parse IDL
* **pub** build publisher
* **sub** build subscriber
* **clean** delete obj src/idl folders and binaries

---
## How to run
### hello_connext, hello_opensplice
Run Publisher
```
./pub
```

Run Subscriber
```
./sub
```

### hello_opendds
Run DCSPInfo(Domain discovery utility)
```
DCPSInfo
```

Run Publisher
```
./pub
```

Run Subscriber
```
./sub
```

