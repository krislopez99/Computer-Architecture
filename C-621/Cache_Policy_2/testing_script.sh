#!/usr/bin/env bash

cache_size=(128 256 512 1024 2048)
assoc_config=(4 8 16)
mem_traces=("sample.mem_trace" "531.deepsjeng_r_llc.mem_trace" "541.leela_r_llc.mem_trace" "548.exchange2_r_llc.mem_trace")
for f in ${mem_traces[@]}
do
		for c in ${cache_size[@]};
		do
			for a in ${assoc_config[@]};
			do
				echo "$f $c $a"
				./Main $f $c $a
			done
		done
done
