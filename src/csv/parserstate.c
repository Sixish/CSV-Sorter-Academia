/* parserstate.c
 * 
 * @Author Reece Clydesdale
 * @StudentID 18924059
 * @Date 27/10/2016
 * @Purpose Defines functions for creating and interacting with parser states via
 * the parser state manager.
 */
#include "parserstate.h"

/*
 * Creates a ParserStateManager and initialzies its fields.
 */
ParserStateManager *createParserStateManager(void)
{
    ParserStateManager *manager = (ParserStateManager *)
        malloc(sizeof(ParserStateManager));
    ParserStateManager m;
    *manager = m;

    /* Initialize the fields. */
    manager->states = createStack();

    return manager;
}

/*
 * Gets the current state from a ParserStateManager.
 */
ParserState *getParserState(ParserStateManager *manager)
{
    ParserState *state = NULL;
    /* Get the current state, i.e. the last item in the stack. */
    if (manager != NULL && manager->states != NULL)
    {
        state = getLastStackItem(manager->states);
    }

    return state;
}

/*
 * End, thereby freeing and removing, a ParserState from a ParserStateManager.
 */
void endState(ParserStateManager *manager, ParserState *state)
{
    /* Only remove the state if it's the last one in the list. */
    if (state != NULL && getParserState(manager) == state)
    {
        pop(manager->states);
        freeState(state);
    }
}

/*
 * Adds a ParserState to the ParserStateManager.
 */
void addState(ParserStateManager *manager, ParserState *state)
{
    /* Adds the state to the manager. */
    if (manager != NULL && manager->states != NULL)
    {
        push(manager->states, (void *)state);
    }
}

/*
 * Creates a ParserState of the specified type.
 */
ParserState *createParserState(ParserStateManager *manager, int type)
{
    ParserState *state = (ParserState *)malloc(sizeof(ParserState));
    ParserState s;
    *state = s;

    /* Initialize the values. */
    state->type = type;
    state->state = NULL;

    switch (type)
    {
        case PARSER_STATE_PARSE_TABLE:
            state->state = (void *)createParseTableState();
            break;
        case PARSER_STATE_PARSE_ROW:
            state->state = (void *)createParseRowState();
            break;
        case PARSER_STATE_PARSE_COLUMN:
            state->state = (void *)createParseColumnState();
            break;
        default:
            /* Well this is messed up. */
            break;
    }

    addState(manager, state);
    return state;
}

/*
 * Creates a ParseTableState and initializes its fields.
 */
ParseTableState *createParseTableState(void)
{
    ParseTableState *state = (ParseTableState *)
        malloc(sizeof(ParseTableState));
    ParseTableState s;
    *state = s;


    /* Initialize the values. */
    state->table = NULL;

    return state;
}

/*
 * Creates a ParseRowState and initializes its fields.
 */
ParseRowState *createParseRowState(void)
{
    ParseRowState *state = (ParseRowState *)
        malloc(sizeof(ParseRowState));
    ParseRowState s;
    *state = s;

    /* Initialize the values. */
    state->row = NULL;

    return state;
}

/*
 * Creates a ParseColumnState and initializes its fields.
 */
ParseColumnState *createParseColumnState(void)
{
    ParseColumnState *state = (ParseColumnState *)
        malloc(sizeof(ParseColumnState));
    ParseColumnState s;
    *state = s;

    /* Initialize the values. */
    state->stateStart = false;
    state->stateEscapedMode = false;
    state->stateLiteralMode = false;

    return state;
}

/*
 * Gets the state from the specialized ParserState.
 */
int getParserStateType(ParserState *state)
{
    int type = 0;
    if (state != NULL)
    {
        type = state->type;
    }

    return type;
}

/*
 * Sets the column of the ParserColumnState contained by state. The imported
 * ParserState must contain a ParseColumnState (state).
 */
void setStateColumn(ParserState *state, Column *col)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;

    innerState->column = col;
}

/*
 * Sets the 'state start' field of the ParseColumnState contained by state. The
 * imported ParserState must contain a ParseColumnState (state).
 */
void setStateColumnStart(ParserState *state, bool value)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;

    innerState->stateStart = value;
}

/*
 * Sets the 'state escaped mode' field of the ParseColumnState contained by
 * state. The imported ParserState must contain a ParseColumnState (state).
 */
void setStateColumnEscapedMode(ParserState *state, bool value)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;

    innerState->stateEscapedMode = value;
}

/*
 * Sets the 'state literal mode' field of the ParseColumnState contained by
 * state. The imported ParserState must contain a ParseColumnState (state).
 */
