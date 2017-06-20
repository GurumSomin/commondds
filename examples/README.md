# HelloWorld Examples

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

## How to compile
> Vendor specific environment variables should be sourced to build 
> Before building Publisher and/or Subscriber, you must parse IDL

Following make targets are available
* **all** build everything
* **generate** parse IDL
* **pub** build publisher
* **sub** build subscriber
* **clean** delete obj src/idl folders and binaries

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

