#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <string.h>

using namespace std;
class Solution {
public:
    string findSmallLex(const std::string &s1,
                        int *pos,
                        int posCount,
                        const std::string &s)
    {
        std::string tmp;
        for (int i = 0; i < posCount; i++) {
           std::stringstream ss;
           ss << s[pos[i]];
           tmp += ss.str();
        }
        //cout << "tmp: " << tmp << endl;
        if (s1.size() == 0) {
            return tmp;
        }
        int ret = memcmp(s1.c_str(), tmp.c_str(), s1.size());
        if (ret <= 0) {
            return s1;
        } else {
            return tmp;
        }
    }
    void shiftLeft(int *pos, int count) {
        for (int i = 0; i < count - 1; i++) {
            pos[i] = pos[i+1];
        }
    }
    string removeDuplicateLetters(string s) {
        size_t l = s.length();
        std::map<char,bool> m;
        size_t count = 0;
        for (unsigned int i = 0; i < l; i++) {
            try {
               m.at(s[i]);
            } catch (const std::out_of_range &e) {
               m[s[i]] = true;
               count++;
            }
        }

        std::map<char,bool> m1;
        int pos[count];
        size_t posCount = 0;
        unsigned int i = 0;
        std::string ret;

        while (i < l) {
            try {
                m1.at(s[i]);
            } catch (const std::out_of_range &e) {
                m1[s[i]] = true;
                std::stringstream ss;
                ss << s[i];
                pos[posCount++] = i;
                if (posCount == count) {
                    ret = findSmallLex(ret, pos, count, s);
                    m1.clear();
                    pos[0] = pos[1];
                    posCount = 1;
                    i = pos[0] + 1;
                    continue;
                }
            }
            i++;
        }
        return ret;
    }
};

