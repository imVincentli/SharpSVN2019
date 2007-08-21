#include "stdafx.h"
#include "SvnAll.h"

using namespace SharpSvn::Apr;
using namespace SharpSvn;


void SvnClient::Blame(SvnTarget^ target, EventHandler<SvnBlameEventArgs^>^ blameHandler)
{
	if(!target)
		throw gcnew ArgumentNullException("target");
	else if(!blameHandler)
		throw gcnew ArgumentNullException("blameHandler");

	Blame(target, gcnew SvnBlameArgs(), blameHandler);
}
static svn_error_t *svn_client_blame_receiver_handler(void *baton, apr_int64_t line_no, svn_revnum_t revision, const char *author, const char *date, const char *line, apr_pool_t *pool)
{
	SvnClient^ client = AprBaton<SvnClient^>::Get((IntPtr)baton);

	AprPool thePool(pool, false);

	SvnBlameArgs^ args = dynamic_cast<SvnBlameArgs^>(client->CurrentArgs); // C#: _currentArgs as SvnCommitArgs
	if(args)
	{
		SvnBlameEventArgs^ e = gcnew SvnBlameEventArgs(revision, line_no, author, date, line, %thePool);
		try
		{
			args->OnBlameHandler(e);

			if(e->Cancel)
				return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, "Diff summary receiver canceled operation");
		}
		catch(Exception^ e)
		{
			return SvnException::CreateExceptionSvnError("Diff summary receiver", e);
		}
		finally
		{
			e->Detach(false);
		}
	}

	return nullptr;
}


bool SvnClient::Blame(SvnTarget^ target, SvnBlameArgs^ args, EventHandler<SvnBlameEventArgs^>^ blameHandler)
{
	if(!target)
		throw gcnew ArgumentNullException("target");
	else if(!args)
		throw gcnew ArgumentNullException("args");

	EnsureState(SvnContextState::AuthorizationInitialized);

	if(_currentArgs)
		throw gcnew InvalidOperationException(SharpSvnStrings::SvnClientOperationInProgress);

	AprPool pool(%_pool);
	_currentArgs = args;

	if(blameHandler)
		args->BlameHandler += blameHandler;
	try
	{
		svn_diff_file_options_t *options = svn_diff_file_options_create(pool.Handle);

		options->ignore_space = (svn_diff_file_ignore_space_t)(svn_diff_file_ignore_space_none + (svn_diff_file_ignore_space_t)args->IgnoreSpacing);
		options->ignore_eol_style = args->IgnoreLineEndings;

		svn_opt_revision_t pegRev = target->GetSvnRevision(SvnRevision::Working, SvnRevision::Head);

		svn_error_t *r = svn_client_blame3(
			pool.AllocString(target->TargetName),
			&pegRev,
			args->Start->AllocSvnRevision(%pool),
			args->End->AllocSvnRevision(%pool),
			options,
			args->IgnoreMimeType,
			svn_client_blame_receiver_handler,
			(void*)_clientBatton->Handle,
			CtxHandle,
			pool.Handle);

		return args->HandleResult(r);
	}
	finally
	{
		_currentArgs = nullptr;
		if(blameHandler)
			args->BlameHandler -= blameHandler;
	}
}

void SvnClient::GetBlame(SvnTarget^ target, [Out] IList<SvnBlameEventArgs^>^% list)
{
	if(!target)
		throw gcnew ArgumentNullException("target");

	InfoItemCollection<SvnBlameEventArgs^>^ results = gcnew InfoItemCollection<SvnBlameEventArgs^>();

	try
	{
		Blame(target, gcnew SvnBlameArgs(), results->Handler);
	}
	finally
	{
		list = safe_cast<IList<SvnBlameEventArgs^>^>(results);
	}
}

bool SvnClient::GetBlame(SvnTarget^ target, SvnBlameArgs^ args, [Out] IList<SvnBlameEventArgs^>^% list)
{
	if(!target)
		throw gcnew ArgumentNullException("target");
	else if(!args)
		throw gcnew ArgumentNullException("args");

	InfoItemCollection<SvnBlameEventArgs^>^ results = gcnew InfoItemCollection<SvnBlameEventArgs^>();

	try
	{
		return Blame(target, args, results->Handler);
	}
	finally
	{
		list = safe_cast<IList<SvnBlameEventArgs^>^>(results);
	}
}
