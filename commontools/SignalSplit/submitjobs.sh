
doSubmit=true

#Set this in run_jobs.sh and mkdir beforehand


rm -rf err
rm -rf out
rm -rf log

mkdir -p err
mkdir -p out
mkdir -p log

filesPerJob=1
nTotalJobs=0
samples=( \
##  "2017_4b_ZH" \
##  "2017_4b_ggZH" \
##  "2017_4d_ZH" \
##  "2017_4d_ggZH" \
##  "2017_4Tau_ZH" \
##  "2017_4Tau_ggZH" \
#  "2018_4b_ZH" \
  "2018_4b_ggZH" \
  "2018_4d_ggZH" \
  "2018_4d_ZH" \
  "2018_4Tau_ZH" \
  "2018_4Tau_ggZH" \
)

names_4b_ZH=( \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
)

names_4b_ggZH=( \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-15_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-40_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTobbbb_ZToLL_MH-125_MS-55_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
)

names_4d_ZH=( \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
)

names_4d_ggZH=( \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-7_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-15_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-40_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTodddd_ZToLL_MH-125_MS-55_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
)


names_4Tau_ZH=( \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
)

names_4Tau_ggZH=( \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-7_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-15_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-40_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-0_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-0p05_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-1_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-10_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-100_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-1000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-10000_TuneCP5_13TeV-powheg-pythia8"  \
  "ggZH_HToSSTo4Tau_ZToLL_MH-125_MS-55_ctauS-100000_TuneCP5_13TeV-powheg-pythia8"  \
)

for sample in ${samples[@]}
do
  nlines=`cat inputLists/${sample}.list | wc -l`
  njobs1=$((nlines/filesPerJob))
  njobs2=$((nlines%filesPerJob))
  if [ $njobs2 -gt 0 ]
  then
    echo adding one
    njobs=$((njobs1+1))
  else  
    echo not adding one
    njobs=$((njobs1))
  fi
  nTotalJobs=$((nTotalJobs+njobs))
  #echo $sample, $nlines
  #echo number of submits, $njobs, $njobs1, $njobs2
  split -l $filesPerJob -d -a 2 --additional-suffix=.list inputLists/${sample}.list ${sample}"_"
  #split -l 5            -d -a 2 --additional-suffix=.list inputLists/2017_ggZH.list 2017_ggZH"_"
  if [ $sample == "2018_4b_ZH" ] || [ $sample == "2017_4b_ZH" ] 
  then
    echo "setting for 4b ZH"
    names=(${names_4b_ZH[*]})
  elif [ $sample == "2018_4b_ggZH" ] || [ $sample == "2017_4b_ggZH" ] 
  then
    echo "setting for 4b ggZH"
    names=(${names_4b_ggZH[*]})
  elif [ $sample == "2018_4d_ZH" ] || [ $sample == "2017_4d_ZH" ] 
  then
    echo "setting for 4d ZH"
    names=(${names_4d_ZH[*]})
  elif [ $sample == "2018_4d_ggZH" ] || [ $sample == "2017_4d_ggZH" ] 
  then
    echo "setting for 4d ggZH"
    names=(${names_4d_ggZH[*]})
  elif [ $sample == "2018_4Tau_ZH" ] || [ $sample == "2017_4Tau_ZH" ] 
  then
    echo "setting for 4Tau ZH"
    names=(${names_4Tau_ZH[*]})
  elif [ $sample == "2018_4Tau_ggZH" ] || [ $sample == "2017_4Tau_ggZH" ] 
  then
    echo "setting for 4Tau ggZH"
    names=(${names_4Tau_ggZH[*]})
  else 
    echo "unknown"
  fi
  for (( i=0; i<$njobs; i++ ))
  do
    for name in ${names[@]}
    do
      if [ $i -lt 10 ] 
      then
        j=0${i}
      else
        j=$i
      fi
      #echo $j, ${sample}_${j}.list
      file=${sample}_${j}.list
      # write base for submit file
      printf "Universe = vanilla\n" > submitfile
      printf "Executable = run_job.sh\n" >> submitfile
      printf "Should_Transfer_Files = YES \n" >> submitfile
      printf "WhenToTransferOutput = ON_EXIT\n" >> submitfile
      printf "Transfer_Input_Files = SignalSplit.exe, cms_setup.tar.gz, ${sample}_${j}.list \n" >> submitfile
      printf "notify_user = $(whoami)@cern.ch\n" >> submitfile
      printf "x509userproxy = \$ENV(X509_USER_PROXY)\n" >> submitfile
      printf "\n" >> submitfile
      printf "Output = out/SigSplit.\$(Cluster)_\$(Process).stdout\n" >> submitfile
      printf "Error  = err/SigSplit.\$(Cluster)_\$(Process).stderr\n" >> submitfile
      printf "Log    = log/SigSplit.\$(Cluster)_\$(Process).log\n" >> submitfile
      printf "\n" >> submitfile
      printf "RequestMemory = 2000\n" >> submitfile
      printf "\n" >> submitfile
      printf "Arguments = ${file} ${name}  \n" >>submitfile
      printf "Queue\n">>submitfile
      echo 
      echo made file for ${sample}_${j}.list and $name 
      echo 
      #submit job
      if [ ${doSubmit} = true ]
      then
       condor_submit submitfile
      fi
      done
  done 
  echo
  echo "nTotalJobs submitted:" $nTotalJobs
  #rm *.list
done
