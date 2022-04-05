#include<iostream>
#include <unordered_map>
#include<string>
#include<fstream>
using namespace std;
void read_instruction(ifstream& file, unordered_map<int,string> & lines)
{
	string inst;
	if (!file.is_open())
		cout << "Can't open file" << endl;
	else
	{
		int i = 0;
		while (getline(file, inst)) 
		{
			lines[i] = inst;
			i = i + 4;
		}
	}
	//for (auto x : lines)
		//cout << x.first << " " << x.second << endl;

}
void read_initial(ifstream& reg, ifstream& memory, unordered_map<string, int>& R, unordered_map<int, int>& M)
{
	string inst;
	if (!reg.is_open()||!memory.is_open())
		cout << "Can't open file" << endl;
	else
	{
		while (reg)
		{
			string r; int value;
			reg >> r >> value;
			if(r!="")
			R[r] = value;
		}
		while (memory)
		{
			int addr,value;
			memory >> addr >> value;
			M[addr] = value;
		}
	}
/*	for (auto x : R)
		cout << x.first << " " << x.second << endl;
	for (auto x : M)
		cout << x.first << " " << x.second << endl;
		*/
}

void operation_divider(string inst) // string of the instruction type will be the input of this function that automaticlly calles the specofoc function for that operation 
{
	if (op == "add")
		output = add_inst(inst);
	if (op == "sub")
		output = sub_inst(inst);
	if (op == "sll")
		output = sll_inst(inst);
	if (op == "slt")
		output = slt_inst(inst);
	if (op == "sltu")
		output = sltu_inst(inst);
	if (op == "xor")
		output = xor_inst(inst);
	if (op == "srl")
		output = srl_inst(inst);
	if (op == "sra")
		output = sra_inst(inst);
	if (op == "or")
		output = or_inst(inst);
	if (op == "and")
		output = and_inst(inst);
	if (op == "slli")
		output = slli_inst(inst);
	if (op == "srli")
		output = srli_inst(inst);
	if (op == "srai")
		output = srai_inst(inst);
	if (op == "addi")
		output = addi_inst(inst);
	if (op == "slti")
		output = slti_inst(inst);
	if (op == "sltiu")
		output = sltiu_inst(inst);
	if (op == "xori")
		output = xori_inst(inst);
	if (op == "ori")
		output = ori_inst(inst);
	if (op == "andi")
		output = andi_inst(inst);
	if (op == "sb")
		output = sb_inst(inst);
	if (op == "sh")
		output = sh_inst(inst);
	if (op == "sw")
		output = sw_inst(inst);
	if (op == "lb")
		output = lb_inst(inst);
	if (op == "lh")
		output = lh_inst(inst);
	if (op == "lw")
		output = lw_inst(inst);
	if (op == "lbu")
		output = lbu_inst(inst);
	if (op == "lhu")
		output = lhu_inst(inst);
	if (op == "beq")
		output = beq_inst(inst);
	if (op == "bne")
		output = bne_inst(inst);
	if (op == "blt")
		output = blt_inst(inst);
	if (op == "bge")
		output = bge_inst(inst);
	if (op == "bltu")
		output = bltu_inst(inst);
	if (op == "bgeu")
		output = bgeu_inst(inst);
	if (op == "jalr")
		output = jalr_inst(inst);
	if (op == "jal")
		output = jal_inst(inst);
	if (op == "lui")
		output = lui_inst(inst);
	if (op == "auipc")
		output = auipc_inst(inst);
}
int add_inst(string inst) // addition instruction 
{
	int output;// = input1 + input2;
	return ouput; 
}
int sub_inst(string inst)  // subtraction instruction
{
	int output;
	return ouput;
}
int sll_inst(string inst) // shift left logical instruction 
{
	int output;
	return ouput;
}
int slt_inst(string inst) // set less than instruction
{
	int output;
	return ouput;
}
int sltu_inst(string inst) // set less than unsigned instruction
{
	int output;
	return ouput;
}
int xor_inst(string inst) // exclusive or instruction 
{
	int output;
	return ouput;
}
int srl_inst(string inst) // shift right logical instruction
{
	int output;
	return ouput;
}
int sra_inst(string inst) // shift right arithmetic instruction 
{
	int output;
	return ouput;
}
int or_inst(string inst) // or instruction
{
	int output;
	return ouput;
}
int and_inst(string inst) // and instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int slli_inst(string inst) // shift left logical immediate instruction  
{
	int output;
	return ouput;
}
int srli_inst(string inst) // shift right logical immediate instrucrtion 
{
	int output;
	return ouput;
}
int srai_inst(string inst) // shfit right arethmetic instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int addi_inst(string inst) // add immediate instruction 
{
	int output;
	return ouput;
}
int slti_inst(string inst) // set if less than immediate instruction 
{
	int output;
	return ouput;
}
int sltiu_inst(string inst) // set if less than unsigned immediate instruction 
{
	int output;
	return ouput;
}
int xori_inst(string inst) // exclusive or immediate instruction 
{
	int output;
	return ouput;
}
int ori_inst(string inst) // or immediate instruction 
{
	int output;
	return ouput;
}
int andi_inst(string inst) // and immediate instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int sb_inst(string inst) // store byte instruction 
{
	int output;
	return ouput;
}
int sh_inst(string inst) // store halfword instruction 
{
	int output;
	return ouput;
}
int sw_inst(string inst) // store word instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int lb_inst(string inst) //  load byte instruction 
{
	int output;
	return ouput;
}
int lh_inst(string inst) //  load halfword instruction 
{
	int output;
	return ouput;
}
int lw_inst(string inst) // load word instruction 
{
	int output;
	return ouput;
}
int lbu_inst(string inst) // load byte unsigned instruction 
{
	int output;
	return ouput;
}
int lhu_inst(string inst) // load halfword unsigne instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int beq_inst(string inst) // branch if equal instruction (==)
{
	int output;
	return ouput;
}
int bne_inst(string inst) // branch if not equal instruction (!=)
{
	int output;
	return ouput;
}
int blt_inst(string inst) // branch if less than instruction(<)
{
	int output;
	return ouput;
}
int bge_inst(string inst) // branch if greater than or equal instruction (>=)
{
	int output;
	return ouput;
}
int bltu_inst(string inst) // branch if less than using unsigned numbers instruction
{
	int output;
	return ouput;
}
int bgeu_inst(string inst) //branch if greater than or equal using unsigned numbers instruction
{
	int output;
	return ouput;
}
/////////////////////////////////
int jalr_inst(string inst) // jump and link register instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int jal_inst(string inst) // jump and link instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////
int lui_inst(string inst) // load upper immediate instruction 
{
	int output;
	return ouput;
}
int auipc_inst(string inst) // add upper immediate to PC instruction 
{
	int output;
	return ouput;
}
/////////////////////////////////



int main()
{
	ifstream inst("instructions.txt");
	ifstream reg_init("initialReg.txt");
	ifstream memory_init("initialMem.txt");
	unordered_map<int, string> lines;
	unordered_map<string, int> reg;
	unordered_map<int, int> memory;
	read_instruction(inst, lines);
	read_initial(reg_init, memory_init, reg, memory);

	return 0;
}