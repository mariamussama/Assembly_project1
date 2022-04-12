#include<iostream>
#include <unordered_map>
#include<string>
#include<fstream>
using namespace std;
//determine the operation 
void det_op(string& operation, string line) //extract label and operation
{
	string Temp = "";
	int i = 0;
	while (line[i] != ' ')
	{
		if (line[i] == ':')
		{
			Temp = ""; i++;
		}
		else
			Temp = Temp + line[i];
		i++;
	}
	operation = Temp;
}
//determine the label if any
void det_label(string& label, string line)
{
	string temp = "";
	int i = 0;
	label = temp;
	while (line[i] != ' ')
	{
		if (line[i] == ':')
		{
			label = temp;
		}
		else
			temp = temp + line[i];
		i++;
	}
}

//read instructions and save them in the corresponding unordered map(lines) and labels
void read_instruction(ifstream& file, unordered_map<int, string>& lines, unordered_map<string, int>& label)
{
	string inst,lab="";
	if (!file.is_open())
		cout << "Can't open file" << endl;
	else
	{
		int i = 0;
		while (getline(file, inst))
		{
			lines[i] = inst;
			det_label(lab, inst);
			if (lab!="")
				label[lab] = i;//save labels and their corresponding instruction no.
			i = i + 4;
		}
		
	}
	//for (auto x : lines)
		//cout << x.first << " " << x.second << endl;

}
//read the initial values of some reg and memory locations
void read_initial(ifstream& reg, ifstream& memory, unordered_map<string, int>& R, unordered_map<int, int>& M)
{
	string inst;
	if (!reg.is_open() || !memory.is_open())
		cout << "Can't open file" << endl;
	else
	{
		while (reg)
		{
			string r; int value;
			reg >> r >> value;
			if (r != "")
				R[r] = value;
		}
		while (memory)
		{
			int addr, value;
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

//instruction divider to get the registers/ offsets/ labels....
void three_reg(string& rd, string& rs1, string& rs2, string Inst, string op) //all instructions that deal with three registers
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	rs1 = reg[1];
	rs2 = reg[2];
}

void imm_op(string& rd, string& rs1, int& val, string Inst, string op) //immediate instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	rs1 = reg[1];
	val = stoi(reg[2]);
}

void load_op(string& rd, string& rs1, int& offset, string Inst, string op) //load instructions 
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		if (line[i] == '(')
		{
			offset = stoi(temp);
			temp = "";
		}
		if (line[i] == ')')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	rs1 = reg[1];

}

void store_op(string& rs1, string& rs2, int& offset, string Inst, string op) //store instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		if (line[i] == '(')
		{
			offset = stoi(temp);
			temp = "";
		}
		if (line[i] == ')')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rs1 = reg[0];
	rs2 = reg[1];

}

void branch_op(string& rs1, string& rs2, string& label, string Inst, string op) //branching instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rs1 = reg[0];
	rs2 = reg[1];
	label = reg[2];
}

void Jal_op(string& rd, string& label, string Inst, string op) //jump and link instruction
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	label = reg[1];
}

void LUI_AUIPC(string& rd, int& val, string Inst, string op) //LUI and AUIPC instructions
{
	vector<string>reg;
	string temp;
	int index = 0;
	reg.resize(1);
	int L = op.length();
	string line = Inst.substr(Inst.find(op) + L + 1, Inst.length() - 1);
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ',') && (line[i] != ' ') && (line[i] != '(') && (line[i] != ')'))
		{
			temp.push_back(line[i]);

		}
		if (line[i] == ',')
		{
			reg[index] = temp;
			temp = "";
			index++;
			reg.resize(index + 1);
		}
		reg[index] = temp;
	}
	rd = reg[0];
	val = stoi(reg[1]);
}

