SECTIONS
{
  . = 0x007000;
  .text : 
  	{ 
  		*(.text) 
  		_etext = .; 
	}

  . = 0x800100;
  .data : 
  	{ 
  		*(.data) 
	}
  .bss : 
  	{ 
  		*(.bss) 
	}

  . = 0x810000;
  .eeprom : 
  	{ 
  		*(.eeprom) 
	}

  . = 0x820000;
  .fuse : 
  	{ 
  		*(.fuse) 
	}

  . = 0x830000;
  .lock : 
  	{ 
  		*(.lock) 
	}

  . = 0x840000;
  .signature : 
  	{ 
  		*(.signature) 
	}
}
