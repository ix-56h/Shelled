**Git startegy:**

Update master: merge master on stg, run utest if ok merge stg on master

Update stg: merge stg on dev, run utest if ok merge dev on stg

Update dev: merge dev on one fix-/maj-/nrm-/feature-, if ok merge on dev THEN merge dev on every fix-/maj-/nrm-
