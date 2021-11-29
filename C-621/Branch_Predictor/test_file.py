import subprocess

two_bit = [[2048, 1], [2048, 2], [4096, 2], [8192, 2], [16384, 2], [32768, 2], [65536, 2]]
tourn = [[2048, 8192, 8192], [4096, 8192, 8192], [4096, 16384, 16384], [16384, 32768, 32768], [32768, 65536, 65536]]
gshare = [8192, 16384, 32768, 65536, 131072]

exec_name = './Main'
file_prefix = "../Workloads/"
file_names = ["sample.cpu_trace", "531.deepsjeng_r_branches.cpu_trace", "541.leela_r_branches.cpu_trace", "548.exchange2_r_branches.cpu_trace"]

print("\n\n2 bit predictor\n\n")
for file in file_names:
	print("\n\n", file, "\n\n")
	for param in two_bit:
		subprocess.call([exec_name, str(param[0]), str(param[1]), file_prefix + file])

print("\n\ntournament predictor\n\n")
for file in file_names:
	print("\n\n", file, "\n\n")
	for param in tourn:
		subprocess.call([exec_name, str(param[0]), str(param[1]), str(param[2]), file_prefix + file])

print("\n\ngshare predictor\n\n")
for file in file_names:
	print("\n\n", file, "\n\n")
	for param in gshare:
		subprocess.call([exec_name, str(param), file_prefix + file])