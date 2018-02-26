_main() 
{
    local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts="--help --mode --dname --run -FP -FPeta -MP -OORP -MPd -OORPd -FCP -tCP -lFCP -aFCP -derThreshSi -derThreshSi_ptCheck -derThreshDi -derThreshDi_ptCheck -JEF -BC -D -E -DE -DEF -F -LP -aAP -aAPef -TEC -mu --muTrg --asym_cut --input --outSuffix -useHF -NPVEta -mon -monSi -IGF -IGFw"

    case "${prev}" in
	--run)
	    COMPREPLY=( $(compgen -W "B C D DE DEF BC" -- ${cur}) )
            return 0
            ;;
	--mode)
	    # COMPREPLY=( $(compgen -W "DeriveThresholds DeriveThresholds_noDiJCut DeriveThresholds_inclSiMu_noDiJCut" -- ${cur}) )
	    local names=$(for x in `ls -1 /nfs/dust/cms/user/"$USER"/forBaconJets/17Nov2017/Residuals/ | grep Run17[B]*[C]*[D]*[E]*[F]*_Data`; do y=${x#*_Data}; echo ${y#_}; done)
	    COMPREPLY=( $(compgen -W "${names}" -- ${cur}) )
            return 0
            ;;
	--dname)
	    # COMPREPLY=( $(compgen -W "newPtBinning wMu17 wIsoMu27 wIsoMu20" -- ${cur}) )
	    local names=$(for x in `ls -1 /nfs/dust/cms/user/"$USER"/forBaconJets/17Nov2017/Residuals/Run17*/ | grep Run.*.root`; do k=${x%.root}; y=${k#Run17[B]*[C]*[D]*[E]*[F]*_17Nov17_2017_}; z=${y#*_17Nov17_2017}; j=${z#*_17Nov17}; echo ${j#_}; done)
	    COMPREPLY=( $(compgen -W "${names}" -- ${cur}) )
            return 0
            ;;
	--asym_cut)
	    COMPREPLY=( $(compgen -W "0.05" -- ${cur}) )
            return 0
            ;;
	--muTrg)
	    COMPREPLY=( $(compgen -W "HLT_Mu17 HLT_IsoMu20 HLT_IsoMu20" -- ${cur}) )
            return 0
            ;;
	--input)
	    COMPREPLY=( $(compgen -o filenames -f -- ${cur}) )
            return 0
            ;;	
        *)
        ;;
    esac
	
    if [[ ${cur} == -* ]] ; then
        COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
        return 0
    fi
}
complete -F _main ./main
