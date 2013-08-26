CC      = g++
CPP     = g++
#PROF    = -pg
DEBUG   = -g
WARN    = -Wall -fpermissive -Wparentheses
OPT     = -O2
CFLAGS  = $(DEBUG) ${OPT} $(WARN) $(PROF)
C_FLAGS = $(CFLAGS) 
VPATH   = ./OBJ


DIR = ./OBJ


C_FILES = abil.cc account.cc acid.cc act.cc action.cc affect.cc alias.cc align.cc appear.cc area.cc armor.cc auction.cc ban.cc bank.cc \
          bard.cc bash.cc bit.cc bow.cc bug.cc cards.cc channel.cc char.cc char_name.cc clan.cc cleric.cc code.cc code2.cc cold.cc color.cc corpse.cc  \
          custom.cc damage.cc death.cc descr.cc dictionary.cc display.cc drink.cc druid.cc dynamic.cc edit.cc enemy.cc exit.cc event.cc event2.cc  \
          exp.cc familiar.cc fight.cc fight2.cc fight3.cc file.cc find.cc fire.cc flag.cc flee.cc food.cc get.cc give.cc group.cc \
          handler.cc help.cc hide.cc host.cc html.cc imm.cc interp.cc kick.cc leech.cc level.cc library.cc \
          lib_exit.cc lib_fight.cc lib_logic.cc lib_list.cc lib_object.cc lib_path.cc lib_quest.cc lib_time.cc lib_vehicle.cc \
          light.cc list.cc log.cc login.cc look.cc macros.cc mage.cc magic.cc magic2.cc memory.cc misc.cc mob_imm.cc mobile.cc money.cc  \
          monk.cc mount.cc move.cc move2.cc mprog.cc network.cc newbie.cc note.cc number.cc obj_imm.cc obj_name.cc obj_prop.cc \
          obj_sort.cc object.cc object2.cc oprog.cc option.cc output.cc paladin.cc path.cc player.cc pet.cc pos.cc  \
          program.cc prompt.cc psi.cc put.cc quest.cc ranger.cc recipe.cc recog.cc regen.cc relig.cc reput.cc rescue.cc  \
	  reset.cc room.cc rtable.cc save.cc score.cc search.cc set.cc shock.cc shop.cc skill.cc social.cc sound.cc spell.cc startup.cc string.cc table.cc teleport.cc \
          twf.cc thief.cc thing.cc throw.cc time.cc tprog.cc track.cc trainer.cc undead.cc update.cc variable.cc vehicle.cc verb.cc vote.cc \
	  wand.cc water.cc wear.cc weather.cc weight.cc where.cc who.cc


C_FILES_GOOD = abil.cc acid.cc act.cc alias.cc align.cc armor.cc ban.cc bank.cc bard.cc bash.cc bit.cc bow.cc bug.cc cards.cc char.cc code.cc \
 	cold.cc corpse.cc custom.cc death.cc descr.cc display.cc drink.cc druid.cc enemy.cc exit.cc event.cc exp.cc familiar.cc fight3.cc file.cc \
 	fire.cc flee.cc food.cc hide.cc handler.cc html.cc kick.cc leech.cc level.cc lib_exit.cc lib_fight.cc lib_logic.cc lib_object.cc lib_path.cc \
 	lib_quest.cc lib_time.cc lib_vehicle.cc light.cc list.cc macros.cc memory.cc misc.cc mobile.cc money.cc monk.cc newbie.cc note.cc obj_prop.cc \
 	obj_sort.cc object.cc object2.cc output.cc paladin.cc program.cc psi.cc quest.cc ranger.cc recipe.cc recog.cc rescue.cc rtable.cc score.cc \
 	search.cc set.cc shock.cc social.cc sound.cc spell.cc time.cc track.cc trainer.cc undead.cc update.cc variable.cc vehicle.cc verb.cc water.cc \
 	weather.cc weight.cc where.cc


C_FILES_WIP = account.cc action.cc affect.cc appear.cc area.cc auction.cc channel.cc char_name.cc clan.cc cleric.cc code2.cc color.cc damage.cc \
 	dictionary.cc edit.cc event2.cc fight.cc fight2.cc find.cc flag.cc get.cc give.cc group.cc help.cc host.cc imm.cc interp.cc library.cc \
 	lib_list.cc log.cc login.cc look.cc mage.cc magic.cc magic2.cc mob_imm.cc mount.cc move.cc move2.cc mprog.cc network.cc number.cc obj_imm.cc \
 	obj_name.cc oprog.cc option.cc path.cc player.cc pet.cc pos.cc prompt.cc put.cc regen.cc relig.cc reput.cc reset.cc room.cc save.cc shop.cc \
 	skill.cc startup.cc string.cc table.cc teleport.cc twf.cc thief.cc thing.cc throw.cc tprog.cc vote.cc wand.cc wear.cc who.cc


O_FILES = $(C_FILES:.cc=.o)


Q_FILES = $(C_FILES_GOOD:.cc=.o) $(C_FILES_WIP:.cc=.o)


all: $(O_FILES)
	rm -f tanglewood
	$(CC) $(C_FLAGS) -o tanglewood $(DIR)/*.o $(L_FLAGS)
	rm -f daemon         
	$(CC) $(C_FLAGS) -o daemon daemon.cc $(L_FLAGS)


separate: $(Q_FILES)
	rm -f tanglewood
	$(CC) $(C_FLAGS) -o tanglewood $(DIR)/*.o $(L_FLAGS)
	rm -f daemon
	$(CC) $(C_FLAGS) -o daemon daemon.cc $(L_FLAGS)


clean:
	rm -f OBJ/*.o
	rm -f core core.* tanglewood daemon
	rm -f email.msg
	rm -f Makefile.bak
	rm -f *~


depend: $(C_FILES)
	makedepend -- $(CFLAGS) -- $(C_FILES)


.cc.o:
	$(CPP) -c $(C_FLAGS) -I. $< -o $(DIR)/$@