void setStateColumnLiteralMode(ParserState *state, bool value)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;

    innerState->stateLiteralMode = value;
}

/*
 * Gets the column contained within the ParseColumnState contained within the
 * imported ParseColumnState. The imported ParserState must contain a
 * ParseColumnState (state).
 */
Column *getStateColumn(ParserState *state)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;
    Column *col = innerState->column;

    return col;
}

/*
 * Gets the start state of the ParseColumnState contained within the imported
 * ParseColumnState. The imported ParserState must contain a ParseColumnState
 * (state).
 */
bool getStateColumnStart(ParserState *state)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;
    bool val = innerState->stateStart;
    return val;
}

/*
 * Gets the escaped mode flag of the ParseColumnState contained within the
 * imported ParseColumnState. The imported ParserState must contain a
 * ParseColumnState (state).
 */
bool getStateColumnEscapedMode(ParserState *state)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;
    bool val = innerState->stateEscapedMode;
    return val;
}

/*
 * Gets the literal mode flag of the ParseColumnState contained within the
 * imported ParseState. The imported ParserState must contain a ParseColumnState
 * (state).
 */
bool getStateColumnLiteralMode(ParserState *state)
{
    ParseColumnState *innerState = (ParseColumnState *)state->state;
    bool val = innerState->stateLiteralMode;
    return val;
}

/*
 * Sets the row of the ParseRowState contained within the imported ParserState.
 * The imported ParserState must contain a ParseRowState (state).
 */
void setStateRow(ParserState *state, Row *row)
{
    ParseRowState *innerState = (ParseRowState *)state->state;
    innerState->row = row;
}

/*
 * Gets the row of the ParserRowState contained by the imported ParserState.
 * The imported ParserState must contain a ParserRowState.
 */
Row *getStateRow(ParserState *state)
{
    ParseRowState *innerState = (ParseRowState *)state->state;
    Row *row = innerState->row;
    return row;
}

/*
 * Sets the table of the ParserTableState contained by the imported ParserState.
 * The imported ParserState must contain a ParserTableState.
 */
void setStateTable(ParserState *state, Table *table)
{
    ParseTableState *innerState = (ParseTableState *)state->state;
    innerState->table = table;
}

/*
 * Gets the table of the ParserTableState contained by the ParserState.
 * The imported ParserState must contain a ParserTableState.
 */
Table *getStateTable(ParserState *state)
{
    ParseTableState *innerState = (ParseTableState *)state->state;
    Table *table = innerState->table;

    return table;
}

/*
 * Frees all memory associated with a ParserStateManager.
 */
void freeStateManager(ParserStateManager *manager)
{
    if (manager != NULL)
    {
        freeStack(manager->states);
        free(manager);
    }
}

/*
 * Frees all memory associated with a ParseTableState.
 */
void freeStateTable(ParseTableState *state)
{
    if (state != NULL)
    {
        /* We do NOT free the table (the result of the parsing). */
        free(state);
    }
}

/*
 * Frees all memory associated with a ParseRowState.
 */
void freeStateRow(ParseRowState *state)
{
    if (state != NULL)
    {
        /* We do NOT free the row (the result of the parsing). */
        free(state);
    }
}

/*
 * Frees all memory associated with a ParseColumnState.
 */
void freeStateColumn(ParseColumnState *state)
{
    if (state != NULL)
    {
        /* We do NOT free the column (the result of the parsing). */
        free(state);
    }
}

/*
 * Frees all memory associated with a ParserState. This frees both the ParserState
 * and the specializes state it contains.
 */
void freeState(ParserState *state)
{
    if (state != NULL)
    {
        switch (state->type)
        {
            case PARSER_STATE_PARSE_TABLE:
                freeStateTable((ParseTableState *)state->state);
                break;
            case PARSER_STATE_PARSE_ROW:
                freeStateRow((ParseRowState *)state->state);
                break;
            case PARSER_STATE_PARSE_COLUMN:
                freeStateColumn((ParseColumnState *)state->state);
                break;
            default:
                /* Well this is awkward. */
                break;
        }
        state->state = NULL;

        free(state);
    }
}

/*
 * Checks if the ParserStateManager has states left. Returns true if the
 * ParserStateManager is empty; false otherwise.
 */
bool parserStateManagerIsEmpty(ParserStateManager *manager)
{
    bool isEmpty = true;
    if (manager == NULL)
    {
        isEmpty = stackIsEmpty(manager->states);
    }

    return isEmpty;
}
