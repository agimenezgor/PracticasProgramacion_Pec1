.PHONY: clean All

All:
	@echo "----------Building project:[ pec1 - Debug ]----------"
	@cd "pec1" && "$(MAKE)" -f  "pec1.mk"
clean:
	@echo "----------Cleaning project:[ pec1 - Debug ]----------"
	@cd "pec1" && "$(MAKE)" -f  "pec1.mk" clean