int main()
{
   std::string i1("bcabc"),
      i2("bcacbabc"),
      i3("cbacdcbc"),
      i4("mhdmsfxmcrslmaruresdouolyectxamdpsyadwxltpepthuwmuvacpvbtkvmdbqcmgavrrekczzltkkgutugzmmjncldgnkegchtuxrpzizhleefdgmigzznislffgzgtkbdabgyxojtkbqfjbkyrscnhizvibuivpsghrhhyarkvyvmexqhdcykulfsqalqwlubzupydxhvugizyhrozdlbdnyuxrersbuilyvouljenqdrxngeydzdltnacxydjflhmrbbujtqjlkfpydheitdeodtyugqljimnjtezgrqpfjyutqpzqiqjpehazybiodbybmvrjjhetdfahqbkucfmaabnpqcsqgdkhiosbndodnpjhanggnhdogfqskxdcjpltdsatdqwtpotgcfhketubhiakfijsxfmjcxnmmoqmdwmfypvarlpxhxkecuyytqjhmxtceopslowsbkreezeggfpmrfrluwtebuuigytcwjywkfcdqbxjdfgcetcxbudzhosjztrzjpqwthtzifbizhqsczetbxmiqaoshnqbybhcpmlyivgtafvoenxdverstplcovvixevpnfdmofdvpiecdzoiysbgdtfxtorlzbjltvdhjumpxovscmrlenfocwpkjmjclqrcyoudfmgxavhnewngsjqlkujwyyqhtxhdmlnvlrrdqzerxxvofnhdotmopxbedqrjzhbdxqsropfmqojqtwlxnkyrlslxcstyppchdpwelytfpfpdarzktxalyrogonlownmxkgxpdvttcmpcrrupiyynibzcxbbhmfunlqcshgyytxnkjadcyckekvcrehlmchgmqbofsodrznqwdbagmdwpnhmheplylucaprzqoyvihitivzgpjqclhwfynhvnnksxvfbqpqdstcghliaxhfmsnhyezwllyrydwfcokzmjuiwgophogqsrumbedwmeiyzwspssgsvwummjvbpulaqlocwyxjhzdijaakwwnrjijwylqgbguachbckkfocbvxaijyxpcrxtsjxknchwlzdouazckvicjetspprzopkfhrtyfyoscixyudpsxcdmaibcmpdprzslnupbrormpglmjgfwutxwacixjdesrewechbbrpreiyvowzixzdiwpfxqnbqobpjuawizuzljbkhgvvgbdoudyhmfzzccwqiyifyjzgcnuogaotnsxyukmhvlikcrqejuvtxwwvdajfamntywqyydevbglgsqfyvvjkxtkfsckelnsuzznmpryqhcacoqshcnskspbqapzljtzhwohqqrkdgcdidwetltjwafphryvnvxyvupmnxmngtecynhgtrweivdwjsfkfqetwxcijdxgebfborhsobkisvwsknxagarcjktkialbqpaostniygbvspdxbhruarkkjnettuvpfsidpjoxexqjlltstwgxffmrslwyipbanjutfqbahpdrtubmncjzpwlgzkhixxuwtzsexydwdeuggeddqsqsfztehjewenxvslbipiudbhhkflgjqygsthabxtocwtqbobvsrqzpeoaroeqgvwfojsxzhruqwwcssqgnwujiscnszlzoohfvglqrrewlvnlxhuubiwgdwrkzpolvwojvqohsyfhgrmhrzemsrvbwnwkywzqgkkxylanyhjtvxvhtrsscnpypmtnouprbtokjhvxgfddiigixwdbylvsofdrmelkrzujntmrjxwmluqmhinqpdihmlafqyhyxcjcsovrpjaovnclwkwkhrqnnotzmqralxfbwneqkwwshgvvurrmoyxbullwxivocehrdmpalzuthuwjqctcvihttnnktfhrgbwumjazfupbrztilnffbzheqeacgfcmmssusszmqiheinygltehwwsaxuvjgedutckpxuwtbovdjcdxxzvkcxvqjlthxreuhasfhcftfutbeelffzvhvcbtmvtvlimzchuyjbaukrictblxiuueuqcrmikeobsoxlhhkjlvamuhupfmuqguqlifjgwwyvqbftaafsgtcliiyniqjcqwzjhgynkzvwdjwquvpizixrhsufytzlqifuuzmnyunqzpjkawxrndzjedmgbgrazowphnyzhyouoywmvfxqsrhjygcwhvjkrlnyddklpblccgmbirdahrjwiyrhnfjpzlrravybzggklkoluiszjiznrpntndpvzqibtqzsaadpriizksjzevjcvxweurahisliczephpfjuuqgrdtalvliwzooqibplvaezhmqeakaasnamdditqrshmtxzvxdhjducjrgnrgjxfqyzwcgunzfyozoufithynydpbavlvovvfbvbkekzlibskkhjysyteyesvfzpztqbdqmefebulnhfufdiknruvjdfedaycumzditjeptpsgarhzynzxfttlujmltopejadhqyixoqumhxbdcaykhfngtdfmemaffrbroxpuezoyzkmqdyfvouywoqekpmllnkafeznzxhvhruzqomohrrloncoenurnxyzgzcronxhcupgsvogwuuxdaavvpcybkmatyabbtfszfvzldlzlekdcvvksugklzvsgqjdxcyvmnezsxrwfdgedhigfilkeiccsmhwqwhhspvbxpysksuwwkcjowhpecfqazdtqejqleezmuzlrfdsvpvncrxvtotiscpmsajnhfllbhfgdjgfjdihfuaymitdjejluccluzgbtcspagfcdcgwnhpzdyqaoqxpqytuxdhwgxwxziqecrkwqoofwanbkynizqambwzvmcjxvkeiqrjunmwwrwhelrocbtmadcceytohbjvxtovdtclilabmabqaolwhhgsraxorjohwxaldttbkswtaxlhpwxcncoxfotnmnkykahsijmuouvsjhtznerqbztftzppvptgfzhdteutcuchhhgkggwzqgdthzowcovxoemlhzaovgrcolakvioduybljadfawdprvuaewqqacbsvdrtvraqdqkrfvinclajunqlvkkpvxofhdqygbuukaplicqaiezdeolkzsnlwbpttvtrwsmiejzjjjfaeqkxgvhjagjnpuubnhgazhcsniznympivmspsiliqttprnyulpumkmvtcrccfqeqyhtjwfsbsitvhshgajibgvbkrphyxdjnhpewlvwnjokffvzkirqxhxjqglrvwjuihqjmncmefncpvrylippcrouprqzlwtctcphfuyilqbmjcemizbdcwqyskwcoexfbuyvtzviftgjlpkbivjrndtwvvocjplfbdtoobxeonzawymfctomlnsdikleqtozyhyftapkfpsqotmmitshrmldcdrupeadrkaroagwexxspekqdizgbzksakprgpderigvzvcgbfdjfyujeroubuuekivlnvoeplpgkwbmfuxweqbosqsqdfbthfqtvkplrvjphenmlbkcrephmtqfzlorcozieegnylznzjesnhpcmcgvzjqlikfukevbyydpxdkvcyxwysupnfnshvaqmhahevnexaxfyiatwrmodobzaemhfvcxbghdfhllpwpmcnoixqxrppbfnbraqitaxdgqtnsxtvqfduhclkrjzgbhbglicgdbmhirhgqvbnomybtembcryzuskxqudtbmvbeqyuutzgiqnntahihpoyfcahmucjlxofwjryjjfytgedaholssotycxhywdzyzdvlvbzxertxeipcklyjkrvcnnveqtudgkaewerdnrviabaamuyymumquprichjcctmervgmxrtuaxtxfvjpdcvwghnwkfbiqpivwvnleopvcncxxtatzbkfabmbgsosezazvxvevyjevuxhpyqncszmzlnlxbxfvrwkmmywuhqgceleiinnwrytshcigzelnrfpbadewyappzrjwzfqxiyjcbmzjvwzldbiicpwlnpvlgzfxtmvgxjdwjzifesaxozhnsubqtfaztagwbrjksnxdazxdpquwyklsogucuiixspqkpnipciomejhjgjoxgemkuijeawaqkwgmsmuvzbhkzbqoazxdglexgxbhveggxfzkxqsukvujamqsiwpdilqedzzgqcttkdabpmybkpyipuujpofqjpivzzautmvcfbyjzwyalxgxotsnazalicoxdzggxmafplrrrcecgfwkdkentjwjjiheutxfuxspdgvhcgyziobkwwndvhsvlfzlcjbicyxsdbhqigzewhixlxjqbknanywfyfduuvegiumtnpilzrerafyaylrpnjtsktbvavkdhxfzwirqawpzqbjopyfiukijyhtieevzldnxrkmtqedullaqorikoelfirmdkkxhfbkeiwpivooztijfmazvyumaqnfvcwwpmjnlfisvohttiqihwyknocbqloxokuwsrjhtoasiivununmefyrxaigcnagxareuciubdxatbmfieyboyrefthnhfyhufosfqdjeehgounlkgwpgluqthhnlypnxbexuqyhnaeppdfjgwpbibhjeeptwbzsvcebzwosynxkzfoaygrnnrgjdmfucnunkjnervmfwxskwibhlwdzzgppxhzdqsjnqrpxdlabbcdtxqpuptpmjtfovtmvgrxxremgbfzgcdcxuackddqgfkvzkwjxhtonbhujcrjpnqnswqswlkubxwyzpnculzjfvulqrnunvgotzkuyisjktxiwreftbalczvluoimahmsuupjmqrurrtttrdtivwkyxbypxqhlgnrvsortiqzirykcnpcjzasjcoxlwrpjpajfzbndlrbdrgcyydxdhtsjltqdfgbijxpepysmsyhblomaufoafcjabrdhtompxdjgssioytkedqoomktrfaxiarjrbjmnyezcwlfxqkrkazammudqhndfnkemdvjnbahkbmmpltzupwnybqdbrkmujsmoyttnhwhydgioatmygrosgsjmnawkxwchtpgcrkfrwvligaoowrrburrlzglozydsqnepqdvveagdjetzfcgupymxxbmfheydayaevamouyqlebnngackvtcpsuopuoawrkhwcnnqnstcrvcspqerredtahrkdnfdzapmyqzgplrepjsxznjsesiduxyslnlhlssszwtonxfmovkikbfopiyjmnfnztesldstolqyplczbpgrexwnfwzfdausdsyicchmfpebljwbvlqbrwdoeflmfvlgbxukuztxngftwjzvjntolpzcmflevmsnmlqmrxtdtwkmwtelrleeklaamfduqsdmhmvypaxzszcjytyurujeqriythhkoyurhrvbyqmozdnissivkwmiprrvieamftbjoicbjpvcphnnkmmjnrzqxclwrvnxjcohjhzwexgcjjrfyaisvvjccokxfycbaqwqgnylitmfyvdambrtbghcvbhbbvpeglhpvyawvxzphyjswgebbrpxyrnaczjmfyukvtdhtevbrisuoquynkrsysixsuktswwxynnmnnsqpgrappzlcnmflaubfkxowvzrwkxcjrseziwqvcdbfmcykajdephktudjosklyqpaqtbbnsdrvvbhjzbkybhryffalyczubankkrjbgtfkfvahdukeyybcxsfaudvgcchsraoxbqxbiemrudhjgfelwemkyeralmbgvtgqhvgpskmpvwaxsxqkksmbwrgisuydnyfmlucdfbujuqqyypcfotidqheyusosjfwcigdbppgrqwwveslwylqpaxfgjhmwxzodxjzjlwqtqonzggcjheevverggvtgejrlhwhatyydofnhmanobpntflkmrtnbsfxskzayrbrnbobxduitrlracnnaoqxebhogbrfbvebvvryopqlaeammwjhaiamqjoutptupvhctgemqizzxcficnognbilaawyldlmyrizaewcckefcehjrcpgiwuglwctywoofoaohlhlcqrynvmrybyblxftobasfskesimnyaqvlwmugaaupyclnwfieaampmfzhlgfivgoahejpacouzjhofcgczzaqhmszpmqpznfcuvbuvzhogbpgpmbaeljdgqjiulwrfokckeydozdvlpoaykdnbfjtgehnzjomelzrobfvzfmpfwuypazfgeteearekcczvrleoyrqudbiserphcrzyielrqewnlmgqldkzsdtrzwqolnttodzrbkwtzmlcrjiqttyftnhujnodccqndjefblvjwjqlarxcheacydskzhwbpzwqwkputfzusjgssstboytyhlbhrlmxctvsizbocnwuhrsccroujafkauxkrzlvsatrjhjoulhkxlxtwstdqrpibjwupkppkqmrnykoppecttmjxnstathqglcdpxhponvkzfnmhwvkugmtxecvcfqoyqlaclrdgdutsbladuggcpgkqrdawcqckuzrqfynrtewvqloyhmorpvchzntyhmjzlbfezeallvyoovzuvnlufswwdkslnyuecqmvzkiwqjmfkhvjnmvgzikahzocejltveeropdnazdpsicaihbntrqkbemhmuzeoqcwfiodvvutwwywluykmcnojwhhcwdscvkfxgwissbrazrrqfpshbjotiedrgdppdwtdcvwjhddogdzarvrztxyyqtnojothpjenfoesovqidpaiumrrkajhatfesxrdfshmufudlrtznfxcddhpfkkiawktxmbzctvbwpxbgiyslnlwjhayjlffmmbbonfhoqoutmjmxmqpuzkdefizbceaolibmchcadyqsxqgacebfjsswaaoenybknjpzhfumxestvpwtgswnysetqxupklnmpfnpnjryzdixolcisazlcvemwlyfrlmmhhzdkdpyvtuqquslvnhafjfkdiozuhmhocuhwivodtxlxuydzeyzzqegarbwvqiwpuvybzxyaalknyzxprrxmevzofurvqcbohpvjxtoemqevcynhftvhwmtwwtjalirukkhvxmhclontxpuafpwknwmwxdbashjtsznrkazngrmzbwoznypkdhalpvgrlflkejkbybjnemwzobzyfkysymmeubqzbgerkswxyojlrtyuzuwgydcdnroyokyhbpqesvtzabjgeabwwnlojsxieodeenonaqliptriswkdzcgfwjljeujdpmxsraizvdlvuqsmfwunkoafcjkemmlzbztfzmtdtvidjdvnxvwvvengcfajvtbsltpmisbhjyoraldphjxgmbyridhvltnqtutovnetksxagcbcsovypspzipjiidqqjyhqxptsloriuflxshqkssluvwyecchuqapazctewywnsjcalgmzxrcrycapnshukvvrrkhxcksbhfmubhdtuordlpsvvfduwbvrzswecwxrauqyvxlzcwgsucidisaglajsokzkhmzeheqvbkkxrzcphhzzahtqpchudofpsftgcjleprkzqcxqjuhmimgoelhyxvqwsopvmuothuviqymknnevoryficlkkifvoveagwwzxxsbtpmuphlzhybzavpmkagwtcktqkeovskupsuxsywxwncokqdhueaaqnoyjsxsizrepudbqyindauqecyymgjnpswktjauozkowpkjjcseezhasjsjpnsenkentcqgzclrmsgnuygjwqegglgcsufmicgwmlkbuxfqsogzfjiksjpdgrbjzprmwqkjojtwzkyuxwhhvrwmissqxsrhvyilasetwfitstpntcyrmaadhmuevzbbakftcqqbqkmuzlkqwrsisagkmjqswgsvnffjbgkvywioaabndgvwwnynxxnoikobyxvjcjuajwirdimyldarbosknvebwhfjuugntzwyqetffjlfcnffbuesymybtsxgiwpjayuznxwcgioajtqeorvzswicpfqhsntnhhvjrqcoqlzvdxydpkkchetlbwoexfpyjmokfnxzfiahakdsculjdxuwzkbftuimpxhnfawwgcffodpljgzhwyrybzkziwqhxbbkentxopopqetuhgkhbwwoixyyftsnfwcyecjoxbqjjaevbwhzibccbcldttaulcwwfztzehtutgfihwsgafjwmtevpyfvggmndmcsbnewpovordalmxklvzuelivmjagqqpzmczhefrhdyobvomkjhlpvlfljuorvwyvliahlbiazxwvnpjxombyuiqjsvdvvmrtjykyjrxtyabsjgpcoiodpzbdnrvczdazesbtrtrxqjsuwbetvapcujysdtiaeojoouhzxfhegsmvumtjpxqnvsaxcbzjdjjmzpdqnxczqszbtgubyvtydwytntwvskssqnggertcikdkpisgvekzushltzzfedcmtsthfvyucseiceqrajr");
   Solution s;
   cout << "Input " << i1 << " : " << s.removeDuplicateLetters(i1) << endl;
   cout << "Input " << i2 << " : " << s.removeDuplicateLetters(i2) << endl;
   cout << "Input " << i3 << " : " << s.removeDuplicateLetters(i3) << endl;
   cout << "Input " << i4 << " : " << s.removeDuplicateLetters(i4) << endl;
   return 0;
}