//the operations fuunctions
void add_inst(string inst) // addition instruction 
{
	cout << "add" << endl;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "add");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sub_inst(string inst)  // subtraction instruction
{
	cout << "sub" << endl;
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sub");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sll_inst(string inst) // shift left logical instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sll");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void slt_inst(string inst, unordered_map<string, int>& reg) // set less than instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "slt");
	if (reg.at(rs1) < reg.at(rs2))
		reg[rd] = 1;
	else
		reg[rd] = 0;
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sltu_inst(string inst) // set less than unsigned instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sltu");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void xor_inst(string inst) // exclusive or instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "xor");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void srl_inst(string inst, unordered_map<string, int>& reg) // shift right logical instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "srl");
	reg[rd] = reg.at(rs1)/(pow(2,reg.at(rs2)));
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void sra_inst(string inst) // shift right arithmetic instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "sra");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void or_inst(string inst, unordered_map<string, int>& reg) // or instruction
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "or");
	if (reg.at(rs1) || reg.at(rs2))
		reg[rd] = 1;
	else 
		reg[rd] = 0;
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
void and_inst(string inst) // and instruction 
{
	string rd, rs1, rs2;
	three_reg(rd, rs1, rs2, inst, "and");
	cout << rd << " " << rs1 << " " << rs2 << endl;
}
/////////////////////////////////
void slli_inst(string inst) // shift left logical immediate instruction  
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "slli");
	cout << rd << " " << rs1 << " " << val << endl;
}
void srli_inst(string inst, unordered_map<string, int>& reg) // shift right logical immediate instrucrtion 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "srli");
	reg[rd] = reg.at(rs1) / (pow(2, val));
	cout << rd << " " << rs1 << " " << val << endl;
}
void srai_inst(string inst) // shfit right arethmetic instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "srai");
	cout << rd << " " << rs1 << " " << val << endl;
}
/////////////////////////////////
void addi_inst(string inst) // add immediate instruction 
{
	cout << "addi" << endl;
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "addi");
	cout << rd << " " << rs1 << " " << val << endl;
}
void slti_inst(string inst) // set if less than immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "slti");
	cout << rd << " " << rs1 << " " << val << endl;
}
void sltiu_inst(string inst) // set if less than unsigned immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "sltiu");
	cout << rd << " " << rs1 << " " << val << endl;
}
void xori_inst(string inst) // exclusive or immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "xori");
	cout << rd << " " << rs1 << " " << val << endl;
}
void ori_inst(string inst) // or immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "ori");
	cout << rd << " " << rs1 << " " << val << endl;
}
void andi_inst(string inst) // and immediate instruction 
{
	string rd, rs1; int val;
	imm_op(rd, rs1, val, inst, "andi");
	cout << rd << " " << rs1 << " " << val << endl;
}
/////////////////////////////////
void sb_inst(string inst) // store byte instruction 
{
	string rs1, rs2; int offset;
	load_op(rs1, rs2, offset, inst,"sb");
	cout << rs1 << " " << rs2 << " " << offset << endl;
}
void sh_inst(string inst) // store halfword instruction 
{
	string rs1, rs2; int offset;
	load_op(rs1, rs2, offset, inst, "sh");
	cout << rs1 << " " << rs2 << " " << offset << endl;
}
void sw_inst(string inst) // store word instruction 
{
	string rs1, rs2; int offset;
	load_op(rs1, rs2, offset, inst, "sw");
	cout << rs1 << " " << rs2 << " " << offset << endl;
}
/////////////////////////////////
void lb_inst(string inst) //  load byte instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lb");
	cout << rd << " " << rs1 << " " << offset << endl;
}
void lh_inst(string inst) //  load halfword instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lh");
	cout << rd << " " << rs1 << " " << offset << endl;
}
void lw_inst(string inst) // load word instruction 
{
	cout << "lw" << endl;
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lw");
	cout << rd << " " << rs1 << " " << offset << endl;
}
void lbu_inst(string inst) // load byte unsigned instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lbu");
	cout << rd << " " << rs1 << " " << offset << endl;
}
void lhu_inst(string inst) // load halfword unsigne instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "lhu");
	cout << rd << " " << rs1 << " " << offset << endl;
}
/////////////////////////////////
void beq_inst(string inst) // branch if equal instruction (==)
{
	cout << "beq" << endl;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "beq");
	cout << rs1 << " " << rs2 << " " << label << endl;
}
void bne_inst(string inst) // branch if not equal instruction (!=)
{
	cout << "bne" << endl;
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bne");
	cout << rs1 << " " << rs2 << " " << label << endl;
}
void blt_inst(string inst) // branch if less than instruction(<)
{
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "blt");
	cout << rs1 << " " << rs2 << " " << label << endl;
}
void bge_inst(string inst) // branch if greater than or equal instruction (>=)
{
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bge");
	cout << rs1 << " " << rs2 << " " << label << endl;
}
void bltu_inst(string inst) // branch if less than using unsigned numbers instruction
{
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bltu");
	cout << rs1 << " " << rs2 << " " << label << endl;
}
void bgeu_inst(string inst) //branch if greater than or equal using unsigned numbers instruction
{
	string rs1, rs2, label;
	branch_op(rs1, rs2, label, inst, "bgeu");
	cout << rs1 << " " << rs2 << " " << label << endl;
}
/////////////////////////////////
void jalr_inst(string inst) // jump and link register instruction 
{
	string rd, rs1; int offset;
	load_op(rd, rs1, offset, inst, "jalr");
	cout << rd << " " << rs1 << " " << offset << endl;
}
/////////////////////////////////
void jal_inst(string inst) // jump and link instruction 
{
	string rd, label;
	Jal_op(rd, label, inst, "jal");
	cout << rd << " " << label << endl;
}
/////////////////////////////////
void lui_inst(string inst) // load upper immediate instruction 
{
	string rd; int val;
	LUI_AUIPC(rd, val, inst, "lui");
	cout << rd << " " << val << endl;
}
void auipc_inst(string inst) // add upper immediate to PC instruction 
{
	string rd; int val;
	LUI_AUIPC(rd, val, inst, "auipc");
	cout << rd << " " << val << endl;
}
/////////////////////////////////
//divider function that call the operation function based on the operation
void operation_divider(string inst, unordered_map<string, int>& reg, unordered_map<string, int>& label, unordered_map<int, int>& memory) // string of the instruction type will be the input of this function that automaticlly calles the specific function for that operation 
{
	int output;
	string op;
	det_op(op, inst);
	//cout << op << endl;
	if (op == "add")
		add_inst(inst);
	if (op == "sub")
		sub_inst(inst);
	if (op == "sll")
		sll_inst(inst);
	if (op == "slt")
		slt_inst(inst,reg);
	if (op == "sltu")
		sltu_inst(inst);
	if (op == "xor")
		xor_inst(inst);
	if (op == "srl")
		srl_inst(inst,reg);
	if (op == "sra")
		sra_inst(inst);
	if (op == "or")
		or_inst(inst, reg);
	if (op == "and")
		and_inst(inst);
	if (op == "slli")
		slli_inst(inst);
	if (op == "srli")
		srli_inst(inst,reg);
	if (op == "srai")
		srai_inst(inst);
	if (op == "addi")
		addi_inst(inst);
	if (op == "slti")
		slti_inst(inst);
	if (op == "sltiu")
		sltiu_inst(inst);
	if (op == "xori")
		xori_inst(inst);
	if (op == "ori")
		ori_inst(inst);
	if (op == "andi")
		andi_inst(inst);
	if (op == "sb")
		sb_inst(inst);
	if (op == "sh")
		sh_inst(inst);
	if (op == "sw")
		sw_inst(inst);
	if (op == "lb")
		lb_inst(inst);
	if (op == "lh")
		lh_inst(inst);
	if (op == "lw")
		lw_inst(inst);
	if (op == "lbu")
		lbu_inst(inst);
	if (op == "lhu")
		lhu_inst(inst);
	if (op == "beq")
		beq_inst(inst);
	if (op == "bne")
		bne_inst(inst);
	if (op == "blt")
		blt_inst(inst);
	if (op == "bge")
		bge_inst(inst);
	if (op == "bltu")
		bltu_inst(inst);
	if (op == "bgeu")
		bgeu_inst(inst);
	if (op == "jalr")
		jalr_inst(inst);
	if (op == "jal")
		jal_inst(inst);
	if (op == "lui")
		lui_inst(inst);
	if (op == "auipc")
		auipc_inst(inst);
}


int main()
{
	ifstream inst("instructions.txt");
	ifstream reg_init("initialReg.txt");
	ifstream memory_init("initialMem.txt");
	unordered_map<int, string> lines;
	unordered_map<string, int> label;
	unordered_map<string, int> reg;
	unordered_map<int, int> memory;
	read_instruction(inst, lines, label);
	read_initial(reg_init, memory_init, reg, memory);
	for (auto x : lines)
	{
		string op, label;
		cout << x.first << " " << x.second << endl;
		//det_op(op, x.second);
		operation_divider(x.second);
		//cout << op << endl;
	}
	for (auto x : label)
	{
		cout << x.first << " " << x.second << endl;
	}

	return 0;
}